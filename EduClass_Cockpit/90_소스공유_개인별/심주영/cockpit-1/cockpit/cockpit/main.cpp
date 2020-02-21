#include "widget.h"
#include "imu.h"
#include "imu3d.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;
    w.show();

    imu imu;
    imu.show();

    //imu3d imu3d;
    //imu3d.show();

    return a.exec();
}
