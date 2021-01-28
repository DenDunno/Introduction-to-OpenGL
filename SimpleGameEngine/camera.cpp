#include "camera.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QMatrix4x4>

Camera::Camera()
{
    _viewMatrix.setToIdentity();
    _translation = QVector3D(0 , 0, 10);
}


void Camera::Draw(QOpenGLShaderProgram* program, QOpenGLFunctions* functions)
{
    Q_UNUSED(functions);

    _viewMatrix.setToIdentity();
    _viewMatrix.translate(_translation.toVector3D());
    _viewMatrix.rotate(_rotation);
    _viewMatrix.scale(_scale);
    _viewMatrix = _viewMatrix.inverted();


    program->setUniformValue("u_viewMatrix" , _viewMatrix);
}


void Camera::Rotate(const QQuaternion& newRotation)
{
    _rotation = newRotation * _rotation;
    QMatrix4x4 rotationMatrix = QMatrix4x4(_rotation.toRotationMatrix());

    _eyeDirection = rotationMatrix * _eyeDirection;
}

