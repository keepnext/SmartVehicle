/********************************************************************************
** Form generated from reading UI file 'imu.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMU_H
#define UI_IMU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Imu
{
public:
    QPushButton *conn;
    QLineEdit *sensorip;
    QLineEdit *sensorport;
    QLabel *label;
    QLabel *value;
    QLabel *value2;
    QLabel *sensor;

    void setupUi(QWidget *Imu)
    {
        if (Imu->objectName().isEmpty())
            Imu->setObjectName(QString::fromUtf8("Imu"));
        Imu->resize(500, 600);
        conn = new QPushButton(Imu);
        conn->setObjectName(QString::fromUtf8("conn"));
        conn->setGeometry(QRect(30, 30, 120, 30));
        sensorip = new QLineEdit(Imu);
        sensorip->setObjectName(QString::fromUtf8("sensorip"));
        sensorip->setGeometry(QRect(180, 30, 121, 30));
        sensorip->setAlignment(Qt::AlignCenter);
        sensorport = new QLineEdit(Imu);
        sensorport->setObjectName(QString::fromUtf8("sensorport"));
        sensorport->setGeometry(QRect(310, 30, 61, 30));
        sensorport->setAlignment(Qt::AlignCenter);
        label = new QLabel(Imu);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 80, 67, 17));
        value = new QLabel(Imu);
        value->setObjectName(QString::fromUtf8("value"));
        value->setGeometry(QRect(80, 80, 380, 17));
        value2 = new QLabel(Imu);
        value2->setObjectName(QString::fromUtf8("value2"));
        value2->setGeometry(QRect(80, 110, 380, 17));
        sensor = new QLabel(Imu);
        sensor->setObjectName(QString::fromUtf8("sensor"));
        sensor->setGeometry(QRect(40, 150, 410, 410));
        sensor->setFrameShape(QFrame::Box);

        retranslateUi(Imu);

        QMetaObject::connectSlotsByName(Imu);
    } // setupUi

    void retranslateUi(QWidget *Imu)
    {
        Imu->setWindowTitle(QApplication::translate("Imu", "Widget", nullptr));
        conn->setText(QApplication::translate("Imu", "IMU \354\240\234\354\226\264\352\270\260 \354\227\260\352\262\260", nullptr));
        sensorip->setText(QApplication::translate("Imu", "192.168.101.12", nullptr));
        sensorport->setText(QApplication::translate("Imu", "9003", nullptr));
        label->setText(QApplication::translate("Imu", "[IMU]", nullptr));
        value->setText(QApplication::translate("Imu", "#YPR=000.00,000.00,000.00", nullptr));
        value2->setText(QApplication::translate("Imu", "YAW : 000.00   Pitch : 000.00   ROLL : 000.00", nullptr));
        sensor->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Imu: public Ui_Imu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMU_H
