#include "ultra.h"
#include "ui_ultra.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>
#include <QPainter>

#include <QTime>

ultra::ultra(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Ultra)
{
    ui->setupUi(this);
    initialize();
}

ultra::~ultra()
{
    delete ui;
}

void ultra::initialize()
{
    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(connected()));
    connect(ui->conn, SIGNAL(clicked()), this, SLOT(connectButton()));
}

void ultra::connectButton()
{
    QString sensorip   = ui->sensorip->text().trimmed();
    QString sensorport   = ui->sensorport->text().trimmed();

    QHostAddress serverAddress(sensorip);
    tcpSocket->connectToHost(serverAddress, sensorport.toUShort());

    qDebug() << Q_FUNC_INFO << "서버 접속 요청";
}

void ultra::connected()
{
    qDebug() << Q_FUNC_INFO << "서버 접속 완료";
}

void ultra::readMessage()
{
    if(tcpSocket->bytesAvailable() >= 0)
    {
        // 상태값 수신
        QByteArray readData = tcpSocket->readAll();
        QString strRecv(readData);
        //qDebug() << strRecv;

        ui->value->setText("현재시간 : " + QTime::currentTime().toString() + " = " + strRecv);

        iUltraDist_in = strRecv.mid(1, 3).toInt();
        iUltraDist_cm = iUltraDist_in * 2.54;

        if(iUltraDist_cm < 30)
        {
            strMsg = "접촉 주의";
        }
        else if(iUltraDist_cm < 60)
        {
            strMsg = "근거리 접근";
        }
        else
        {
            strMsg = "";
        }
        ui->value2->setText(QString("%1in = %2cm").arg(iUltraDist_in).arg(iUltraDist_cm));
        update();
    }
}

void ultra::disconnected()
{
    tcpSocket->close();
    qDebug() << Q_FUNC_INFO << "서버 접속 종료.";
}

void ultra::paintEvent(QPaintEvent *event)
{   
    QPainter *painter = new QPainter(this);
    painter->translate(width()/2, ui->sensor->y() + 30);
    QRect rectangle(-150, -300 + 20, 300, 600);
    int startAngle = 5760 / 4 * -1 + 16 * 30 * -1;
    int spanAngle = 16 * 30 * 2;
    painter->setPen(QPen(Qt::blue, 1));
    painter->setBrush(QBrush(Qt::white));
    painter->drawPie(rectangle, startAngle, spanAngle);
    painter->setPen(QPen(Qt::blue, 10));
    painter->drawPoint(0, 0);
    // 152.2cm
    painter->setPen(QPen(Qt::red, 1));
    if(iUltraDist_cm > 152)
    {
        iUltraDist_cm = 152;
    }
    painter->drawLine(-150, iUltraDist_cm * 2 + 20, 150, iUltraDist_cm * 2 + 20);
    painter->drawText(50, 0, strMsg);
    QRect clipRect(-150, 20, 300, iUltraDist_cm * 2);
    painter->setClipping(true);
    painter->setClipRect(clipRect);
    painter->setBrush(QBrush(Qt::red));
    painter->drawPie(rectangle, startAngle, spanAngle);
    delete painter;
}
