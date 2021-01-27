#include "transformableobject.h"


void TransformableObject::SetGlobalTransform(QMatrix4x4& globalMatrix)
{
    _globalTransform = globalMatrix;
}



void TransformableObject::Rotate(const QQuaternion& rotation)
{
    _rotation = rotation;
}


void TransformableObject::Translate(const QVector3D& translateVector)
{
    _translation += translateVector;
}


void TransformableObject::Scale(const QVector3D& scaleVector)
{
    _scale = scaleVector;
}
