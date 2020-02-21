#include "widget.h"
#include "ui_widget.h"

#include <QTimer>

int iStartFollower = 0;
int iGraphSeq = 0;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


    timer= new QTimer(this); //타이머 생성
    connect(timer,SIGNAL(timeout()),this,SLOT(timerFunction())); //타이머와 함수를 연결

    series1 = new QSplineSeries();
    series2 = new QSplineSeries();

    chart = new QChart();
    chart->legend()->hide();  // 범례 숨김
    chart->addSeries(series1);
    chart->addSeries(series2);
    chart->createDefaultAxes(); // 기본 축 생성
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->axisX()->setRange(0, 100);
    chart->axisY()->setRange(0, 140);

    chartView = new QChartView(chart, ui->graph);
    chartView->setRenderHint(QPainter::Antialiasing);

    chartView->resize(ui->graph->width(), ui->graph->height());


    series3 = new QSplineSeries();
    series4 = new QSplineSeries();

    chart2 = new QChart();
    chart2->legend()->hide();  // 범례 숨김
    chart2->addSeries(series3);
    chart2->addSeries(series4);
    chart2->createDefaultAxes(); // 기본 축 생성
    chart2->setAnimationOptions(QChart::AllAnimations);
    chart2->axisX()->setRange(0, 100);
    chart2->axisY()->setRange(0, 100);

    chartView2 = new QChartView(chart2, ui->graph2);
    chartView2->setRenderHint(QPainter::Antialiasing);

    chartView2->resize(ui->graph2->width(), ui->graph2->height());
}

Widget::~Widget()
{
    delete ui;
}

void Widget::timerFunction()
{
    if(Fowarder.b_Run == true)
    {
        if(Fowarder.db_Vel < Fowarder.db_TargetVel)
        {
            Fowarder.db_Vel = Fowarder.db_Vel + Fowarder.db_Acc * ui->proc_sec->text().toInt();
        }
        else
        {
            if(Fowarder.i_Braking == 1)
            {
                Fowarder.db_Vel = Fowarder.db_Vel + ((Fowarder.db_Brake * (ui->maxbrake_per->text().toDouble() / 100))  * ui->proc_sec->text().toInt() * -1);
            }
            else
            {
                Fowarder.db_Vel = Fowarder.db_Vel + ((Fowarder.db_Brake * (ui->maxbrake_per->text().toDouble() / 100))  * ui->proc_sec->text().toInt() * -1);
            }
        }

        if(Fowarder.db_Vel < 0)
        {
            Fowarder.db_Vel = 0;
        }

        if(Fowarder.db_Vel > 0)
        {
            Fowarder.db_MinPos = Fowarder.db_Pos + ((Fowarder.db_Vel - (ui->spderr_mt->text().toDouble() * 3.6)) / 3.6);
            if(Fowarder.db_MinPos < 0)
            {
                Fowarder.db_MinPos = 0;
            }
            Fowarder.db_Pos = Fowarder.db_Pos + (Fowarder.db_Vel / 3.6);
        }

        if(Fowarder.i_sendremain > 0 )
        {
            Fowarder.i_sendremain--;
        }
        else
        {
            Fowarder.db_sendvel = Fowarder.db_Vel - (ui->spderr_mt->text().toDouble() * 3.6);
            Fowarder.db_sendpos = Fowarder.db_MinPos;
            Fowarder.i_sendBraking = Fowarder.i_Braking;
            Fowarder.i_sendremain = Fowarder.i_sendsec;
        }
    }

    if(Follower.b_Run == true)
    {
        Follower.db_relpos = Fowarder.db_sendpos - Follower.db_MaxPos;
        Follower.db_relvel = Fowarder.db_sendvel - Follower.db_Vel;

        Follower.db_StopBestDist_Fwd = pow(Fowarder.db_sendvel / 3.6, 2) / (Fowarder.db_Brake * (ui->maxbrake_per->text().toDouble() / 100));
        Follower.db_StopWorstDist_Flw = pow(Follower.db_Vel / 3.6, 2) / (Follower.db_Brake * 0.9);

        if(Follower.db_MaxPos + Follower.db_StopWorstDist_Flw
                > Fowarder.db_sendpos + Follower.db_StopBestDist_Fwd - 2) // 목표 최소 추종거리
        {
            Follower.i_State = 3;  // 속도 감속
        }
        else if(Follower.db_Vel >= Fowarder.db_sendvel + 10) // 목표 최소 추종거리
        {
            Follower.i_State = 2;  // 속도 감속
        }
        else if(Follower.db_MaxPos + Follower.db_StopWorstDist_Flw
                    > Fowarder.db_sendpos + Follower.db_StopBestDist_Fwd - 1) // 목표 최소 추종거리
        {
            Follower.i_State = 1;  // 간격 유지
        }
        else
        {
            Follower.i_State = 0;   // 증속
        }

        if(Fowarder.i_sendBraking == 1)
        {
            Follower.i_State = 4;   // 긴급제동
        }

        if(Follower.i_State == 0
                || Follower.i_State == 1)
        {
            if(Follower.i_State == 0)
            {
                Follower.db_Acc_Control = Follower.db_Acc;
            }
            else if(Follower.i_State == 1)
            {
                if(Follower.db_Vel < Fowarder.db_sendvel)
                {
                    Follower.db_Acc_Control = 0.1;
                }
                else
                {
                    Follower.db_Acc_Control = -0.1;
                }
            }

            Follower.db_Vel = Follower.db_Vel + Follower.db_Acc_Control * ui->proc_sec->text().toInt();
        }
        else if(Follower.i_State == 2)
        {
           Follower.db_Vel = Follower.db_Vel + ((Follower.db_Brake * 0.1) * ui->proc_sec->text().toInt() * -1);
        }
        else if(Follower.i_State == 3)
        {
           Follower.db_Vel = Follower.db_Vel + ((Follower.db_Brake * 0.9) * ui->proc_sec->text().toInt() * -1);
        }
        else
        {
           Follower.db_Vel = Follower.db_Vel + ((Follower.db_Brake * (ui->maxbrake_per->text().toDouble() / 100))  * ui->proc_sec->text().toInt() * -1);
        }



        if(Follower.db_Vel < 0)
        {
            Follower.db_Vel = 0;
        }

        if(Follower.db_Vel > 0)
        {
            Follower.db_MaxPos = Follower.db_Pos + ((Follower.db_Vel + Follower.db_Acc * ui->proc_sec->text().toInt()) / 3.6);
            Follower.db_Pos = Follower.db_Pos + (Follower.db_Vel / 3.6);
        }
    }

    if(iStartFollower < 5)
    {
        if(Fowarder.db_TargetVel > 0)
        {
            iStartFollower++;
        }
    }
    else
    {
        Follower.b_Run = true;
    }

    series1->append(iGraphSeq, static_cast<int>(Fowarder.db_Vel));
    series2->append(iGraphSeq, static_cast<int>(Follower.db_Vel));

    if(iGraphSeq > 60 && iGraphSeq % 30 == 1)
    {
        chart->scroll(70, 0);
    }

    series3->append(iGraphSeq, static_cast<int>(Follower.db_relpos));
    series4->append(iGraphSeq, static_cast<int>(Follower.db_relpos));

    if(iGraphSeq > 60 && iGraphSeq % 30 == 1)
    {
        chart2->scroll(70, 0);
    }

    iGraphSeq++;

    ui->fwdspd->setText(QString::number(Fowarder.db_Vel));
    ui->fwdpos->setText(QString("%1, MIN %2").arg(QString::number(Fowarder.db_Pos)) \
                        .arg(QString::number(Fowarder.db_MinPos)));

    ui->flwspd->setText(QString::number(Follower.db_Vel));
    ui->flwpos->setText(QString("%1, MAX %2").arg(QString::number(Follower.db_Pos)) \
                        .arg(QString::number(Follower.db_MaxPos)));


    ui->relspd->setText(QString::number(Follower.db_relvel));
    ui->relpos->setText(QString::number(Follower.db_relpos));

    ui->fwdstopdistmin->setText(QString::number(Follower.db_StopBestDist_Fwd));
    ui->flwstopdistmax->setText(QString::number(Follower.db_StopWorstDist_Flw));

    ui->flwstate->setText(QString::number(Follower.i_State));

    if(Fowarder.b_Run == false)
    {
        timer->stop();
    }
}


void Widget::on_start_clicked()
{
    Fowarder.b_Run = true;
    Fowarder.db_Vel = 0;
    Fowarder.db_TargetVel = 0;
    Fowarder.db_Acc = ui->highacc_spd->text().toDouble();
    Fowarder.db_Brake = ui->highbrake_spd->text().toDouble();
    Fowarder.db_Pos = 0;
    Fowarder.db_MinPos = 0;
    Fowarder.i_sendsec =  ui->comm_sec->text().toInt();
    Fowarder.i_sendremain =  Fowarder.i_sendsec;


    Follower.db_Vel = 0;
    Follower.db_Acc = ui->highacc_spd->text().toDouble();
    Follower.db_Brake = ui->highbrake_spd->text().toDouble();
    Follower.db_Pos = 0;
    Follower.db_MaxPos = 0;

    Follower.db_relvel = 0;
    Follower.db_relpos = 0;

    iStartFollower = 0;
    timer->start(ui->proc_sec->text().toInt() * 100); //타이머 시작

    ui->targetspd->setText("0");
    ui->fwdspd->setText("0");
    ui->fwdpos->setText("0");

    ui->flwstate->setText("0");
    ui->flwspd->setText("0");
    ui->flwpos->setText("0");

    ui->relspd->setText("0");
    ui->relpos->setText("0");

    ui->fwdstopdistmin->setText("0");
    ui->flwstopdistmax->setText("0");
}


void Widget::on_stop_clicked()
{
    timer->stop();
}


void Widget::on_spdup_clicked()
{
    Fowarder.db_TargetVel += 5;
    ui->targetspd->setText(QString::number(Fowarder.db_TargetVel));
}

void Widget::on_spddown_clicked()
{
    Fowarder.db_TargetVel -= 5;
    if(Fowarder.db_TargetVel < 0)
    {
        Fowarder.db_TargetVel = 0;
    }
    ui->targetspd->setText(QString::number(Fowarder.db_TargetVel));
}
