#include "skybox.h"
#include "simpleobject3d.h"

SkyBox::SkyBox(const QImage& texture)
{
    Q_UNUSED(texture);
    _matrix.setToIdentity(); // model matrix
    _globalTransform.setToIdentity();
}


void SkyBox::Draw(QOpenGLShaderProgram* program, QOpenGLFunctions* functions)
{
    _cube->Draw(program , functions);
}
