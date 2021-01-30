#include "group.h"

Group::~Group()
{
    for (int i = 0 ; i < _objects.size() ; ++i)
    {
        delete _objects[i];
    }
}


void Group::Draw(QOpenGLShaderProgram* program, QOpenGLFunctions* functions)
{    
    for (int i = 0 ; i < _objects.size() ; ++i)
    {
        _objects[i]->Draw(program , functions);
    }
}


void Group::RebuildMatrix()
{
    TransformableObject::RebuildMatrix();

    _matrix = _globalTransform * _matrix;

    for (int i = 0 ; i < _objects.size() ; ++i)
    {
        _objects[i]->SetGlobalTransform(_matrix);
    }
}



void Group::AddObject(TransformableObject* object)
{
    _objects.push_back(object);

    TransformableObject::RebuildMatrix();
    _matrix = _globalTransform * _matrix;
    _objects.back()->SetGlobalTransform(_matrix);
}


void Group::RemoveObject(TransformableObject* object)
{
    _objects.removeAll(object);
}


void Group::RemoveObject(const int index)
{
    _objects.remove(index);
}


