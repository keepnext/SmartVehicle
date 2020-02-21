#include "lidar_test.h"

#include "ui_lidar_design.h"

#include <QTcpSocket>
#include <QHostAddress>

#include <QPainter>

lidar_test::lidar_test(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::lidar_ui)
{
    ui->setupUi(this);
    connect(ui->connbtn, SIGNAL(clicked()), \
            this, SLOT(connectbtn_push()));
    tcpClient = new QTcpSocket(this);
    connect(tcpClient, SIGNAL(readyRead()), \
            this, SLOT(tcp_recved_data()));
    connect(tcpClient, SIGNAL(connected()), \
            this, SLOT(tcp_connected()));
    connect(tcpClient, SIGNAL(disconnected()), \
            this, SLOT(tcp_disconnected()));

    for(int i=0;i<360;i++)
    {
        iDist[i] = 0;
    }
}
lidar_test::~lidar_test()
{
    delete ui;
}

void lidar_test::connectbtn_push()
{
    QString xycarip = ui->serverip->text().trimmed();
    QString lidarport = ui->serverport->text().trimmed();

    QHostAddress HADDR_IP(xycarip);


    tcpClient->connectToHost(HADDR_IP, lidarport.toUShort());
}

void lidar_test::tcp_connected()
{
    qDebug() << Q_FUNC_INFO << "서버접속완료";
}

void lidar_test::tcp_recved_data()
{
    qDebug() << Q_FUNC_INFO << "수신";

    if(tcpClient->bytesAvailable() >= 0)
    {
        QByteArray readData = tcpClient->readAll();
        //qDebug() << readData;

        QString strRecv(readData);

        ui->sensordata->setText(strRecv);


        int iStartPos = strRecv.indexOf("[", 0); // -1
        int iEndPos = strRecv.indexOf("]", 1);

        if(iStartPos != -1)
        {
            if(iStartPos < iEndPos)
            {
               qDebug() << "start:" << \
                           iStartPos << "end:" << iEndPos;


               QString strRadTotal = \
                       strRecv.mid(iStartPos, \
                                   iEndPos - \
                                   iStartPos);
               //qDebug() << strRadTotal;

               strRadTotal.remove(0,1);

               QStringList strRad = strRadTotal.split("|");
               qDebug() << strRad.count();
               if(strRad.count() == 361)
               {
                   for(int i = 0; i < 360; i++)
                   {
                       int iRad = strRad[i].mid(0,3).toInt();
                       int iDistance = strRad[i].remove(0,4).toInt();

                       iDist[iRad] = iDistance;
                   }
               }
            }
        }


    }
}

void lidar_test::tcp_disconnected()
{
    qDebug() << Q_FUNC_INFO << "연결종료";
}

void lidar_test::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this);

    painter->setPen(QPen(Qt::red, 6));
    painter->translate(this->size().width()/2, \
                       this->size().height()/2 + 100);

    painter->drawPoint(0, 0);

    painter->setPen(QPen(Qt::green, 1));
    painter->drawLine(0, 0, 0, -50);

    painter->setPen(QPen(Qt::blue, 3));
    painter->drawArc(40/-2, 40/-2, 40, 40, 0, 360 * 16);
    painter->drawText(20,20, "20cm");
    painter->drawArc(100/-2, 100/-2, 100, 100, 0, 360 * 16);
    painter->drawText(50,50, "50cm");
    painter->drawArc(200 /-2, 200/-2, 200, 200, 0, 360 * 16);
    painter->drawText(100,100, "100cm");





    delete painter;
}












