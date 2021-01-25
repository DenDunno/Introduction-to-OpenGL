#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>


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



class Widget : public QOpenGLWidget
{
    Q_OBJECT

public:

    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:

    void initializeGL();
    void resizeGL(int width , int height);
    void paintGL();

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

    void initShaders();
    void initCube(float width);

private:

    QMatrix4x4 _projectionMatrix;
    QOpenGLShaderProgram _renderProgram;
    QOpenGLTexture* _texture;
    QOpenGLBuffer _arrayBuffer;
    QOpenGLBuffer _indexBuffer;

    QVector2D _mousePosition;
    QQuaternion _rotation;
};

#endif // WIDGET_H
