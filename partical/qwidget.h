#ifndef myQWIDGET_H
#define myQWIDGET_H

#include <QtGui>
#include <QtOpenGL>
#include "particalsystem.h"
#include <math.h>
#include<GL/glu.h>
#include<GL/glut.h>

class qwidget : public QGLWidget
{
    Q_OBJECT


public:
    qwidget(QWidget * parent = 0, const QGLWidget * shareWidget = 0, Qt::WindowFlags f = 0);
    ~qwidget();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mouseMoveEvent(QMouseEvent *event);
private:
    int x,y;
};

#endif // myQWIDGET_H
