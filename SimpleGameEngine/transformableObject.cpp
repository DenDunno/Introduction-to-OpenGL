#include "transformableobject.h"


TransformableObject::TransformableObject()
{
    _matrix.setToIdentity();
    _globalTransform.setToIdentity();
}

TransformableObject::~TransformableObject()
{
}



void TransformableObject::SetGlobalTransform(QMatrix4x4& globalMatrix)
{
    _globalTransform = globalMatrix;
    RebuildMatrix();
}


void TransformableObject::Rotate(const QQuaternion& newRotation)
{
    _rotation = newRotation;
    RebuildMatrix();
}


void TransformableObject::Translate(const float translate_X, const float translate_Y, const float translate_Z)
{
    _translation += QVector3D(translate_X , translate_Y , translate_Z);
    RebuildMatrix();
}


void TransformableObject::Scale(const float scale_X, const float scale_Y, const float scale_Z)
{
    _scale = QVector3D(scale_X , scale_Y , scale_Z);
    RebuildMatrix();
}




void TransformableObject::RebuildMatrix()
{
    _matrix.setToIdentity();
    _matrix.translate(_translation.toVector3D());
    _matrix.rotate(_rotation);
    _matrix.scale(_scale);
}
