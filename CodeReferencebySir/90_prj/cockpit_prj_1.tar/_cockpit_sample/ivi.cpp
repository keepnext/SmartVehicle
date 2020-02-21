#include "ivi.h"
#include "ui_ivi.h"

ivi::ivi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ivi)
{
    ui->setupUi(this);


    // load image
    on = new QPixmap(":/images/off.png");
    off = new QPixmap(":/images/on.png");

    on_icon = new QIcon(*on);
    off_icon = new QIcon(*off);

    ui->start->setIcon(*on_icon);
    ui->start->setIconSize(ui->start->rect().size());

    bStart = false;
}

ivi::~ivi()
{
    delete ui;

    delete on;
    delete off;

    delete on_icon;
    delete off_icon;
}

void ivi::on_start_clicked()
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
