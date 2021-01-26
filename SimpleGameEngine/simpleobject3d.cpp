#include "simpleobject3d.h"
#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>


void SimpleObject3D::InitFields()
{
    _vertexesBuffer = QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    _indexesBuffer = QOpenGLBuffer(QOpenGLBuffer::Type::IndexBuffer);
    _modelMatrix.setToIdentity();
    _texture = 0;
}



SimpleObject3D::SimpleObject3D()
{
    InitFields();
}


SimpleObject3D::SimpleObject3D(const QVector<VertexData>& vertexData, const QVector<GLuint>& indexData, const QImage& texture)
{
    InitFields();
    Init(vertexData , indexData , texture);
}


void SimpleObject3D::ClearBuffers()
{
    if (_indexesBuffer.isCreated() == true)
        _indexesBuffer.destroy();

    if (_vertexesBuffer.isCreated() == true)
        _vertexesBuffer.destroy();
}


SimpleObject3D::~SimpleObject3D()
{
    ClearBuffers();

    if (_texture != 0)
        if (_texture->isCreated() == true)
            _texture->destroy();
}



void SimpleObject3D::Init(const QVector<VertexData>& vertexData, const QVector<GLuint>& indexData, const QImage& texture)
{
    ClearBuffers();

    if (_texture != 0)
    {
        if (_texture->isCreated() == true)
        {
            delete _texture;
            _texture = 0;

        }
    }

    _vertexesBuffer.create();
    _vertexesBuffer.bind();
    _vertexesBuffer.allocate(vertexData.constData(), vertexData.size() * sizeof (VertexData));
    _vertexesBuffer.release();

    _indexesBuffer.create();
    _indexesBuffer.bind();
    _indexesBuffer.allocate(indexData.constData(), indexData.size() * sizeof (GLuint));
    _indexesBuffer.release();

    _texture = new QOpenGLTexture(texture.mirrored());
    _texture->setMinificationFilter(QOpenGLTexture::Nearest);
    _texture->setMagnificationFilter(QOpenGLTexture::Linear);
    _texture->setWrapMode(QOpenGLTexture::Repeat);

    _modelMatrix.setToIdentity();
}


void SimpleObject3D::Draw(QOpenGLShaderProgram* shaderProgram, QOpenGLFunctions* functions)
{
    if (_vertexesBuffer.isCreated() == false || _indexesBuffer.isCreated() == false)
    {
        return;
    }

    _vertexesBuffer.bind();
    _indexesBuffer.bind();
    _texture->bind(0);

    shaderProgram->setUniformValue("u_texture" , 0);
    shaderProgram->setUniformValue("u_modelMatrix" , _modelMatrix);


    int offset = 0;
    int vertexLoc = shaderProgram->attributeLocation("a_position");
    shaderProgram->enableAttributeArray(vertexLoc);
    shaderProgram->setAttributeBuffer(vertexLoc, GL_FLOAT , offset , 3 , sizeof (VertexData));

    offset += sizeof (QVector3D);

    int textLoc = shaderProgram->attributeLocation("a_textCoord");
    shaderProgram->enableAttributeArray(textLoc);
    shaderProgram->setAttributeBuffer(textLoc, GL_FLOAT , offset , 2 , sizeof (VertexData));

    offset += sizeof (QVector2D);

    int normalLoc = shaderProgram->attributeLocation("a_normal");
    shaderProgram->enableAttributeArray(normalLoc);
    shaderProgram->setAttributeBuffer(normalLoc, GL_FLOAT , offset , 3 , sizeof (VertexData));


    functions->glDrawElements(GL_TRIANGLES , _indexesBuffer.size() , GL_UNSIGNED_INT , 0);


    _vertexesBuffer.release();
    _indexesBuffer.release();
    _texture->release();
}



void SimpleObject3D::Rotate(const QQuaternion& rotation)
{

}


void SimpleObject3D::Translate(const QVector3D& translateVector)
{
    _modelMatrix.translate(translateVector);
}


void SimpleObject3D::Scale(const QVector3D& scaleVector)
{

}




void SimpleObject3D::SetGlobalTransform(QMatrix4x4& globalMatrix)
{

}
