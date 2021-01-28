#include "widget.h"
#include"simpleobject3d.h"
#include "group.h"
#include "camera.h"

#include <QMouseEvent>
#include <QOpenGLContext>
#include <QtMath>
#include <QKeyEvent>


Widget::Widget(QWidget *parent): QOpenGLWidget(parent)
{
    _camera = new Camera();
}


void Widget::initializeGL()
{
    glClearColor(0.0 , 0.0 , 0.0 , 1.0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    initShaders();


    ////////////////////////   TEMPORARY   /////////////////////////

    float step = 2.0f;

    _groups.push_back(new Group());

    for (int x = -step ; x <= step ; x += step)
    {
        for (int y = -step ; y <= step ; y += step)
        {
            for (int z = -step ; z <= step ; z += step)
            {
                initCube(1);
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
                initCube(1);
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


    _timer.start(30 , this);
}


void Widget::resizeGL(int width, int height)
{
    float aspect = width / (float)height;

    _projectionMatrix.setToIdentity();
    _projectionMatrix.perspective(45 , aspect , 0.1 , 100);
}


void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _renderProgram.bind();
    _renderProgram.setUniformValue("u_projectionMatrix" , _projectionMatrix);
    _renderProgram.setUniformValue("u_lightPosition" , QVector4D(0 , 0 , 0 , 1));
    _renderProgram.setUniformValue("u_lightPower" , 1.0f);

    _camera->Draw(&_renderProgram , context()->functions());
    for (int i = 0 ; i < _transformableObjects.size() ; ++i)
    {
        _transformableObjects[i]->Draw(&_renderProgram , context()->functions());
    }
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
            _singleObjects[i]->Rotate(QQuaternion::fromAxisAndAngle(1 , 0 , 0 , angObj));
            _singleObjects[i]->Rotate(QQuaternion::fromAxisAndAngle(0 , 1 , 0 , angObj));
        }
        else
        {
            _singleObjects[i]->Rotate(QQuaternion::fromAxisAndAngle(0 , 1 , 0 , angObj));
            _singleObjects[i]->Rotate(QQuaternion::fromAxisAndAngle(1 , 0 , 0 , angObj));
        }
    }

    _groups[0]->Rotate(QQuaternion::fromAxisAndAngle(0 , 1 , 0 , angGroup1));
    _groups[0]->Rotate(QQuaternion::fromAxisAndAngle(0 , 0 , 1 , angGroup1));

    _groups[1]->Rotate(QQuaternion::fromAxisAndAngle(1 , 0 , 0 , angGroup2));
    _groups[1]->Rotate(QQuaternion::fromAxisAndAngle(0 , 1 , 0 , angGroup2));

    _groups[2]->Rotate(QQuaternion::fromAxisAndAngle(0 , 1 , 0 , angMain));
    _groups[2]->Rotate(QQuaternion::fromAxisAndAngle(0 , 0 , 1 , angMain));


    angObj = ((int)angObj + 3) % 360;
    angGroup1 = ((int)angGroup1 + 2) % 360;
    angGroup2 = ((int)angGroup2 + 2) % 360;
    angMain = ((int)angMain + 1) % 360;

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
    bool vShaderSucceeded = _renderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex , ":/vertexShader.vsh");
    bool fShaderSucceeded = _renderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment , ":/fragmentShader.fsh");
    bool linkSucceeded = _renderProgram.link();

    if (vShaderSucceeded && fShaderSucceeded && linkSucceeded == false)
        close();
}


void Widget::initCube(float width)
{
    float widthHalf = width / 2;
    QVector<VertexData> vertexes;
    QVector<GLuint> indexes;

    vertexes.push_back(VertexData(QVector3D(-widthHalf , widthHalf  , widthHalf) , QVector2D(0 , 1) , QVector3D(0 , 0 , 1)));
    vertexes.push_back(VertexData(QVector3D(-widthHalf , -widthHalf , widthHalf) , QVector2D(0 , 0) , QVector3D(0 , 0 , 1)));
    vertexes.push_back(VertexData(QVector3D(widthHalf  , widthHalf  , widthHalf) , QVector2D(1 , 1) , QVector3D(0 , 0 , 1)));
    vertexes.push_back(VertexData(QVector3D(widthHalf  , -widthHalf , widthHalf) , QVector2D(1 , 0) , QVector3D(0 , 0 , 1)));

    vertexes.push_back(VertexData(QVector3D(widthHalf , widthHalf  , widthHalf)  , QVector2D(0 , 1) , QVector3D(1 , 0 , 0)));
    vertexes.push_back(VertexData(QVector3D(widthHalf , -widthHalf , widthHalf)  , QVector2D(0 , 0) , QVector3D(1 , 0 , 0)));
    vertexes.push_back(VertexData(QVector3D(widthHalf , widthHalf  , -widthHalf) , QVector2D(1 , 1) , QVector3D(1 , 0 , 0)));
    vertexes.push_back(VertexData(QVector3D(widthHalf , -widthHalf , -widthHalf) , QVector2D(1 , 0) , QVector3D(1 , 0 , 0)));

    vertexes.push_back(VertexData(QVector3D(widthHalf  , widthHalf , widthHalf)  , QVector2D(0 , 1) , QVector3D(0 , 1 , 0)));
    vertexes.push_back(VertexData(QVector3D(widthHalf  , widthHalf , -widthHalf) , QVector2D(0 , 0) , QVector3D(0 , 1 , 0)));
    vertexes.push_back(VertexData(QVector3D(-widthHalf , widthHalf , widthHalf)  , QVector2D(1 , 1) , QVector3D(0 , 1 , 0)));
    vertexes.push_back(VertexData(QVector3D(-widthHalf , widthHalf , -widthHalf) , QVector2D(1 , 0) , QVector3D(0 , 1 , 0)));

    vertexes.push_back(VertexData(QVector3D(widthHalf  , widthHalf  , -widthHalf) , QVector2D(0 , 1) , QVector3D(0 , 0 , -1)));
    vertexes.push_back(VertexData(QVector3D(widthHalf  , -widthHalf , -widthHalf) , QVector2D(0 , 0) , QVector3D(0 , 0 , -1)));
    vertexes.push_back(VertexData(QVector3D(-widthHalf , widthHalf  , -widthHalf) , QVector2D(1 , 1) , QVector3D(0 , 0 , -1)));
    vertexes.push_back(VertexData(QVector3D(-widthHalf , -widthHalf , -widthHalf) , QVector2D(1 , 0) , QVector3D(0 , 0 , -1)));

    vertexes.push_back(VertexData(QVector3D(-widthHalf , widthHalf  , widthHalf)  , QVector2D(0 , 1) , QVector3D(-1 , 0 , 0)));
    vertexes.push_back(VertexData(QVector3D(-widthHalf , widthHalf  , -widthHalf) , QVector2D(0 , 0) , QVector3D(-1 , 0 , 0)));
    vertexes.push_back(VertexData(QVector3D(-widthHalf , -widthHalf , widthHalf)  , QVector2D(1 , 1) , QVector3D(-1 , 0 , 0)));
    vertexes.push_back(VertexData(QVector3D(-widthHalf , -widthHalf , -widthHalf) , QVector2D(1 , 0) , QVector3D(-1 , 0 , 0)));

    vertexes.push_back(VertexData(QVector3D(-widthHalf , -widthHalf , widthHalf)  , QVector2D(0 , 1) , QVector3D(0 , -1 , 0)));
    vertexes.push_back(VertexData(QVector3D(-widthHalf , -widthHalf , -widthHalf) , QVector2D(0 , 0) , QVector3D(0 , -1 , 0)));
    vertexes.push_back(VertexData(QVector3D(widthHalf  , -widthHalf , widthHalf)  , QVector2D(1 , 1) , QVector3D(0 , -1 , 0)));
    vertexes.push_back(VertexData(QVector3D(widthHalf  , -widthHalf , -widthHalf) , QVector2D(1 , 0) , QVector3D(0 , -1 , 0)));


    for (int i = 0 ; i < 24 ; i += 4)
    {
        indexes.push_back(i + 0);
        indexes.push_back(i + 1);
        indexes.push_back(i + 2);
        indexes.push_back(i + 2);
        indexes.push_back(i + 1);
        indexes.push_back(i + 3);
    }

    _singleObjects.push_back(new SimpleObject3D(vertexes , indexes , QImage(":/wood.png")));
}

