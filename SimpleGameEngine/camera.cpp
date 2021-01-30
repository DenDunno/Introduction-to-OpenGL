#include "camera.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QMatrix4x4>

Camera::Camera()
{
    _translation = QVector3D(0 , 0, -10);
}


void Camera::Draw(QOpenGLShaderProgram* program, QOpenGLFunctions* functions)
{
    Q_UNUSED(functions);

    program->setUniformValue("u_viewMatrix" , _matrix);
}


void Camera::RebuildMatrix()
{
    TransformableObject::RebuildMatrix();

    _matrix = _matrix * _globalTransform.inverted();
}


void Camera::Rotate(const QQuaternion& newRotation)
{
    _rotation = newRotation * _rotation;
    RebuildMatrix();
}


