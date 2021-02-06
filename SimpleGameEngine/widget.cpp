#include "widget.h"
#include"simpleobject3d.h"
#include "group.h"
#include "camera.h"
#include "modelAssembling.h"
#include "skybox.h"

#include <QMouseEvent>
#include <QOpenGLContext>
#include <QtMath>
#include <QKeyEvent>




Widget::Widget(QWidget *parent): QOpenGLWidget(parent)
{
    _camera = new Camera();
}


Widget::~Widget()
{
    for (int i = 0 ; i < _transformableObjects.size() ; ++i)
        delete _transformableObjects[i];
}


void Widget::initializeGL()
{
    glClearColor(0.0 , 0.0 , 0.0 , 1.0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    initShaders();


    ////////////////////////   TEMPORARY   /////////////////////////
    float step = 2.0f;

    modelData cubeModelData = GetCubeModelData(1.0f);
    QImage cubeTexture = QImage(":/wood.png");

    _groups.push_back(new Group());

    for (int x = -step ; x <= step ; x += step)
    {
        for (int y = -step ; y <= step ; y += step)
        {
            for (int z = -step ; z <= step ; z += step)
            {
                _singleObjects.push_back(new SimpleObject3D(cubeModelData.first , cubeModelData.second , cubeTexture));
                _singleObjects.back()->Translate(x , y , z);
                _groups.back()->AddObject(_singleObjects.back());
            }
        }
    }

    _groups.back()->Translate(-4 , 0 , 0);

    _groups.push_back(new Group());

    for (int x = -step ; x <= step ; x += step)
    {
        for (int y = -step ; y <= step ; y += step)
        {
            for (int z = -step ; z <= step ; z += step)
            {
                _singleObjects.push_back(new SimpleObject3D(cubeModelData.first , cubeModelData.second , cubeTexture));
                _singleObjects.back()->Translate(x , y , z);
                _groups.back()->AddObject(_singleObjects.back());
            }
        }
    }

    _groups.back()->Translate(4 , 0 , 0);


    _groups.push_back(new Group());
    _groups.back()->AddObject(_groups[0]);
    _groups.back()->AddObject(_groups[1]);

    _groups[0]->AddObject(_camera);
    _transformableObjects.push_back(_groups.back());
    ////////////////////////   TEMPORARY_END   //////////////////////


    _skybox = new SkyBox(200 , QImage(":/skybox2.png"));

    _timer.start(30 , this);
}


void Widget::resizeGL(int width, int height)
{
    float aspect = width / (float)height;

    _projectionMatrix.setToIdentity();
    _projectionMatrix.perspective(45 , aspect , 0.1 , 1000);
}


void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _shaderSkybox.bind();
    _shaderSkybox.setUniformValue("u_projectionMatrix" , _projectionMatrix);
    _camera->Draw(&_shaderSkybox , context()->functions());
    _skybox->Draw(&_shaderSkybox , context()->functions());
    _shaderSkybox.release();


    _renderProgram.bind();
    _renderProgram.setUniformValue("u_projectionMatrix" , _projectionMatrix);
    _renderProgram.setUniformValue("u_lightPosition" , QVector4D(0 , 0 , 0 , 1));
    _renderProgram.setUniformValue("u_lightPower" , 1.0f);

    _camera->Draw(&_renderProgram , context()->functions());

    for (int i = 0 ; i < _transformableObjects.size() ; ++i)
    {
        _transformableObjects[i]->Draw(&_renderProgram , context()->functions());
    }
    _renderProgram.release();
}


void Widget::mousePressEvent(QMouseEvent* event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        _mousePosition = (QVector2D)event->localPos();
    }

    event->accept();
}


void Widget::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() != Qt::LeftButton)
        return;

    QVector2D currentPosition = (QVector2D)event->localPos();

    QVector2D delta = currentPosition - _mousePosition;
    _mousePosition = currentPosition;

    float angle = delta.length() / 2;
    QVector3D rotationVector = QVector3D(delta.y() , delta.x() , 0);

    _camera->Rotate(QQuaternion::fromAxisAndAngle(rotationVector , angle));

    event->accept();
    update();
}


void Widget::wheelEvent(QWheelEvent* event)
{
    float zoomSpeed = 0.25;
    float delta = event->angleDelta().y();

    if (delta < 0)
        zoomSpeed = -zoomSpeed;

    _camera->Translate(0 , 0 , zoomSpeed);

    event->accept();
    update();
}


void Widget::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event);

    for (int i = 0 ; i < _singleObjects.size(); ++i)
    {
        if (i % 2 == 0)
        {
            _singleObjects[i]->Rotate(QQuaternion::fromAxisAndAngle(1 , 0 , 0 , _angObj));
            _singleObjects[i]->Rotate(QQuaternion::fromAxisAndAngle(0 , 1 , 0 , _angObj));
        }
        else
        {
            _singleObjects[i]->Rotate(QQuaternion::fromAxisAndAngle(0 , 1 , 0 , _angObj));
            _singleObjects[i]->Rotate(QQuaternion::fromAxisAndAngle(1 , 0 , 0 , _angObj));
        }
    }

    _groups[0]->Rotate(QQuaternion::fromAxisAndAngle(0 , 1 , 0 , _angGroup1));
    _groups[0]->Rotate(QQuaternion::fromAxisAndAngle(0 , 0 , 1 , _angGroup1));

    _groups[1]->Rotate(QQuaternion::fromAxisAndAngle(1 , 0 , 0 , _angGroup2));
    _groups[1]->Rotate(QQuaternion::fromAxisAndAngle(0 , 1 , 0 , _angGroup2));

    _groups[2]->Rotate(QQuaternion::fromAxisAndAngle(0 , 1 , 0 , _angMain));
    _groups[2]->Rotate(QQuaternion::fromAxisAndAngle(0 , 0 , 1 , _angMain));


    _angObj = ((int)_angObj + 3) % 360;
    _angGroup1 = ((int)_angGroup1 + 2) % 360;
    _angGroup2 = ((int)_angGroup2 + 2) % 360;
    _angMain = ((int)_angMain + 1) % 360;

    update();
}



////////////////////////   TEMPORARY   /////////////////////////
void Widget::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
    case Qt::Key_Left:
    _groups[0]->RemoveObject(_camera);
    _groups[1]->AddObject(_camera);
    break;

    case Qt::Key_Right:
    _groups[1]->RemoveObject(_camera);
    _groups[0]->AddObject(_camera);
    break;

    case Qt::Key_Down:
    _groups[0]->RemoveObject(_camera);
    _groups[1]->RemoveObject(_camera);
    break;
    }
}
////////////////////////   TEMPORARY_END   //////////////////////




void Widget::initShaders()
{
    bool success = tryInitShader(&_renderProgram , ":/vertexShader.vsh" , ":/fragmentShader.fsh");
    success = success && tryInitShader(&_shaderSkybox , ":/skybox_VShader.vsh" , ":/skybox_FShader.fsh");

    if (success == false)
    close();
}


bool Widget::tryInitShader(QOpenGLShaderProgram* program , QString vShaderPath , QString fShaderPath)
{
    bool vShaderSucceeded = program->addShaderFromSourceFile(QOpenGLShader::Vertex , vShaderPath);
    bool fShaderSucceeded = program->addShaderFromSourceFile(QOpenGLShader::Fragment , fShaderPath);
    bool linkSucceeded = program->link();

    return vShaderSucceeded && fShaderSucceeded && linkSucceeded;
}



void Widget::loadObj(const QString& path)
{
    QFile objFile(path);

    QVector<QVector3D> vertexes;
    QVector<QVector3D> normals;
    QVector<QVector2D> texCoord;


    if (objFile.exists() == false)
    {
        qDebug() << "File not found";
        return;
    }

    objFile.open(QIODevice::ReadOnly);
    QTextStream input(&objFile);

    while (input.atEnd() == true)
    {
        QString str = input.readLine();
        QStringList list = str.split(" ");

        QString strCommand = list[0];

        if (strCommand == "v")
        {
            vertexes.push_back(QVector3D(list[1].toFloat() , list[2].toFloat() , list[3].toFloat()));
        }

        else if (strCommand == "vn")
        {
            normals.push_back(QVector3D(list[1].toFloat() , list[2].toFloat() , list[3].toFloat()));
        }

        else if (strCommand == "vt")
        {
            texCoord.push_back(QVector2D(list[1].toFloat() , list[2].toFloat()));
        }

        else if (strCommand == "f")
        {
            texCoord.push_back(QVector2D(list[1].toFloat() , list[2].toFloat()));
        }
    }


    objFile.close();
}

