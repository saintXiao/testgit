#include "glhuaxian.h"

#include <QtGui>
#include <QtOpenGL>
#include <math.h>
#include<GL/glu.h>
#include<GL/glut.h>




MyGLWidget::MyGLWidget(QWidget * parent, const QGLWidget * shareWidget, Qt::WindowFlags f)
{
    setMinimumSize(320, 240);
    resize(640, 480);
    setWindowTitle(tr("The first OPEN_GL Program"));


    short angle = 18;
    const GLfloat PI = 3.1415926536f;
    /*for(short i=0;i<5; i++)
    {


        Point[i][0] = cos (angle * PI/180);
        Point[i][1] = sin (angle * PI/180);
        Point[i][2] = 0.0;
        angle += 72;
    }*/
}

MyGLWidget::~MyGLWidget()
{
}


void MyGLWidget::initializeGL()
{
     glShadeModel(GL_SMOOTH);
     loadGLTextures();
     glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
     glClearDepth(1.0);
     glEnable(GL_DEPTH_TEST);
     glDepthFunc(GL_LEQUAL);
     glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
     glEnableClientState(GL_VERTEX_ARRAY);
     glEnable( GL_TEXTURE_2D);        //Texture
     //glVertexPointer(3, GL_FLOAT, 0, Point);
}

void MyGLWidget::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef( 0.0, 0.0, -6.0 );
    glBindTexture(GL_TEXTURE_2D, texture[0]);//绑定纹理目标
       glBegin(GL_QUADS);
           glTexCoord2f( 0.0, 0.0 ); glVertex3f( -2.0, -2.0,  1.0 );
           glTexCoord2f( 1.0, 0.0 ); glVertex3f(  2.0, -2.0,  1.0 );
           glTexCoord2f( 1.0, 1.0 ); glVertex3f(  2.0,  2.0,  1.0 );
           glTexCoord2f( 0.0, 1.0 ); glVertex3f( -2.0,  2.0,  1.0 );
       glEnd();






}

void MyGLWidget::resizeGL(int width, int height)
{
    glViewport( 0, 0, (GLint)width, (GLint)height);
    glMatrixMode( GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( 45.0, (GLfloat)width/(GLfloat)height, 0.1, 100.0);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

}

/*void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    x = event->x();
    y = event->y();
    pixmap.fill(QColor(255,255,255,127));
    QPainter painter(&pixmap);
    painter.setPen(QColor(255,0,0));
    painter.drawText(20, 40, QString("%1").arg(x) + "," +
        QString("%1").arg(y));
    update();
}*/

void MyGLWidget::loadGLTextures()
{
    QImage tex, buf;
           if(!buf.load("test.jpg"))//这个时候因为debug没有在外面，所以图片文件夹就是本目录了
           {
               qWarning("Cannot open the image...");
               QImage dummy(128, 128, QImage::Format_RGB32);//当没找到所需打开的图片时，创建一副128*128大小，深度为32位的位图
               dummy.fill(Qt::green);
               buf = dummy;
           }
           tex = convertToGLFormat(buf);//将Qt图片的格式buf转换成opengl的图片格式tex
           glGenTextures(1, &texture[0]);//开辟3个纹理内存，索引指向texture[0]

           /*建立第一个纹理*/
           glBindTexture(GL_TEXTURE_2D, texture[0]);//将创建的纹理内存指向的内容绑定到纹理对象GL_TEXTURE_2D上，经过这句代码后，以后对
                                                   //GL_TEXTURE_2D的操作的任何操作都同时对应与它所绑定的纹理对象
           glTexImage2D(GL_TEXTURE_2D, 0, 3, tex.width(), tex.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());//开始真正创建纹理数据
           glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//当所显示的纹理比加载进来的纹理小时，采用GL_NEAREST的方法来处理
                                                                             //GL_NEAREST方式速度非常快，因为它不是真正的滤波，所以占用内存非常
                                                                             // 小，速度就快了
           glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//当所显示的纹理比加载进来的纹理大时，采用GL_NEAREST的方法来处理
}

