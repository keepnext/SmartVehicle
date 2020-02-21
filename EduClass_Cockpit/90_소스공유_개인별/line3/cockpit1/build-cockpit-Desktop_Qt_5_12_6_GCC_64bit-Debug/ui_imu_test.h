/********************************************************************************
** Form generated from reading UI file 'imu_test.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMU_TEST_H
#define UI_IMU_TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_imu_test
{
public:
    QPushButton *conn;
    QLineEdit *serverip;
    QLineEdit *serverport;
    QLabel *data;
    QLabel *opengl;

    void setupUi(QWidget *imu_test)
    {
        if (imu_test->objectName().isEmpty())
            imu_test->setObjectName(QString::fromUtf8("imu_test"));
        imu_test->resize(400, 407);
        conn = new QPushButton(imu_test);
        conn->setObjectName(QString::fromUtf8("conn"));
        conn->setGeometry(QRect(30, 20, 89, 25));
        serverip = new QLineEdit(imu_test);
        serverip->setObjectName(QString::fromUtf8("serverip"));
        serverip->setGeometry(QRect(130, 20, 113, 25));
        serverport = new QLineEdit(imu_test);
        serverport->setObjectName(QString::fromUtf8("serverport"));
        serverport->setGeometry(QRect(260, 20, 113, 25));
        data = new QLabel(imu_test);
        data->setObjectName(QString::fromUtf8("data"));
        data->setGeometry(QRect(40, 70, 321, 31));
        opengl = new QLabel(imu_test);
        opengl->setObjectName(QString::fromUtf8("opengl"));
        opengl->setGeometry(QRect(20, 120, 351, 191));

        retranslateUi(imu_test);

        QMetaObject::connectSlotsByName(imu_test);
    } // setupUi

    void retranslateUi(QWidget *imu_test)
    {
        imu_test->setWindowTitle(QApplication::translate("imu_test", "Form", nullptr));
        conn->setText(QApplication::translate("imu_test", "PushButton", nullptr));
        serverip->setText(QApplication::translate("imu_test", "192.168.101.7", nullptr));
        serverport->setText(QApplication::translate("imu_test", "9004", nullptr));
        data->setText(QApplication::translate("imu_test", "TextLabel", nullptr));
        opengl->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class imu_test: public Ui_imu_test {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMU_TEST_H
