#include "cont.h"
#include "ui_cont.h"

#include "common.h"

#include <QWebEngineView>  //added
#include <QUrl>


#include <QDateTime>  //mw add2
#include <QDateTimeEdit>  //mw add2

#include <QTabWidget> // mw add3

cont::cont(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cont)
{
    ui->setupUi(this);

    //connect(ui->sbar_fuel, SIGNAL(valueChanged(int)), ui->pbar_fuel, SLOT(setValue(int)));

    //connect(ui->sbar_yaw, SIGNAL(valueChanged(int)), ui->disp_yaw, SLOT(display(int)));
    //connect(ui->sbar_pitch, SIGNAL(valueChanged(int)), ui->disp_pitch, SLOT(display(int)));
    //connect(ui->sbar_roll, SIGNAL(valueChanged(int)), ui->disp_roll, SLOT(display(int)));


    //connect(ui->dial_rpm, SIGNAL(valueChanged(int)), ui->sbar_rpm, SLOT(setValue(int)));
    //connect(ui->dial_speed, SIGNAL(valueChanged(int)), ui->sbar_speed, SLOT(setValue(int)));

    //connect(ui->dial_rpm, SIGNAL(valueChanged(int)), ui->disp_rpm, SLOT(display(int)));
    //connect(ui->dial_speed, SIGNAL(valueChanged(int)), ui->disp_speed, SLOT(display(int)));


    connect(ui->end, SIGNAL(clicked()), qApp, SLOT(quit()));

    common::GetInstance().lidar_rad = ui->lidarrad->text().trimmed().toInt();

    // load image added
    on = new QPixmap(":/images/off.png");
    off = new QPixmap(":/images/on.png");

    on_icon = new QIcon(*on);
    off_icon = new QIcon(*off);

    ui->start->setIcon(*on_icon);
    ui->start->setIconSize(ui->start->rect().size());

    bStart = false;

    view = new QWebEngineView(this);
    //view->setGeometry(100,10, 400,300);
    view->setGeometry(930,130,460,350);

    view->setUrl(QUrl("qrc:/map.html"));
    //view->setUrl(QUrl("http://192.168.101.3/test.html"));


    // mw add2
    // QDateTime 은 날짜시간을 가져오거나 관리하는 클래스
    // QDate / QTime 은 날짜 / 시간을 가져오거나 관리하는 클래스
    // QDateTimeEdit는 날짜시간을 표시하거나 수정하는 클래스
    QDateTimeEdit *dateEdit = new QDateTimeEdit(QDate::currentDate(), this);
    dateEdit->setMinimumDate(QDate::currentDate().addDays(-365)); // 수정 범위 지정
    dateEdit->setMaximumDate(QDate::currentDate().addDays(365)); // 수정 범위 지정
    dateEdit->setDisplayFormat("yyyy.MM.dd hh:mm:ss");
    dateEdit->setGeometry(0,0,300,50);


    // mw add3
    QTabWidget *tab = new QTabWidget(this);
    tab->resize(100,100); // 탭 위젯 사이즈
    QWidget* widget = new QWidget();
    widget->resize(50,50);
    QPushButton* push = new QPushButton(widget);
    tab->addTab(widget, "widget");
    // 탭위젯은 탭 위젯 안에 위젯을 넣는 것입니다.
    // 별도의 위젯 클래스를 두고 그 위젯을 넣는 것입니다.

}

cont::~cont()
{
    delete ui;

    delete on;   //added
    delete off;  //added

    delete on_icon;  //added
    delete off_icon; //added
}

void cont::connectDevice()
{
    emit connLidar(ui->carip->text().trimmed(), ui->lidarport->text().trimmed());
    emit connCam(ui->carip->text().trimmed(), ui->camport->text().trimmed());
    emit connImu(ui->carip->text().trimmed(), ui->sonarport->text().trimmed());
    emit connSonar(ui->carip->text().trimmed(), ui->imuport->text().trimmed());
}

void cont::disconnectDevice()
{
    emit disconn();
}

void cont::on_accel_clicked()
{
    if(common::GetInstance().iGear == 1 || common::GetInstance().iGear == 3)
    {
        if(common::GetInstance().iSpeed < 240)
        {
            common::GetInstance().iSpeed += 1;
        }
    }
}

void cont::on_brake_clicked()
{
    if(common::GetInstance().iSpeed > 0)
    {
        common::GetInstance().iSpeed -= 1;
    }
}

void cont::on_left_clicked()
{
    common::GetInstance().bRightOn = false;
    common::GetInstance().bLeftOn = !common::GetInstance().bLeftOn;
    if(common::GetInstance().bEmgrOn != true)
    {
        common::GetInstance().iL_On_DispCnt = 0;
    }
}

void cont::on_right_clicked()
{
    common::GetInstance().bLeftOn = false;
    common::GetInstance().bRightOn = !common::GetInstance().bRightOn;
    if(common::GetInstance().bEmgrOn != true)
    {
        common::GetInstance().iR_On_DispCnt = 0;
    }
}

void cont::on_emgr_clicked()
{
    common::GetInstance().bEmgrOn = !common::GetInstance().bEmgrOn;
    common::GetInstance().iL_On_DispCnt = 0;
    common::GetInstance().iR_On_DispCnt = 0;
}

void cont::on_gear_valueChanged(int value)
{
    common::GetInstance().iGear = value;
}

void cont::on_lidarrad_textChanged(const QString &arg1)
{
    common::GetInstance().lidar_rad = ui->lidarrad->text().trimmed().toInt();
}

//added

void cont::on_start_clicked()
{
    if(bStart == true)
    {
        bStart = false;
        emit endSystem();
        ui->start->setIcon(*on_icon);
    }
    else
    {
        bStart = true;
        emit startSystem();
        ui->start->setIcon(*off_icon);
    }
}

void cont::on_map1_clicked()
{
    view->page()->runJavaScript("moveto(127.0347583,37.4992707);",[this](const QVariant &v)
        {
            qDebug()<<v.toString();
        }
    );
}

void cont::on_map2_clicked()
{
    view->page()->runJavaScript("moveto(127.0342583,37.4992700);",[this](const QVariant &v)
        {
            qDebug()<<v.toString();
        }
    );
}

void cont::on_horizontalSlider_actionTriggered(int action)
{
    // 오류 추가
}

void cont::on_progressBar_2_valueChanged(int value)
{
    // 오류 추가
}
