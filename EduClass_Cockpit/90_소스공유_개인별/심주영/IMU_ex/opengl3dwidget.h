#ifndef OPENGL3DWIDGET_H
#define OPENGL3DWIDGET_H

#include <QWidget>
#include <QtOpenGL>
#include <QGLWidget>
class QTimer;
class OpenGL3DWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
     OpenGL3DWidget(QWidget *parent = nullptr);
     ~OpenGL3DWidget();

private:
    void paintGL(); //실제 그래픽을 그린다.
    void initializeGL(); //Opengl 초기화
    void resizeGL(int w, int h); //위젯 크기 변했을때 발생하는 함수
    void mousePressEvent(QMouseEvent *event); //마우스클릭 이벤트
    void mouseMoveEvent(QMouseEvent *event); //마우스이동이벤트

    GLfloat xRot,yRot,zRot; //회전을 위한 변수
    GLfloat windowWidth; //위젯 길이
    GLfloat windowHeight; //위젯 높이
    QPoint lastPos; //마우스 이동을 위한 변수
    QTimer* timer; //타이머 0.01초마다 발생
signals:
    void xRotationChanged(int angle); //X축 회전했을때
    void yRotationChanged(int angle); //Y축 회전했을때
    void zRotationChanged(int angle); //Z축 회전했을때

public slots:
    void timerFunction(); //0.01초 지나면 이함수 실행
    void setXRotation(int angle); //X축으로 회전하기
    void setYRotation(int angle); //Y축으로 회전하기
    void setZRotation(int angle); //Z축으로 회전하기
    void setXYZRotation(float y, float p, float r);
};


#endif // OPENGL3DWIDGET_H
