#include <QtGui>
#include  "qwidget.h"
#include  "particalsystem.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QCursor *myCursor= new QCursor(QPixmap(":test.jpg"),-1,-1);
    qwidget myGLWidget;

    myGLWidget.setMouseTracking(true);
    myGLWidget.show();
    return a.exec();
}
