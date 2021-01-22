#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QMatrix4x4>

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

private:

    QMatrix4x4 _projectionMatrix;
};

#endif // WIDGET_H
