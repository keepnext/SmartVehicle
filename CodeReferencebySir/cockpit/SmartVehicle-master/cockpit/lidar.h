
#ifndef 
#


#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui {class lidar_ui;}

class QTcpSocket;
QT_END_NAMESPACE

class lidar_test: public QWidget
{
public:
    lidar_test(QWidget*parent = nullptr);

private:
    UI::lidar_ui *ui;
    QTcpSocket *tcpClient;

private slots:
    void connectbtn_push();

    void tcp_connected();
    void tcp_receved_data();
    void tcp_disconnectd();

}