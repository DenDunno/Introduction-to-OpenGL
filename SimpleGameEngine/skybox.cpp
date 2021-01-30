#include "skybox.h"
#include "simpleobject3d.h"
#include "modelAssembling.h"



SkyBox::SkyBox(float width , const QImage& texture)
{
    modelData skyBoxModelData = GetCubeModelData(width);

    SetTexture(skyBoxModelData.first);
    SetIndexes(skyBoxModelData.second);

    for (int i = 0 ; i < skyBoxModelData.first.size() ; ++i)
        skyBoxModelData.first[i].Normal *= -1; // we need to see cube from inside, not outside


    _cube = new SimpleObject3D(skyBoxModelData.first , skyBoxModelData.second , texture);
}


SkyBox::~SkyBox()
{
    delete _cube;
}



void SkyBox::Draw(QOpenGLShaderProgram* program, QOpenGLFunctions* functions)
{
    _cube->Draw(program , functions);
}



void SkyBox::SetTexture(QVector<VertexData>& vertexes)
{
    // Behind
    vertexes[0].TexturePosition  = QVector2D(1.0 , 2.0/3);
    vertexes[1].TexturePosition  = QVector2D(1.0 , 1.0/3);
    vertexes[2].TexturePosition  = QVector2D(3.0/4 , 2.0/3);
    vertexes[3].TexturePosition  = QVector2D(3.0/4 , 1.0/3);
    // Right
    vertexes[4].TexturePosition  = QVector2D(3.0/4 , 2.0/3);
    vertexes[5].TexturePosition  = QVector2D(3.0/4 , 1.0/3);
    vertexes[6].TexturePosition  = QVector2D(2.0/4 , 2.0/3);
    vertexes[7].TexturePosition  = QVector2D(2.0/4 , 1.0/3);
    // Up
    vertexes[8].TexturePosition  = QVector2D(2.0/4 , 1.0);
    vertexes[9].TexturePosition  = QVector2D(2.0/4 , 2.0/3);
    vertexes[10].TexturePosition = QVector2D(1.0/4 , 1.0);
    vertexes[11].TexturePosition = QVector2D(1.0/4 , 2.0/3);
    // Front
    vertexes[12].TexturePosition = QVector2D(2.0/4 , 2.0/3);
    vertexes[13].TexturePosition = QVector2D(2.0/4 , 1.0/3);
    vertexes[14].TexturePosition = QVector2D(1.0/4 , 2.0/3);
    vertexes[15].TexturePosition = QVector2D(1.0/4 , 1.0/3);
    // Left
    vertexes[16].TexturePosition = QVector2D(0.0 , 2.0/3);
    vertexes[17].TexturePosition = QVector2D(1.0/4 , 2.0/3);
    vertexes[18].TexturePosition = QVector2D(0.0 , 1.0/3);
    vertexes[19].TexturePosition = QVector2D(1.0/4 , 1.0/3);
    // Down
    vertexes[20].TexturePosition = QVector2D(1.0/4 , 0.0);
    vertexes[21].TexturePosition = QVector2D(1.0/4 , 1.0/3);
    vertexes[22].TexturePosition = QVector2D(2.0/4 , 0.0);
    vertexes[23].TexturePosition = QVector2D(2.0/4 , 1.0/3);
}


void SkyBox::SetIndexes(QVector<unsigned int>& indexes)
{
    indexes.clear();

    for (int i = 0 ; i < 24 ; i += 4)
    {
        indexes.push_back(i + 0);
        indexes.push_back(i + 2);
        indexes.push_back(i + 1);

        indexes.push_back(i + 2);
        indexes.push_back(i + 3);
        indexes.push_back(i + 1);
    }
}




