#ifndef GLHUAXIAN_H
#define GLHUAXIAN_H

#include <QtGui>
#include <QtOpenGL>

class MyGLWidget : public QGLWidget
{
    Q_OBJECT

public:
    MyGLWidget(QWidget * parent = 0, const QGLWidget * shareWidget = 0, Qt::WindowFlags f = 0);
    ~MyGLWidget();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    //void mouseMoveEvent( QMouseEvent * event );
    void loadGLTextures();


private:
    int x,y;
    GLuint texture[6];


};
#endif // GLHUAXIAN_H
