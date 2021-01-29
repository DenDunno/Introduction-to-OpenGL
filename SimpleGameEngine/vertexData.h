#ifndef VERTEXDATA_H
#define VERTEXDATA_H

#include <QVector3D>
#include <QVector2D>

struct VertexData
{
    QVector3D Position;
    QVector2D TexturePosition;
    QVector3D Normal;

    VertexData() { }

    VertexData(QVector3D position , QVector2D texturePosition , QVector3D normal)
    {
        Position = position;
        TexturePosition = texturePosition;
        Normal = normal;
    }
};


#endif // VERTEXDATA_H
