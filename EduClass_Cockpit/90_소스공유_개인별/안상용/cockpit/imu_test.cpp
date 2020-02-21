#include "imu_test.h"
#include "ui_imu_test.h"
#include "imu3d_test.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>
#include <QPainter>

#include <QTime>

imu_test::imu_test(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::imu_test)
{
    ui->setupUi(this);
    initialize();

    //obj3d = new imu3d_test(ui->opengl);
    //obj3d ->resize(ui->opengl->width(), ui->opengl->height());


}

imu_test::~imu_test()
{
    delete ui;
}

void imu_test::initialize()
{
    tcpSocket = new QTcpSocket(this);

    connect(ui->conn, SIGNAL(clicked()), this, SLOT(connectButton()));
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(connected()));

}

void imu_test::connectButton()
{
    QString sensorip   = ui->serverip->text().trimmed();
    QString sensorport   = ui->serverport->text().trimmed();

    QHostAddress serverAddress(sensorip);
    tcpSocket->connectToHost(serverAddress, sensorport.toUShort());

    qDebug() << Q_FUNC_INFO << "서버 접속 요청";
}

void imu_test::connected()
{
    qDebug() << Q_FUNC_INFO << "서버 접속 완료";
    startTimer(1000);
}

void imu_test::readMessage()
{
    if(tcpSocket->bytesAvailable() >= 0)
    {
        // 영상값 수신
                QByteArray readData = tcpSocket->readAll();
                imgByte.append(readData);
                //ui->value->setText("현재시간 : " + QTime::currentTime().toString() + "," + QString::number(readData.count()));
                if(imgByte.count() >= 480 * 640 * 3)
                {
                    cv::Mat tmp(480, 640, CV_8UC3, imgByte.data());
                    img = tmp.clone();
                    imgByte.remove(0, 480*640*3);

                    QImage image( img.data,
                                  img.cols, img.rows,
                                  static_cast<int>(img.step),
                                  QImage::Format_RGB888 );
                    ui->opengl->setPixmap(QPixmap::fromImage(image));
                }

        /*
        // 상태값 수신
        QByteArray readData = tcpSocket->readAll();
        QString strRecv(readData);
       //ui->data->setText("현재시간 : " + QTime::currentTime().toString() + " = " + strRecv);
        strRecv.remove("\r\n").remove("#YPR=");
        QStringList strRecvArray = strRecv.split(",");
        ui->data->setText(QString("YAW : %1 PITCH = %2 ROLL = %3").arg(strRecvArray[0]).arg(strRecvArray[1]).arg(strRecvArray[2]));
       // qDebug() << strRecvArray;

        emit sendYaw(static_cast<int>(strRecvArray[0].toFloat()));  //signals에서 데이터 발생하는걸 필요할때 가져와서 사용
        //iRecvYaw = static_cast<int>(strRecvArray[0].toFloat()); //float 데이터를 소숫점이하 버리고 int 형으로 바꿈
        obj3d->setXYZRotation(strRecvArray[0].toFloat(), strRecvArray[1].toFloat(), strRecvArray[2].toFloat());
        */
    }
}

void imu_test::disconnected()
{
    tcpSocket->close();
    qDebug() << Q_FUNC_INFO << "서버 접속 종료.";
}

void imu_test::paintEvent(QPaintEvent *event)
{
}

void imu_test::timerEvent(QTimerEvent* event)
{
    update();
}

