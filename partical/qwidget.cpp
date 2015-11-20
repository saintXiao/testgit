#include "qwidget.h"
  ParticalSystem ps;


qwidget::qwidget(QWidget * parent, const QGLWidget * shareWidget, Qt::WindowFlags f)
{
    setMinimumSize(800, 800);
        resize(640, 480);
        setWindowTitle(tr("The  OPEN_GL_test Program"));

}

qwidget::~qwidget()
{
}
void qwidget::initializeGL()
{
     glShadeModel(GL_SMOOTH);
     //loadGLTextures();
     glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
     glClearDepth(1.0);
     glEnable(GL_DEPTH_TEST);
     glDepthFunc(GL_LEQUAL);
     glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
     glEnableClientState(GL_VERTEX_ARRAY);
     glEnable( GL_TEXTURE_2D);        //Texture
     //glVertexPointer(3, GL_FLOAT, 0, Point);
     glEnable(GL_BLEND);
     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


         //Set the SDL
     ps=ParticalSystem(100,-15.0);
     ps.init();
     //main loop

}
void qwidget::resizeGL(int width, int height)
{
    glViewport( 0, 0, (GLint)width, (GLint)height);
    glMatrixMode( GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( 45.0, (GLfloat)width/(GLfloat)height, 0.1, 100.0);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

}

void qwidget::paintGL()
{

 setCursor(Qt::CrossCursor);
    /* Process incoming events. */

    ps.simulate(0.02,x ,y);
        //Set the OpenGL
       // initGL(SCREEN_WIDTH, SCREEN_HEIGHT );

            /* Draw the screen. */
            glClear(GL_DEPTH_BUFFER_BIT);
               // We don't want to modify the projection matrix. */
               glMatrixMode( GL_MODELVIEW );
               glLoadIdentity( );
               // Move down the z-axis.
               glTranslatef(0.0f,0.0f,-35.0f);
               ps.render();
            //   SDL_GL_SwapBuffers( );
        update();
}

void qwidget::mouseMoveEvent(QMouseEvent *event)
{
    x= event->x()-400;
    y=400- event->y();
    //update();
}
