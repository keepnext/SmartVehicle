#include "lidar_test.h"
#include "ui_lidar_design.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>
#include <QPainter>

lidar_test::lidar_test(QWidget* parent): QWidget(parent) ,ui(new Ui::lidar_ui)
{
    ui->setupUi(this);

    tcpClient = new QTcpSocket(this);
    connect(ui->connbtn, SIGNAL(clicked()), this, SLOT(connetbtn_push()));
    connect(tcpClient, SIGNAL(readyRead()), this, SLOT(tcp_recved_data()));
    connect(tcpClient, SIGNAL(connected()), this, SLOT(tcp_connected()));
    connect(tcpClient, SIGNAL(disconnected()), this, SLOT(tcp_disconnected()));
    for(int i=0;i<360; i++)
    {
        iDist[i] =0;
    }
}


lidar_test::~lidar_test()
{
    delete ui;
}


void lidar_test::connetbtn_push()
{
    QString xycarip = ui ->serverip->text().trimmed();
    QString lidarport = ui -> serverport-> text().trimmed();

    QHostAddress HADDR_IP(xycarip);     //자료형 변경
    tcpClient->connectToHost(HADDR_IP, lidarport.toUShort());     //unsigned shot


}

void lidar_test::tcp_connected()
{
    qDebug() << Q_FUNC_INFO << "서버 접속 완료";
}

void lidar_test::tcp_recved_data()
{
    qDebug() << Q_FUNC_INFO << "수신";
    if(tcpClient->bytesAvailable() >=0)
    {
        QByteArray readData = tcpClient->readAll();
        //qDebug() << readData;

        QString strRecv(readData);

        ui->sensordata->setText(strRecv);

        int iStartPos = strRecv.indexOf("[",0);
        int iEndPos = strRecv.indexOf("]",1);

        if(iStartPos != -1)
        {
            if(iStartPos < iEndPos )
            {
                qDebug() << "start:" << iStartPos << "end:" << iEndPos;
                QString strRadTotal = strRecv.mid(iStartPos,iEndPos - iStartPos);

                //qDebug() << strRadTotal;

                strRadTotal.remove("[");
                QStringList strRad = strRadTotal.split("|");
                if(strRad.count() == 361)
                {
                    for( int i =0 ; i < 360; i ++)
                    {
                        int iRad = strRad[i].mid(0,3).toInt();
                        int iDistance = strRad[i].remove(0,4.).toInt();
                       // qDebug() << "rad:" << strRad[i].mid(0,3).toInt(); //각도값
                        //qDebug() << "dist: " << strRad[i].remove(0,4).toInt(); //거리값
                        iDist[iRad] = iDistance;
                    }
                }
                update();

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
    QPainter *painter =new QPainter(this);
    painter->drawText(0,0, QString(iYaw));

    painter -> setPen(QPen(Qt::red,6));   //색상 두께
    //painter -> drawPoint(200,300);

    painter->translate(this->size().width()/2,this->size().height()/2+100);

    painter->drawPoint(0,0);



    painter->setPen(QPen(Qt::blue,3));  //정의된 색상 사용
    painter->drawArc(40/-2,40/-2,40,40, 0,360*16);
    painter->drawText(20,20,"20cm");
    painter->drawArc(100/-2,100/-2,100,100, 0,360*16);
    painter->drawText(50,50,"50cm");
    painter->drawArc(200/-2,200/-2,200,200, 0,360*16);
    painter->drawText(100,100,"100cm");

     //초기각도 값을 불러와서 공백을 없애고 값을 가져옴

    painter->setPen(QPen(Qt::green,1));
    painter->drawLine(0,0,0,-50);

    painter->rotate(ui->angle->text().toInt()*-1);

    //0~359, 거리
    painter->setPen(QPen(QColor(255,255,50),3));  //색상 만들어 사용 RGB

    for(int i =0; i<360; i++)
    {
        if(iDist[i] != 0)
        {
        //painter->drawLine(0,0,0,-100);
            if(iDist[i] > 20 && iDist[i] < 50)
            {
                painter->setPen(QPen(QColor(255,150,50),3));
                painter->drawPoint(iDist[i]/10,0);
            }
            if(iDist[i] > 50 && iDist[i] < 100)
            {
                painter->setPen(QPen(QColor(150,150,50),3));
                painter->drawPoint(iDist[i]/10,0);
            }
            else
            {
                painter->setPen(QPen(QColor(50,50,50),3));
                painter->drawPoint(iDist[i]/10,0);
            }

        painter->drawPoint(iDist[i] /10, 0);
        iDist[i] = 0;
        }
        painter->rotate(-1); //현재상황에서 각도를 돌림 기준 각도 아님

    }

    //painter->drawPoint(50,-50);



    delete painter;
}
void lidar_test::recvYaw(int iRecvYaw)
{
    iYaw = iRecvYaw;
}
