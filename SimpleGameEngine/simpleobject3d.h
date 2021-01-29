 #ifndef SIMPLEOBJECT3D_H
#define SIMPLEOBJECT3D_H

#include "transformableobject.h"
#include "vertexData.h"

#include <QOpenGLBuffer>
#include <QMatrix4x4>



class QOpenGLTexture;
class QOpenGLFunctions;
class QOpenGLShaderProgram;



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

    void Bind(const QVector<VertexData>& vertexData, const QVector<GLuint>& indexData, const QImage& texture);
    void Draw(QOpenGLShaderProgram* program , QOpenGLFunctions* functions) override;
    void RebuildMatrix() override;
};

#endif // SIMPLEOBJECT3D_H
