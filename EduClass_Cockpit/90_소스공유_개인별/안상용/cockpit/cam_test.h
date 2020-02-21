#ifndef CAM_TEST_H
#define CAM_TEST_H

#include <QWidget>

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "lidar_test.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Cam_UI; }
class QTcpSocket;
QT_END_NAMESPACE

class cam_test : public QWidget
{
    Q_OBJECT

public:
    cam_test(QWidget* parent = nullptr,lidar_test*lidar = nullptr);
    ~cam_test();

private:
    lidar_test* ptr_lidar;

    Ui::Cam_UI *ui;
    QTcpSocket *tcpSocket;
    cv::Mat img;
    QByteArray imgByte;

private slots:
    void connectButton();
    void connected();
    void readMessage();
    void disconnected();
};

#endif // CAM_TEST_H
