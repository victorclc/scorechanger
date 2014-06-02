#ifndef POPOUT_H
#define POPOUT_H

#include <QWidget>

namespace Ui {
class popout;
}


class popout : public QWidget
{
    Q_OBJECT

public:
    explicit popout(QWidget *parent = 0);
    ~popout();

private slots:
    void on_pushButton_clicked();

private:
    Ui::popout *ui;
    QString newMap;
};

#endif // POPOUT_H
