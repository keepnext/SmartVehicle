/********************************************************************************
** Form generated from reading UI file 'lidar_design.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIDAR_DESIGN_H
#define UI_LIDAR_DESIGN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_lidar_ui
{
public:
    QPushButton *connbtn;
    QLineEdit *serverip;
    QLineEdit *serverport;
    QLabel *label;
    QLabel *sensordata;
    QLabel *label_2;
    QLineEdit *angle;

    void setupUi(QWidget *lidar_ui)
    {
        if (lidar_ui->objectName().isEmpty())
            lidar_ui->setObjectName(QString::fromUtf8("lidar_ui"));
        lidar_ui->resize(400, 524);
        connbtn = new QPushButton(lidar_ui);
        connbtn->setObjectName(QString::fromUtf8("connbtn"));
        connbtn->setGeometry(QRect(20, 30, 89, 25));
        serverip = new QLineEdit(lidar_ui);
        serverip->setObjectName(QString::fromUtf8("serverip"));
        serverip->setGeometry(QRect(130, 30, 113, 25));
        serverport = new QLineEdit(lidar_ui);
        serverport->setObjectName(QString::fromUtf8("serverport"));
        serverport->setGeometry(QRect(280, 30, 113, 25));
        label = new QLabel(lidar_ui);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 100, 91, 20));
        sensordata = new QLabel(lidar_ui);
        sensordata->setObjectName(QString::fromUtf8("sensordata"));
        sensordata->setGeometry(QRect(130, 100, 251, 71));
        sensordata->setFrameShape(QFrame::Box);
        label_2 = new QLabel(lidar_ui);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(130, 70, 67, 17));
        angle = new QLineEdit(lidar_ui);
        angle->setObjectName(QString::fromUtf8("angle"));
        angle->setGeometry(QRect(198, 67, 113, 25));

        retranslateUi(lidar_ui);

        QMetaObject::connectSlotsByName(lidar_ui);
    } // setupUi

    void retranslateUi(QWidget *lidar_ui)
    {
        lidar_ui->setWindowTitle(QApplication::translate("lidar_ui", "Form", nullptr));
        connbtn->setText(QApplication::translate("lidar_ui", "connbtn", nullptr));
        serverip->setText(QApplication::translate("lidar_ui", "192.168.101.7", nullptr));
        serverport->setText(QApplication::translate("lidar_ui", "9004", nullptr));
        label->setText(QApplication::translate("lidar_ui", "LIDAR DATA:", nullptr));
        sensordata->setText(QApplication::translate("lidar_ui", "[0000_000|0000_000................]", nullptr));
        label_2->setText(QApplication::translate("lidar_ui", "\354\264\210\352\270\260\352\260\201\353\217\204:", nullptr));
        angle->setText(QApplication::translate("lidar_ui", "180", nullptr));
    } // retranslateUi

};

namespace Ui {
    class lidar_ui: public Ui_lidar_ui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIDAR_DESIGN_H
