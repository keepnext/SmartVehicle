#include "lidar_test.h"

#include "ui_lidar_design.h"
#include ""
#include "QHostAddress"


lidar_test::lidar_test(QWidget* parent)
    : QWidget(parent), ui(new Ui::lidar_ui)
{
    ui->setupUi(this)

    connect(ui->connbtn, SIGNAL(clicked())), this, SLOT(connectbtn_push()));

    tcpClient = new QTcpSocket(this)

    connect(tcpClient, SIGNAL(readyRead())), this, SLOT(tcp_recved_data());
    connect(tcpClient, SIGNAL(connected())), this, SLOT(tcp_connected()));
    connect(tcpClient, SIGNAL(connected())), this, SLOT(tcp_disconnected()));
}

void lidar_test::connectbtn_push()
{
    QString xycarip = ui->serverip->text().trimmed();
    QString lidarport = ui->serverip->text().trimmed();

    QHostAddress HADDR_IP(xycarip); 

    tcpClient -> connectToHost(HADDR_IP, lidarport.toUShost);
}

void lidar_test::tcp_connected()
{

    qDebug() << Q_FUNC_INFO << "서버 접속 완료";
} 
   

ui -> sensordata -> setText(strRecv);

int iStartPos = strRecv.index0f("[", 0);

int iEndPos = strRecv.index0f("]", 1);

if(iStartPos != -1)
{
    if(iStartPos < iEndPos)
    {
        qDebug() << "start:" << iStartPos <<
    }
}









