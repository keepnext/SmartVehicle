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
    QLabel *value;
    QLineEdit *sensorip;
    QLabel *value2;
    QPushButton *conn;
    QLineEdit *sensorport;
    QLabel *sensor;
    QLabel *label;

    void setupUi(QWidget *Imu)
    {
        if (Imu->objectName().isEmpty())
            Imu->setObjectName(QString::fromUtf8("Imu"));
        Imu->resize(465, 481);
        value = new QLabel(Imu);
        value->setObjectName(QString::fromUtf8("value"));
        value->setGeometry(QRect(66, 50, 381, 20));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(value->sizePolicy().hasHeightForWidth());
        value->setSizePolicy(sizePolicy);
        sensorip = new QLineEdit(Imu);
        sensorip->setObjectName(QString::fromUtf8("sensorip"));
        sensorip->setGeometry(QRect(144, 15, 113, 25));
        value2 = new QLabel(Imu);
        value2->setObjectName(QString::fromUtf8("value2"));
        value2->setGeometry(QRect(66, 80, 341, 17));
        sizePolicy.setHeightForWidth(value2->sizePolicy().hasHeightForWidth());
        value2->setSizePolicy(sizePolicy);
        conn = new QPushButton(Imu);
        conn->setObjectName(QString::fromUtf8("conn"));
        conn->setGeometry(QRect(6, 10, 131, 31));
        sensorport = new QLineEdit(Imu);
        sensorport->setObjectName(QString::fromUtf8("sensorport"));
        sensorport->setGeometry(QRect(266, 15, 61, 25));
        sensor = new QLabel(Imu);
        sensor->setObjectName(QString::fromUtf8("sensor"));
        sensor->setGeometry(QRect(16, 100, 431, 371));
        sensor->setAutoFillBackground(false);
        sensor->setFrameShape(QFrame::Box);
        label = new QLabel(Imu);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(16, 50, 141, 17));

        retranslateUi(Imu);

        QMetaObject::connectSlotsByName(Imu);
    } // setupUi

    void retranslateUi(QWidget *Imu)
    {
        Imu->setWindowTitle(QApplication::translate("Imu", "IMU", nullptr));
        value->setText(QApplication::translate("Imu", "YPR : 0000, 0000, 0000", nullptr));
        sensorip->setText(QApplication::translate("Imu", "192.168.0.22", nullptr));
        value2->setText(QApplication::translate("Imu", "Yaw : 0000, Pitch : 0000, Roll : 0000", nullptr));
        conn->setText(QApplication::translate("Imu", "IMU \354\240\234\354\226\264\352\270\260 \354\227\260\352\262\260", nullptr));
        sensorport->setText(QApplication::translate("Imu", "9003", nullptr));
        sensor->setText(QString());
        label->setText(QApplication::translate("Imu", "IMU : ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Imu: public Ui_Imu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMU_H
