#include "widget.h"

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

    QMatrix4x4 cubeModelViewMatrix;
    cubeModelViewMatrix.setToIdentity();// камера установлена в 0, видовая матрица = E
    cubeModelViewMatrix.translate(0 , 0 , -5);
    cubeModelViewMatrix.rotate(30 , 1 , 0 , 0);
    cubeModelViewMatrix.rotate(30 , 0 , 1 , 0);


    _texture->bind(0);

    _renderProgram.bind();
    _renderProgram.setUniformValue("qt_ModelViewProjectionMatrix" , _projectionMatrix * cubeModelViewMatrix);
    _renderProgram.setUniformValue("qt_Texture0" , 0);

    _arrayBuffer.bind();


    int offset = 0;

    int vertexLoc = _renderProgram.attributeLocation("qt_Vertex");
    _renderProgram.enableAttributeArray(vertexLoc);
    _renderProgram.setAttributeBuffer(vertexLoc, GL_FLOAT , offset , 3 , sizeof (VertexData));

    offset += sizeof (QVector3D);

    int textLoc = _renderProgram.attributeLocation("qt_MultiTexCoord0");
    _renderProgram.enableAttributeArray(textLoc);
    _renderProgram.setAttributeBuffer(textLoc, GL_FLOAT , offset , 2 , sizeof (VertexData));

    _indexBuffer.bind();

    glDrawElements(GL_TRIANGLES , _indexBuffer.size() , GL_UNSIGNED_INT , nullptr);
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

