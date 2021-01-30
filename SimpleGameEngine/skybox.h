#ifndef SKYBOX_H
#define SKYBOX_H

#include "transformableobject.h"
#include "vertexData.h"

class SimpleObject3D;

class SkyBox : public TransformableObject
{
private:

    SimpleObject3D* _cube;

    void SetTexture(QVector<VertexData>& vertexes);
    void SetIndexes(QVector<unsigned int>& indexes);

public:

    SkyBox(float width , const QImage& texture);
    ~SkyBox();

    void Draw(QOpenGLShaderProgram* program , QOpenGLFunctions* functions) override;
};

#endif // SKYBOX_H
