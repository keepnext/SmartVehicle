#ifndef ULTRA_H
#define ULTRA_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Ultra; }
class QTcpSocket;
QT_END_NAMESPACE

class ultra : public QWidget
{
    Q_OBJECT

public:
    ultra(QWidget *parent = nullptr);
    ~ultra();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::Ultra *ui;
    QTcpSocket *tcpSocket;

    QString strRecved;
    int iUltraDist_in;
    int iUltraDist_cm;
    QString strMsg;
    void initialize();

private slots:
    void connectButton();
    void connected();
    void readMessage();
    void disconnected();
};
#endif // ULTRA_H
