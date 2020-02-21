#include "cam_test.h"

#include "ui_cam.h"

#include <QTcpSocket>
#include <QHostAddress>

cam_test::cam_test(QWidget* parent)
        : QWidget(parent)
        , ui(new Ui::Cam_UI)
{
    ui->setupUi(this);

    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(connected()));
    connect(ui->conn, SIGNAL(clicked()), this, SLOT(connectButton()));
}

cam_test::~cam_test()
{

}

void cam_test::connectButton()
{
    QString sensorip   = ui->serverip->text().trimmed();
    QString sensorport   = ui->serverport->text().trimmed();

    QHostAddress serverAddress(sensorip);
    tcpSocket->connectToHost(serverAddress, sensorport.toUShort());

    qDebug() << Q_FUNC_INFO << "서버 접속 요청";
}

void cam_test::connected()
{
    qDebug() << Q_FUNC_INFO << "서버 접속 완료";
}

void cam_test::readMessage()
{
    if(tcpSocket->bytesAvailable() >= 0)
    {
        // 영상값 수신
        QByteArray readData = tcpSocket->readAll();
        imgByte.append(readData);

        if(imgByte.count() >= 480 * 640 * 3)
        {
            cv::Mat tmp(480, 640, CV_8UC3, imgByte.data());
            img = tmp.clone();
            imgByte.remove(0, 480*640*3);

            QImage image( img.data,
                          img.cols, img.rows,
                          static_cast<int>(img.step),
                          QImage::Format_RGB888 );
            ui->cam->setPixmap(QPixmap::fromImage(image));
        }
    }
}

void cam_test::disconnected()
{
    tcpSocket->close();
    qDebug() << Q_FUNC_INFO << "서버 접속 종료.";
}
