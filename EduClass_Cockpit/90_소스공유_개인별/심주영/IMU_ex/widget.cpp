#include "widget.h"
#include "ui_widget.h"
#include <QHostAddress>
#include <QDebug>
#include <QTime>
#include <QGLWidget>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->connectButton, SIGNAL(clicked()),
            this,              SLOT(connectButton()));


    object3d = new OpenGL3DWidget(ui->label_object3d);
    object3d->resize(ui->label_object3d->width(), ui->label_object3d->height());
    Init();

}

Widget::~Widget()
{
    delete ui;
}


void Widget::Init()
{
    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket, SIGNAL(readyRead()),
            this,      SLOT(readMessage()));
    connect(tcpSocket, SIGNAL(disconnected()),
            this,      SLOT(disconnected()));
}

void Widget::connectButton()
{
    QString serverip   = ui->serverIP->text().trimmed();
    QString Port       = ui->PORT->text().trimmed();

    QHostAddress serverAddress(serverip);
    tcpSocket->connectToHost(serverAddress, Port.toInt());
}

void Widget::readMessage()
{
    if(tcpSocket->bytesAvailable() >= 0)
    {
        QByteArray readData = tcpSocket->readAll();

        QString strrecv(readData);

        strrecv.remove("\r\n").remove("#YPRAG=");

        QStringList strRecvArry = strrecv.split(",");
        ui->label_imuLog->setText("Time : "+QTime::currentTime().toString());
        ui->label_2->setText("[ Y : "+strRecvArry[0]+" ] "+"[ P : "+ strRecvArry[1]+" ] "+" [ R : "+strRecvArry[2] +" ]\n");
        object3d->setXYZRotation(strRecvArry[0].toFloat(), strRecvArry[1].toFloat(), strRecvArry[2].toFloat());
       }
}

void Widget::disconnected()
{

        qDebug() << Q_FUNC_INFO << "서버 접속 종료.";
}
