#ifndef TRANSFORMABLEOBJECT_H
#define TRANSFORMABLEOBJECT_H

#include<QQuaternion>
#include<QMatrix4x4>

class QOpenGLShaderProgram;
class QOpenGLFunctions;


class TransformableObject
{
protected:

    QMatrix4x4 _matrix;
    /*
     * In Camera = view matrix
     * In SimpleObject3D = model matrix
     * In Group = local matrix
     */

    QQuaternion _rotation = QQuaternion(0 , QVector3D(0 , 0 , 1));
    QVector4D _translation = QVector4D(0 , 0 , 0 , 0);
    QVector3D _scale = QVector3D(1 , 1 , 1);

    QMatrix4x4 _globalTransform;

public:

     TransformableObject();
     virtual ~TransformableObject();

     virtual void Draw(QOpenGLShaderProgram* program , QOpenGLFunctions* functions) = 0;
     virtual void RebuildMatrix();

     virtual void Rotate(const QQuaternion& newRotation);
     virtual void Translate(const float translate_X , const float translate_Y , const float translate_Z);
     virtual void Scale(const float scale_X , const float scale_Y , const float scale_Z);

     void SetGlobalTransform(QMatrix4x4& globalMatrix);
};


#endif // TRANSFORMABLEOBJECT_H
