#include "modelAssembling.h"


modelData GetCubeModelData(float width)
{
    float widthHalf = width / 2;
    QVector<VertexData> vertexes;
    QVector<GLuint> indexes;

    vertexes.push_back(VertexData(QVector3D(-widthHalf , widthHalf  , widthHalf) , QVector2D(0 , 1) , QVector3D(0 , 0 , 1)));
    vertexes.push_back(VertexData(QVector3D(-widthHalf , -widthHalf , widthHalf) , QVector2D(0 , 0) , QVector3D(0 , 0 , 1)));
    vertexes.push_back(VertexData(QVector3D(widthHalf  , widthHalf  , widthHalf) , QVector2D(1 , 1) , QVector3D(0 , 0 , 1)));
    vertexes.push_back(VertexData(QVector3D(widthHalf  , -widthHalf , widthHalf) , QVector2D(1 , 0) , QVector3D(0 , 0 , 1)));

    vertexes.push_back(VertexData(QVector3D(widthHalf , widthHalf  , widthHalf)  , QVector2D(0 , 1) , QVector3D(1 , 0 , 0)));
    vertexes.push_back(VertexData(QVector3D(widthHalf , -widthHalf , widthHalf)  , QVector2D(0 , 0) , QVector3D(1 , 0 , 0)));
    vertexes.push_back(VertexData(QVector3D(widthHalf , widthHalf  , -widthHalf) , QVector2D(1 , 1) , QVector3D(1 , 0 , 0)));
    vertexes.push_back(VertexData(QVector3D(widthHalf , -widthHalf , -widthHalf) , QVector2D(1 , 0) , QVector3D(1 , 0 , 0)));

    vertexes.push_back(VertexData(QVector3D(widthHalf  , widthHalf , widthHalf)  , QVector2D(0 , 1) , QVector3D(0 , 1 , 0)));
    vertexes.push_back(VertexData(QVector3D(widthHalf  , widthHalf , -widthHalf) , QVector2D(0 , 0) , QVector3D(0 , 1 , 0)));
    vertexes.push_back(VertexData(QVector3D(-widthHalf , widthHalf , widthHalf)  , QVector2D(1 , 1) , QVector3D(0 , 1 , 0)));
    vertexes.push_back(VertexData(QVector3D(-widthHalf , widthHalf , -widthHalf) , QVector2D(1 , 0) , QVector3D(0 , 1 , 0)));

    vertexes.push_back(VertexData(QVector3D(widthHalf  , widthHalf  , -widthHalf) , QVector2D(0 , 1) , QVector3D(0 , 0 , -1)));
    vertexes.push_back(VertexData(QVector3D(widthHalf  , -widthHalf , -widthHalf) , QVector2D(0 , 0) , QVector3D(0 , 0 , -1)));
    vertexes.push_back(VertexData(QVector3D(-widthHalf , widthHalf  , -widthHalf) , QVector2D(1 , 1) , QVector3D(0 , 0 , -1)));
    vertexes.push_back(VertexData(QVector3D(-widthHalf , -widthHalf , -widthHalf) , QVector2D(1 , 0) , QVector3D(0 , 0 , -1)));

    vertexes.push_back(VertexData(QVector3D(-widthHalf , widthHalf  , widthHalf)  , QVector2D(0 , 1) , QVector3D(-1 , 0 , 0)));
    vertexes.push_back(VertexData(QVector3D(-widthHalf , widthHalf  , -widthHalf) , QVector2D(0 , 0) , QVector3D(-1 , 0 , 0)));
    vertexes.push_back(VertexData(QVector3D(-widthHalf , -widthHalf , widthHalf)  , QVector2D(1 , 1) , QVector3D(-1 , 0 , 0)));
    vertexes.push_back(VertexData(QVector3D(-widthHalf , -widthHalf , -widthHalf) , QVector2D(1 , 0) , QVector3D(-1 , 0 , 0)));

    vertexes.push_back(VertexData(QVector3D(-widthHalf , -widthHalf , widthHalf)  , QVector2D(0 , 1) , QVector3D(0 , -1 , 0)));
    vertexes.push_back(VertexData(QVector3D(-widthHalf , -widthHalf , -widthHalf) , QVector2D(0 , 0) , QVector3D(0 , -1 , 0)));
    vertexes.push_back(VertexData(QVector3D(widthHalf  , -widthHalf , widthHalf)  , QVector2D(1 , 1) , QVector3D(0 , -1 , 0)));
    vertexes.push_back(VertexData(QVector3D(widthHalf  , -widthHalf , -widthHalf) , QVector2D(1 , 0) , QVector3D(0 , -1 , 0)));

    for (int i = 0 ; i < 24 ; i += 4)
    {
        indexes.push_back(i + 0);
        indexes.push_back(i + 1);
        indexes.push_back(i + 2);
        indexes.push_back(i + 2);
        indexes.push_back(i + 1);
        indexes.push_back(i + 3);
    }

    return qMakePair(vertexes , indexes);
}
