#ifndef IVI_H
#define IVI_H

#include <QWidget>
#include <QIcon>

namespace Ui {
class ivi;
}

class ivi : public QWidget
{
    Q_OBJECT

public:
    explicit ivi(QWidget *parent = nullptr);
    ~ivi();

signals:
    void startSystem();
    void endSystem();

private slots:
    void on_start_clicked();

private:
    bool bStart;
    Ui::ivi *ui;

    QPixmap* on;
    QPixmap* off;

    QIcon* on_icon;
    QIcon* off_icon;
};

#endif // IVI_H
