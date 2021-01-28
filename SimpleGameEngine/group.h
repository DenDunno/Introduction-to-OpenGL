#ifndef GROUP_H
#define GROUP_H

#include "transformableobject.h"


class Group : public TransformableObject
{

private:

    QVector<TransformableObject* > _objects;

public:

    Group();

    void Draw(QOpenGLShaderProgram* program , QOpenGLFunctions* functions) override;
    void RebuildMatrix() override;

    void AddObject(TransformableObject* object);
    void RemoveObject(TransformableObject* object);
    void RemoveObject(const int index);


};

#endif // GROUP_H
