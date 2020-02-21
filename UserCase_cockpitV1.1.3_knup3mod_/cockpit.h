#ifndef COCKPIT_H
#define COCKPIT_H

#include <QWidget>
#include "common.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Cockpit; }
QT_END_NAMESPACE

//콕핏디스플레이에 디지털시간표시(타이머)
class QLCDNumber;
//콕핏디스플레이에 관성측정장치 화면표시
class imu3d;

class cockpit  : public QWidget
{
    Q_OBJECT

public:
    cockpit(QWidget *parent = nullptr);
    ~cockpit();

protected:
    void paintEvent(QPaintEvent *);


public:
    imu3d* obj_imu3d;
    int iRenderCnt;


    void initialize();

    // Image
    QPixmap* cluster_bg;
    QPixmap* arr_left; //방향지시등(좌)화살표 표시, 제어신호시 깜박임
    QPixmap* arr_right; //방향지시등(우)화살표 표시, 제어신호시 깜박임

    QLCDNumber *lcd; //기어위치상태 표시

private:
    Ui::Cockpit *ui;


private slots:
    void displayClock();

    void recv_YPR(float, float, float);
};

#endif // COCKPIT_H
