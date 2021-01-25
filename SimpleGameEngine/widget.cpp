#include "widget.h"

#include <QMouseEvent>

Widget::Widget(QWidget *parent): QOpenGLWidget(parent)
{
    _texture = nullptr;
    _indexBuffer = QOpenGLBuffer(QOpenGLBuffer::Type::IndexBuffer);
    _arrayBuffer = QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
}

Widget::~Widget()
{
}



void Widget::initializeGL()
{
    glClearColor(0.0 , 0.0 , 0.0 , 1.0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    initShaders();

    initCube(1);
}


void Widget::resizeGL(int width, int height)
{
    float aspect = width / (float)height;

    _projectionMatrix.setToIdentity();
    _projectionMatrix.perspective(45 , aspect , 0.1 , 10);
}


void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity(); // камера установлена в 0, видовая матрица = E
    modelMatrix.translate(0 , 0 , -2.5);
    modelMatrix.rotate(_rotation);


    QMatrix4x4 viewMatrix;
    viewMatrix.setToIdentity();

    _texture->bind(0);

    _renderProgram.bind();
    _renderProgram.setUniformValue("u_projectionMatrix" , _projectionMatrix);
    _renderProgram.setUniformValue("u_modelMatrix" , modelMatrix);
    _renderProgram.setUniformValue("u_viewMatrix" , viewMatrix);
    _renderProgram.setUniformValue("u_texture" , 0);
    _renderProgram.setUniformValue("u_lightPosition" , QVector4D(0 , 0 , 0 , 1));
    _renderProgram.setUniformValue("u_lightPower" , 5.0f);

    _arrayBuffer.bind();


    int offset = 0;

    int vertexLoc = _renderProgram.attributeLocation("a_position");
    _renderProgram.enableAttributeArray(vertexLoc);
    _renderProgram.setAttributeBuffer(vertexLoc, GL_FLOAT , offset , 3 , sizeof (VertexData));

    offset += sizeof (QVector3D);

    int textLoc = _renderProgram.attributeLocation("a_textCoord");
    _renderProgram.enableAttributeArray(textLoc);
    _renderProgram.setAttributeBuffer(textLoc, GL_FLOAT , offset , 2 , sizeof (VertexData));


    offset += sizeof (QVector2D);

    int normalLoc = _renderProgram.attributeLocation("a_normal");
    _renderProgram.enableAttributeArray(normalLoc);
    _renderProgram.setAttributeBuffer(normalLoc, GL_FLOAT , offset , 3 , sizeof (VertexData));


    _indexBuffer.bind();

    glDrawElements(GL_TRIANGLES , _indexBuffer.size() , GL_UNSIGNED_INT , nullptr);
}



void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        _mousePosition = (QVector2D)event->localPos();
    }

    event->accept();
}


void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() != Qt::LeftButton)
        return;

    QVector2D currentPosition = (QVector2D)event->localPos();

    QVector2D delta = currentPosition - _mousePosition;
    _mousePosition = currentPosition;

    float angle = delta.length() / 2;
    QVector3D rotationVector = QVector3D(delta.y() , delta.x() , 0);

    _rotation = QQuaternion::fromAxisAndAngle(rotationVector , angle) * _rotation;

    update();
}




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

    _arrayBuffer.create();
    _arrayBuffer.bind();
    _arrayBuffer.allocate(vertexes.constData() , vertexes.size() * sizeof(VertexData));
    _arrayBuffer.release();

    _indexBuffer.create();
    _indexBuffer.bind();
    _indexBuffer.allocate(indexes.constData() , indexes.size() * sizeof(GLuint));
    _indexBuffer.release();

    _texture = new QOpenGLTexture(QImage(":/wood.png").mirrored());

    _texture->setMinificationFilter(QOpenGLTexture::Nearest);
    _texture->setMagnificationFilter(QOpenGLTexture::Linear);
    _texture->setWrapMode(QOpenGLTexture::Repeat);

}

