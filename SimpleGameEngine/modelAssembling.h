#ifndef MODELASSEMBLING_H
#define MODELASSEMBLING_H

#include "vertexData.h"
#include <GLES2/gl2.h>
#include <QVector>

typedef  QPair<QVector<VertexData> , QVector<GLuint>> modelData;


modelData GetCubeModelData(float width);


#endif // MODELASSEMBLING_H
