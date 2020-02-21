#include "opengl3dwidget.h"
#include <QTimer>
#include <math.h>
#include <QMouseEvent>
#include <QGLWidget>
#include <QDebug>


OpenGL3DWidget::OpenGL3DWidget(QWidget *parent)
{
    qDebug() << "Create";
   xRot=yRot=zRot=0.0f;
   timer=new QTimer(this); //타이머 생성
      timer->setInterval(20); //0.01초 간격으로 타이머 발생
      connect(timer,SIGNAL(timeout()),this,SLOT(timerFunction())); //타이머와 함수를 연결
      timer->start(); //타이머 시작
}
OpenGL3DWidget::~OpenGL3DWidget()
{

}
void OpenGL3DWidget::initializeGL() //GL 초기화
{
    initializeOpenGLFunctions();
        glEnable(GL_DEPTH_TEST); //깊이값 반영
}

void OpenGL3DWidget::resizeGL(int w, int h) //위젯 크기 변했을때
{
    qDebug() << "resizeGL";
    GLfloat aspectRatio; //화면 비율

    if(h==0)
        h=1;

    glViewport(0,0,w,h); //뷰포트 설정

    glMatrixMode(GL_PROJECTION); //행렬모드지정
    glLoadIdentity(); //좌표계 초기화

    aspectRatio=(GLfloat)w/(GLfloat)h; //화면비율 지정
    if(w<=h)
    {
        windowWidth=1;
        windowHeight=1/aspectRatio;
        glFrustum(-1.0,1.0,-windowHeight,windowHeight,5.0,300.0);//3D
        //glOrtho(-100.0,100.0,-windowHeight,windowHeight,1.0,-1.0);//2D
    }
    else
    {
        windowWidth=1*aspectRatio;
        windowHeight=1;
        glFrustum(-windowWidth,windowWidth,-1.0,1.0,5.0,3000.0);
        //glOrtho(-windowWidth,windowWidth,-100.0,100.0,1.0,-1.0);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void OpenGL3DWidget::paintGL() //실제 그리는 함수
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
       glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //화면을 지워준다.

       glMatrixMode(GL_MODELVIEW);
       glLoadIdentity();
       glTranslatef(0.0f,0.0f,-1500.0f); //move along z-axis// 카메라 이동

       glRotatef(xRot,1.0,0.0,0.0);
       glRotatef(yRot,0.0,1.0,0.0);
       glRotatef(zRot,0.0,0.0,1.0);

       glLineWidth(10.0);
       glBegin(GL_LINE_LOOP);
           glColor3f(1.f,0.f,0.f);
           glVertex3f(0.0, 0.0, 0.0);
           glVertex3f(-400.0, 0.0, 0.0);
       glEnd();

       glBegin(GL_LINE_LOOP);
           glColor3f(0.f,1.f,0.f);
           glVertex3f(0.0, 0.0, 0.0);
           glVertex3f(0.0, -400.0, 0.0);
       glEnd();

       glBegin(GL_LINE_LOOP);
           glColor3f(0.f,0.f,1.f);
           glVertex3f(0.0, 0.0, 0.0);
           glVertex3f(0.0, 0.0, -400.0);
       glEnd();

       /* create 3D-Cube */
        glBegin(GL_QUADS); //사각형
           //front
           glColor3f(1.0,0.0,0.0);
           glVertex3f(101.0,51.0,101.0);
           glVertex3f(-101.0,51.0,101.0);
           glVertex3f(-101.0,-51.0,101.0);
           glVertex3f(101.0,-51.0,101.0);

           //back
           glColor3f(1.0,0.0,0.0);
           glVertex3f(101.0,51.0,-101.0);
           glVertex3f(-101.0,51.0,-101.0);
           glVertex3f(-101.0,-51.0,-101.0);
           glVertex3f(101.0,-51.0,-101.0);

           //top
           glColor3f(0.0,0.0,1.0);
           glVertex3f(-101.0,51.0,101.0);
           glVertex3f(101.0,51.0,101.0);
           glVertex3f(101.0,51.0,-101.0);
           glVertex3f(-101.0,51.0,-101.0);

           //bottom
           glColor3f(0.0,1.0,0.0);
           glVertex3f(101.0,-51.0,101.0);
           glVertex3f(101.0,-51.0,-101.0);
           glVertex3f(-101.0,-51.0,-101.0);
           glVertex3f(-101.0,-51.0,101.0);

           //right
           glColor3f(1.0,1.0,0.0);
           glVertex3f(101.0,51.0,101.0);
           glVertex3f(101.0,-51.0,101.0);
           glVertex3f(101.0,-51.0,-101.0);
           glVertex3f(101.0,51.0,-101.0);

           //left
           glColor3f(1.0,0.0,1.0);
           glVertex3f(-101.0,51.0,101.0);
           glVertex3f(-101.0,-51.0,101.0);
           glVertex3f(-101.0,-51.0,-101.0);
           glVertex3f(-101.0,51.0,-101.0);
       glEnd();

       glFlush();
       qDebug() << "test";
}
static void qNormalizeAngle(int &angle)
{
     while (angle < 0)
         angle += 360 * 16;
     while (angle > 360 * 16)
         angle -= 360 * 16;
}
void OpenGL3DWidget::setXRotation(int angle)
 {
     qNormalizeAngle(angle);
     if (angle != xRot) {
         xRot = angle;
         //emit xRotationChanged(angle);
       //updateGL();
     }
 }

 void OpenGL3DWidget::setYRotation(int angle)
 {
     qNormalizeAngle(angle);
     if (angle != yRot) {
         yRot = angle;
         //emit yRotationChanged(angle);
         //updateGL();
     }
 }

 void OpenGL3DWidget::setZRotation(int angle)
 {
     qNormalizeAngle(angle);
     if (angle != zRot) {
         zRot = angle;
         //emit zRotationChanged(angle);
        // updateGL();
     }
 }

void OpenGL3DWidget::mousePressEvent(QMouseEvent *event)
 {
     lastPos = event->pos();
 }

 void OpenGL3DWidget::mouseMoveEvent(QMouseEvent *event)
 {
     int dx = event->x() - lastPos.x();
     int dy = event->y() - lastPos.y();

     if (event->buttons() & Qt::LeftButton) {
         setXRotation(xRot + 1 * dy);
         setYRotation(yRot + 1 * dx);
     } else if (event->buttons() & Qt::RightButton) {
         setXRotation(xRot + 1 * dy);
         setZRotation(zRot + 1 * dx);
     }
     lastPos = event->pos();
}

 void OpenGL3DWidget::timerFunction()
 {
     update(); //GL 업데이트
 }
 void OpenGL3DWidget::setXYZRotation(float y, float p, float r)
 {
     xRot = p;
     yRot = y * -1;
     zRot = r * -1;
     //updateGL();
 }
