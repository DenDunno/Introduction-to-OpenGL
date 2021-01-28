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

    QOpenGLBuffer _vertexesBuffer;
    QOpenGLBuffer _indexesBuffer;
    QOpenGLTexture* _texture = 0;

    void Clear();

public:

    SimpleObject3D();
    SimpleObject3D(const QVector<VertexData>& vertexData, const QVector<GLuint>& indexData, const QImage& texture);
   ~SimpleObject3D();

    void Init(const QVector<VertexData>& vertexData, const QVector<GLuint>& indexData, const QImage& texture);
    void Draw(QOpenGLShaderProgram* program , QOpenGLFunctions* functions) override;
    void RebuildMatrix() override;
};

#endif // SIMPLEOBJECT3D_H
