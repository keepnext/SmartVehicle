#ifndef CONT_H
#define CONT_H

#include <QWidget>
#include <QIcon>

namespace Ui {
class cont;
}

class QWebEngineView;  //ivi function added
class cont : public QWidget
{
    Q_OBJECT

public:
    explicit cont(QWidget *parent = nullptr);
    ~cont();

signals:
    void connLidar(QString, QString);
    void connCam(QString, QString);
    void connImu(QString, QString);
    void connSonar(QString, QString);

    void disconn();
    void startSystem();  //ivi function added
    void endSystem();    //ivi function added

public slots:
    void connectDevice();
    void disconnectDevice();

private slots:

    void on_accel_clicked();
    void on_brake_clicked();

    void on_left_clicked();
    void on_right_clicked();
    void on_emgr_clicked();

    void on_gear_valueChanged(int value);

    void on_lidarrad_textChanged(const QString &arg1);

    void on_start_clicked();  //ivi funtion added
    void on_map1_clicked();   //ivi funtion added
    void on_map2_clicked();   //ivi funtion added

    void on_horizontalSlider_actionTriggered(int action);

    void on_progressBar_2_valueChanged(int value);

private:
    QTimer* timer; //타이머 0.01초마다 발생
    bool bStart;    //ivi function added

    Ui::cont *ui;
//ivi function added
    QPixmap* on;
    QPixmap* off;

    QIcon* on_icon;
    QIcon* off_icon;

    QWebEngineView* view;

};

#endif // CONT_H
