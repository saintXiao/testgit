#include <QtGui>
#include "glhuaxian.h"
#include<GL/glut.h>

int main(int argc, char *argv[])
{
    glutInit(& argc , argv);
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    MyGLWidget myGLWidget;
    QCursor *myCursor= new QCursor(QPixmap(":test.jpg"),-1,-1);
    myGLWidget.setMouseTracking(true);
    myGLWidget.show();
    return a.exec();
}
