#ifndef SKYBOX_H
#define SKYBOX_H

#include "transformableobject.h"

class SimpleObject3D;

class SkyBox : public TransformableObject
{
private:

    SimpleObject3D* _cube;

public:

    SkyBox(const QImage& texture);

    void Draw(QOpenGLShaderProgram* program , QOpenGLFunctions* functions) override;
};

#endif // SKYBOX_H
