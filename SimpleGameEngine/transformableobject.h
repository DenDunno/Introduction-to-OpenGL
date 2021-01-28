#ifndef TRANSFORMABLEOBJECT_H
#define TRANSFORMABLEOBJECT_H

#include<QQuaternion>
#include<QMatrix4x4>

class QOpenGLShaderProgram;
class QOpenGLFunctions;


class TransformableObject
{
protected:

    QQuaternion _rotation = QQuaternion(0 , QVector3D(0 , 0 , 1));
    QVector4D _translation = QVector4D(0 , 0 , 0 , 0);
    QVector3D _scale = QVector3D(1 , 1 , 1);

    QMatrix4x4 _globalTransform;

public:

     virtual void Draw(QOpenGLShaderProgram* program , QOpenGLFunctions* functions) = 0;

     virtual void Rotate(const QQuaternion& newRotation);
     virtual void Translate(const QVector3D& translateVector);
     virtual void Scale(const QVector3D& scaleVector);

     void SetGlobalTransform(QMatrix4x4& globalMatrix);
};




#endif // TRANSFORMABLEOBJECT_H
