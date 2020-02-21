#include "widget.h"

#include <QApplication>
#include <lidar_test.h>
#include <imu_test.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    lidar_test w;
    w.show();

    imu_test w1;
    w1.show();

    QObject::connect(&w1, SIGNAL(sendYaw()), &w,SLOT(recvYaw()));


    return a.exec();
}
