#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QBasicTimer>


class SimpleObject3D;
class Group3D;
class TransformableObject;


class Widget : public QOpenGLWidget
{
    Q_OBJECT

private:

    QVector<SimpleObject3D* > _singleObjects;
    QVector<Group3D* > _groups;
    QVector<TransformableObject* > _transformableObjects;

    QOpenGLShaderProgram _renderProgram;

    QMatrix4x4 _projectionMatrix;
    QVector2D _mousePosition;
    QQuaternion _rotation;

    float _viewMatrix_Z;

    QBasicTimer _timer;
    float angObj;
    float angGroup1;
    float angGroup2;
    float angMain;

protected:

    void initializeGL();
    void resizeGL(int width , int height);
    void paintGL();

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void timerEvent(QTimerEvent* event);

    void initShaders();
    void initCube(float width);


public:

    Widget(QWidget *parent = 0);

};

#endif // WIDGET_H
