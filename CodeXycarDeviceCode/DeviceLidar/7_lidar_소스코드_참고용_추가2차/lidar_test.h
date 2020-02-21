#ifndef LIDAR_TEST_H
#define LIDAR_TEST_H

#include <QWidget>
#include "imu_test.h"

QT_BEGIN_NAMESPACE
namespace Ui { class lidar_ui; }
QT_END_NAMESPACE

class QTcpSocket;

class lidar_test : public QWidget
{
    Q_OBJECT

public:
    lidar_test(QWidget* parent = nullptr);
    ~lidar_test();

private:
    Ui::lidar_ui *ui;
    QTcpSocket *tcpClient;

    int iDist[360];
    
    int iYaw;


protected:
    void paintEvent(QPaintEvent *event) override;

public slots:
    void recvYaw(int);

private slots:
    void connectbtn_push();

    void tcp_connected();
    void tcp_recved_data();
    void tcp_disconnected();
};

#endif // LIDAR_TEST_H

