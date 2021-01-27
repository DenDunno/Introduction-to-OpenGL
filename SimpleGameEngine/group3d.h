#ifndef GROUP3D_H
#define GROUP3D_H

#include "transformableobject.h"


class Group3D : public TransformableObject
{

private:

    QVector<TransformableObject* > _objects;

public:

    Group3D();

    void Draw(QOpenGLShaderProgram* program , QOpenGLFunctions* functions) override;
    void AddObject(TransformableObject* object);

};

#endif // GROUP3D_H
