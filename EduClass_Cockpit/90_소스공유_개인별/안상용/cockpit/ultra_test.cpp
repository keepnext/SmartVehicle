#include "ultra_test.h"

Ultra_test::Ultra_test()
{

}


{
    QPainter *painter =new QPainter(this);
    painter->translate(width()/2, ui->sensor->y() + 30);
    QRect rectang(-150, -300 + 20, 300, 600);
    int startAngle = 5760/4 * -1 +16*30 -1;
    int spanAngle = 16 *30 *2;
    painter->setPen(QPen(Qt::blue, 1));


    painter -> setBrush(QBrush(Qt::white));   //색상 두께
    //painter -> drawPoint(200,300);

    painter->drawPie(rectangle, startAngle, spanAngle);


    painter->setPen(Qpen(Qt::blue, 10));




    painter->drawPoint(0,0);
    painter->setPen(QPen(Qt::red, 1));
    if (iUltraDist_cm > 152)
    {
        iUltraDist_cm = 152
    }

    painter->drawLine(-150, iUltra_cm * 2 + 20, 150, iUltraa
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
        //painter->drawLine(0,0,0,-50);
            if(iDist[i]/10> 20 && iDist[i]/10 < 50)
            {
                painter->setPen(QPen(QColor(255,150,50),3));
                painter->drawPoint(iDist[i]/10,0);
            }
            if(iDist[i]/10 > 50 && iDist[i]/10 < 100)
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
