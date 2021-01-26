 #ifndef SIMPLEOBJECT3D_H
#define SIMPLEOBJECT3D_H

#include "transformableobject.h"
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include<QVector2D>


class QOpenGLTexture;
class QOpenGLFunctions;
class QOpenGLShaderProgram;

struct VertexData
{
    QVector3D Position;
    QVector2D TexturePosition;
    QVector3D Normal;

    VertexData() { }

    VertexData(QVector3D position , QVector2D texturePosition , QVector3D normal)
    {
        Position = position;
        TexturePosition = texturePosition;
        Normal = normal;
    }
};



class SimpleObject3D : public TransformableObject
{
private:

    QQuaternion _rotation;
    QVector3D _translation;
    QVector3D _scale;

    QMatrix4x4 _modelMatrix;
    QMatrix4x4 _globalTransform;

    QOpenGLBuffer _vertexesBuffer;
    QOpenGLBuffer _indexesBuffer;
    QOpenGLTexture* _texture;

    void ClearBuffers();
    void InitFields();

public:

    SimpleObject3D();
    SimpleObject3D(const QVector<VertexData>& vertexData, const QVector<GLuint>& indexData, const QImage& texture);
   ~SimpleObject3D();

    void Init(const QVector<VertexData>& vertexData, const QVector<GLuint>& indexData, const QImage& texture);
    void Draw(QOpenGLShaderProgram* program , QOpenGLFunctions* functions);

    void Rotate(const QQuaternion& rotation);
    void Translate(const QVector3D& translateVector);
    void Scale(const QVector3D& scaleVector);

    void SetGlobalTransform(QMatrix4x4& globalMatrix);
};

#endif // SIMPLEOBJECT3D_H
