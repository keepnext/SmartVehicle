#include "widget.h"

#include <QDebug>
#include <QPushButton>
#include <QApplication>
#include <QAbstractButton>

int m_value = 0;
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->resize(100,100);
    QPushButton *btn = new QPushButton("exit", this);

    // lambda
    connect(btn, &QPushButton::clicked, [btn] { ++m_value; btn->setText(QString::number(m_value)); });

    // 단순화 예시
    //QObject::connect(btn, SIGNAL(clicked()), this, SLOT(slotExample()));
    //->connect(btn, SIGNAL(clicked()), this, SLOT(slotExample()));
    //->->connect(btn, SIGNAL(clicked()), SLOT(slotExample()));

    // emit 예시
    QPushButton *btn1 = new QPushButton("emit", this);
    QPushButton *btn2 = new QPushButton("target", this);
    btn1->move(0, 30);
    btn2->move(0, 60);
    connect(btn1, SIGNAL(clicked()), this, SLOT(emitSlot()));
    connect(btn2, SIGNAL(clicked()), this, SLOT(TargetSlot(int))); // 작동 안함
    connect(this, SIGNAL(sigCustom(int)), this, SLOT(TargetSlot(int)));
    //connect(btn2, &QPushButton::clicked, qApp, QApplication::quit); // static 만 사용 가능
}

Widget::~Widget()
{
}

void Widget::slotCustom(int i)
{
    qDebug() << i;
}

void Widget::slotExample()
{
    qDebug() << "Empty Function";
}

void Widget::emitSlot()
{
    qDebug() << "CALL emitSlot";
    emit TargetSlot(100);
    emit sigCustom(101);
}

void Widget::TargetSlot(int i)
{
    qDebug() << "CALL TargetSlot";
    qDebug() << i;
}


