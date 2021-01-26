#ifndef TRANSFORMABLEOBJECT_H
#define TRANSFORMABLEOBJECT_H

class QQuaternion;
class QVector3D;
class QMatrix4x4;
class QOpenGLShaderProgram;
class QOpenGLFunctions;


class TransformableObject
{
public:

    virtual void SetGlobalTransform(QMatrix4x4& globalMatrix) = 0;
    virtual void Draw(QOpenGLShaderProgram* program , QOpenGLFunctions* functions) = 0;

    virtual void Rotate(const QQuaternion& rotation) = 0;
    virtual void Translate(const QVector3D& translateVector) = 0;
    virtual void Scale(const QVector3D& scaleVector) = 0;
};

#endif // TRANSFORMABLEOBJECT_H
