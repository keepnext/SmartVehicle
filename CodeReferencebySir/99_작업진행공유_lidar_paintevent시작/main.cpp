#include <QApplication>

#include "lidar_test.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    lidar_test w;
    w.show();

    return a.exec();
}









