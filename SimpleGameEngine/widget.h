#ifndef WIDGET_H
#define WIDGET_H
#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QBasicTimer>


class SimpleObject3D;
class Group;
class TransformableObject;
class Camera;


class Widget : public QOpenGLWidget
{
    Q_OBJECT

private:

    QVector<SimpleObject3D* > _singleObjects;
    QVector<Group* > _groups;
    QVector<TransformableObject* > _transformableObjects;

    QOpenGLShaderProgram _renderProgram;

    Camera* _camera;
    QMatrix4x4 _projectionMatrix;
    QVector2D _mousePosition;

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
    void keyPressEvent(QKeyEvent* event);

    void initShaders();
    void initCube(float width);


public:

    Widget(QWidget *parent = 0);

};

#endif // WIDGET_H
