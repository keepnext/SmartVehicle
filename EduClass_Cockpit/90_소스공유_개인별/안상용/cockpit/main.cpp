#include "widget.h"

#include <QApplication>
#include "lidar_test.h"
#include "imu_test.h"
#include "cam_test.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    imu_test w2;
    w2.show();

    lidar_test w;
    w.show();



    QObject::connect(&w2, SIGNAL(sendYaw(int)), &w,SLOT(recvYaw(int)));

    cam_test w3(nullptr, &w);
    w3.show();
    return a.exec();
}
