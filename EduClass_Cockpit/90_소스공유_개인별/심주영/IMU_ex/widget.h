#ifndef WIDGET_H
#define WIDGET_H

#include "opengl3dwidget.h"
#include <QWidget>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE
class OpenGL3DWidget;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    void Init();
     QTcpSocket *tcpSocket;
    OpenGL3DWidget *object3d;
private slots:
     void connectButton();
     void readMessage(); // 서버로부터 메세지를 받을 때 호출 됨
     void disconnected();
};
#endif // WIDGET_H
