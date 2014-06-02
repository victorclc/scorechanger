#ifndef SCORECHANGER_H
#define SCORECHANGER_H

#include <QMainWindow>
#include "popout.h"
namespace Ui {
class ScoreChanger;
}

class ScoreChanger : public QMainWindow
{
    Q_OBJECT

public:
    explicit ScoreChanger(QWidget *parent = 0);
    ~ScoreChanger();

    QString getNameBLU() const;
    QString getNameRED() const;
    QString getMap() const;
    int getPointBLU() const;
    int getPointRED() const;

    void resetScore();
    void setTeamBLU(const QString &blu);
    void setTeamRED(const QString &red);
    void setAddMap(const QString &map);

private slots:
    void on_actionPath_triggered();

    void on_nameBLU_textChanged(const QString &arg1);

    void on_nameRED_textChanged(const QString &arg1);

    void on_pointBLU_valueChanged(const QString &arg1);

    void on_pointRED_valueChanged(const QString &arg1);

    void on_resetScore_clicked();

    void on_swap_clicked();

    void on_endMatch_clicked();

   // void on_comboBox_currentTextChanged(const QString &arg1);

    void on_statsEdit_textChanged(const QString &arg1);

    void on_narratorEdit_textChanged(const QString &arg1);

    void on_cameraEdit_textChanged(const QString &arg1);

    void on_commentatorEdit_textChanged(const QString &arg1);

    void on_titleEdit_textChanged(const QString &arg1);

    void on_timeEdit_timeChanged();

    void on_comboMap_currentTextChanged(const QString &arg1);

    void on_toolButton_clicked();

private:
    Ui::ScoreChanger *ui;
    QString path;
    QString addMap;
};

#endif // SCORECHANGER_H
