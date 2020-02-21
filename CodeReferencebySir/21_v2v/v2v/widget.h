#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QtCharts>
#include <QGraphicsView>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

struct CAR_INFO_FWD
{
    bool b_Run = false;
    double db_Vel = 0;

    int    i_sendsec = 0;
    int    i_sendremain = 0;
    double db_sendvel = 0;
    double db_sendpos = 0;

    double db_TargetVel = 0;
    double db_Acc = 0;
    double db_Brake = 0;
    double db_Pos = 0;
    double db_MinPos = 0;

    int i_Braking = 0; // 1 : 긴급 제동
    int i_sendBraking = 0;
};

struct CAR_INFO_FLW
{
    bool b_Run = false;
    int i_State = 0; // 0 : 증속, 1 : 추종, 2 : 최대감속
    double db_Vel = 0;

    double db_Acc = 0;
    double db_Acc_Control = 0;
    double db_Brake = 0;
    double db_Pos = 0;
    double db_MaxPos = 0;

    double db_relvel = 0;
    double db_relpos = 0;

    double db_StopBestDist_Fwd = 0;
    double db_StopWorstDist_Flw = 0;
};

class QTimer;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QTimer* timer;

    CAR_INFO_FWD Fowarder;
    CAR_INFO_FLW Follower;

    QSplineSeries* series1;
    QSplineSeries* series2;
    QChartView *chartView;
    QChart *chart;

    QSplineSeries* series3;
    QSplineSeries* series4;
    QChartView *chartView2;
    QChart *chart2;

private slots:
    void on_start_clicked();
    void timerFunction();

    void on_spdup_clicked();

    void on_spddown_clicked();

    void on_stop_clicked();

private:
    Ui::Widget *ui;

};
#endif // WIDGET_H
