#include "group3d.h"


Group3D::Group3D()
{
    _globalTransform.setToIdentity();
}


void Group3D::Draw(QOpenGLShaderProgram* program, QOpenGLFunctions* functions)
{
    QMatrix4x4 localMatrix;
    localMatrix.setToIdentity();
    localMatrix.translate(_translation);
    localMatrix.rotate(_rotation);
    localMatrix.scale(_scale);
    localMatrix = _globalTransform * localMatrix;

    for (int i = 0 ; i < _objects.size() ; ++i)
    {
        _objects[i]->SetGlobalTransform(localMatrix);
        _objects[i]->Draw(program , functions);
    }
}



void Group3D::AddObject(TransformableObject* object)
{
    _objects.push_back(object);
}


