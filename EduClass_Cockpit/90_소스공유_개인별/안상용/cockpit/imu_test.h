#ifndef IMU_TEST_H
#define IMU_TEST_H


#include <QWidget>

#include "imu3d_test.h"





#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class imu_test; }
class QTcpSocket;
//class imu3d;
QT_END_NAMESPACE

class imu_test : public QWidget
{
    Q_OBJECT

public:
    imu_test(QWidget *parent = nullptr);
    ~imu_test();

protected:
    void paintEvent(QPaintEvent *event);

signals:
    void sendYaw(int);

private:
    Ui::imu_test *ui;
    QTcpSocket *tcpSocket;

    QString strRecved;
    QString strMsg;

    imu3d_test* obj3d;
    cv::Mat img;
   QByteArray imgByte;


    void initialize();

private slots:
    void timerEvent(QTimerEvent* event);
    void connectButton();
    void connected();
    void readMessage();
    void disconnected();


};


#endif // IMU_TEST_H
