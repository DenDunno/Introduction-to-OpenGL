#ifndef CAMERA_H
#define CAMERA_H

#include "transformableobject.h"


class Camera  : public TransformableObject
{
private:

    QMatrix4x4 _viewMatrix;
    QVector3D _eyeDirection = QVector3D(1 , 1 , 1);

public:

    Camera();
    void Draw(QOpenGLShaderProgram* program , QOpenGLFunctions* functions) override;
    void Rotate(const QQuaternion& newRotation) override;


};

#endif // CAMERA_H
