#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>


class SimpleObject3D;


class Widget : public QOpenGLWidget
{
    Q_OBJECT

public:

    Widget(QWidget *parent = 0);

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

    QVector2D _mousePosition;
    QQuaternion _rotation;

    QVector<SimpleObject3D* > _objects;
};

#endif // WIDGET_H
