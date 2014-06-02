#include <QFileDialog>
#include <QFile>
#include <QTime>
#include "scorechanger.h"
#include "ui_scorechanger.h"
#include "dialog.h"

ScoreChanger::ScoreChanger(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ScoreChanger)
{
    ui->setupUi(this);
    QFile dPath("dpath.txt");
    if(!dPath.open(QIODevice::ReadOnly | QIODevice::Text))
        this->path = "";
    else{
        this->path = dPath.readLine();
    }
    dPath.close();

    QFile mapList("Map List.txt");
    mapList.open(QIODevice::ReadOnly | QIODevice::Text);

    while(!mapList.atEnd()){

        QString data = mapList.readLink();
        ui->comboMap->addItem(data);
    }


}

ScoreChanger::~ScoreChanger()
{
    delete ui;
}

QString ScoreChanger::getNameBLU()const{
    return ui->nameBLU->text();
}

QString ScoreChanger::getNameRED()const{
    return ui->nameRED->text();
}

int ScoreChanger::getPointBLU() const{
    return ui->pointBLU->text().toInt();
}

int ScoreChanger::getPointRED() const{
    return ui->pointRED->text().toInt();
}

QString ScoreChanger::getMap()const{
    return ui->comboMap->currentText();
}

void ScoreChanger::on_actionPath_triggered()
{
    this->path = QFileDialog::getExistingDirectory(this,  tr("Files Directory"));
    QFile dPath("dpath.txt");
    dPath.open(QIODevice::WriteOnly | QIODevice::Text);
    dPath.write(this->path.toUtf8());
    dPath.close();
}



void ScoreChanger::on_nameBLU_textChanged(const QString &arg1) //changes the teamBLU txt file
{
    ui->nameBLU->setText(arg1);
    QFile teamBLU(this->path+"/TeamBlu.txt");
    teamBLU.open(QIODevice::WriteOnly | QIODevice::Text);
        QByteArray ba = arg1.toUtf8();

        teamBLU.write(ba);
        teamBLU.close();
}

void ScoreChanger::on_nameRED_textChanged(const QString &arg1) // changes the teamRED txt file
{
    ui->nameRED->setText(arg1);
    QFile teamRED(this->path+"/TeamRed.txt");
    teamRED.open(QIODevice::WriteOnly | QIODevice::Text);
        QByteArray ba = arg1.toUtf8();
        teamRED.write(ba);
        teamRED.close();
}

void ScoreChanger::on_pointBLU_valueChanged(const QString &arg1) //changes the pointBLU txt file
{
    QFile point(this->path+"/pontoblu.txt");
    point.open(QIODevice::WriteOnly | QIODevice::Text);
    QByteArray data = arg1.toUtf8();
    point.write(data);
    ui->act->setText("Updated.");
}

void ScoreChanger::on_pointRED_valueChanged(const QString &arg1) //changes the pointRED txt file
{
    QFile point(this->path+"/pontored.txt");
    point.open(QIODevice::WriteOnly | QIODevice::Text);
    QByteArray data = arg1.toUtf8();
    point.write(data);
    ui->act->setText("Updated.");

}

void ScoreChanger::on_resetScore_clicked()
{
    QFile pointred(this->path+"/pontored.txt");
    QFile pointblu(this->path+"/pontoblu.txt");
    pointred.open(QIODevice::WriteOnly | QIODevice::Text);
    pointblu.open(QIODevice::WriteOnly | QIODevice::Text);
    pointred.write("0");
    pointblu.write("0");
    ui->pointBLU->setValue(0);
    ui->pointRED->setValue(0);

    ui->act->setText("Score Reseted!");

}

void ScoreChanger::on_swap_clicked()
{
    QString aux;
    aux = getNameBLU();
    setTeamBLU(getNameRED());
    setTeamRED(aux);
    ui->act->setText("Swap made.");
}

void ScoreChanger::setTeamBLU(const QString &blu){
    ui->nameBLU->setText(blu);
    QFile teamBLU(this->path+"/TeamBlu.txt");
    teamBLU.open(QIODevice::WriteOnly | QIODevice::Text);
        QByteArray ba = blu.toUtf8();

        teamBLU.write(ba);
        teamBLU.close();

}

void ScoreChanger::setTeamRED(const QString &red){
    ui->nameRED->setText(red);
    QFile teamRED(this->path+"/TeamRed.txt");
    teamRED.open(QIODevice::WriteOnly | QIODevice::Text);
        QByteArray ba = red.toUtf8();
        teamRED.write(ba);
        teamRED.close();
}


void ScoreChanger::on_endMatch_clicked()
{
    QFile mapScore(this->path+"/Map score.txt");
    mapScore.open(QIODevice::WriteOnly | QIODevice::Text);
    QString space = " ";
    QString x = " x ";
    QString symbol = " •\n";
    QString dots = ": ";

    mapScore.write(getMap().toUtf8());
    mapScore.write(dots.toUtf8());
    mapScore.write(getNameBLU().toUtf8());
    mapScore.write(space.toUtf8());
    mapScore.write(ui->pointBLU->text().toUtf8());
    mapScore.write(x.toUtf8());
    mapScore.write(ui->pointRED->text().toUtf8());
    mapScore.write(space.toUtf8());
    mapScore.write(getNameRED().toUtf8());
    mapScore.write(symbol.toUtf8());

   // out<< getMap() <<": "<< getNameBLU() << " " << getPointBLU() << " x " << getPointRED() << " " << getNameRED()<<" •\n ";



    //save last team names
    QFile teamRed(this->path+"/TeamRed_fim.txt");
    if(teamRed.exists()){
        teamRed.open(QIODevice::WriteOnly | QIODevice::Text);
        QByteArray data = getNameRED().toUtf8();
        teamRed.write(data);
    }else{
        teamRed.rename(this->path+"/TeamRed.txt", this->path+"/TeamRed_fim.txt");
    }
    teamRed.close();

    QFile teamBlu(this->path+"/TeamBlu_fim.txt");
    if(teamBlu.exists()){
        teamBlu.open(QIODevice::WriteOnly | QIODevice::Text);
        QByteArray data = getNameBLU().toUtf8();
        teamBlu.write(data);
    }else{
        teamBlu.rename(this->path+"/TeamBlu.txt", this->path+"/TeamBlu_fim.txt");
    }
    teamBlu.close();

    QFile map(this->path+"/map_fim.txt");

    if(map.exists()){//TODO VOLTAR AQUI
        map.open(QIODevice::WriteOnly | QIODevice::Text);
        QByteArray data = ui->comboMap->currentText().toUtf8();
        map.write(data);
    }else{
        map.rename(this->path+"/map.txt", this->path+"/map_fim.txt");
    }
     map.close();

    //save last results
    QFile pointRed(this->path+"/pontored_fim.txt");
    if(pointRed.exists()){
        pointRed.open(QIODevice::WriteOnly | QIODevice::Text);
        QByteArray data = ui->pointRED->text().toUtf8();
        pointRed.write(data);
    }else{
        pointRed.rename(this->path+"/pontored.txt", this->path+"/pontored_fim.txt");
    }
    pointRed.close();

    QFile pointBlu(this->path+"/pontoblu_fim.txt");

    if(pointBlu.exists()){
        pointBlu.open(QIODevice::WriteOnly | QIODevice::Text);
        QByteArray data = ui->pointBLU->text().toUtf8();
        pointBlu.write(data);
    }else{
        pointBlu.rename(this->path+"/pontoblu.txt", this->path+"/pontoblu_fim.txt");
    }
    pointBlu.close();
    ui->comboMap->setCurrentIndex(0);
    resetScore();
    ui->act->setText("Match Ended.");
}

//void ScoreChanger::on_comboBox_currentTextChanged(const QString &arg1)
//{
  //  QFile map(this->path+"/map.txt");
    //map.open(QIODevice::WriteOnly | QIODevice::Text);
    //QByteArray data = arg1.toUtf8();
    //map.write(data);
    //ui->act->setText("Updated.");
//}

void ScoreChanger::resetScore(){
    QFile pointred(this->path+"/pontored.txt");
    QFile pointblu(this->path+"/pontoblu.txt");
    pointred.open(QIODevice::WriteOnly | QIODevice::Text);
    pointblu.open(QIODevice::WriteOnly | QIODevice::Text);
    pointred.write("0");
    pointblu.write("0");
    ui->pointBLU->setValue(0);
    ui->pointRED->setValue(0);
}

//STREAMSETTINGS

void ScoreChanger::on_statsEdit_textChanged(const QString &arg1)
{
    QFile logs(this->path+"/Stats link.txt");
    logs.open(QIODevice::WriteOnly | QIODevice::Text);
    QByteArray data = arg1.toUtf8();
    logs.write(data);
    ui->act->setText("Updated.");
}

void ScoreChanger::on_narratorEdit_textChanged(const QString &arg1)
{
    ui->act->setText("Updating.");
    QFile narrator(this->path+"/Narrator.txt");
    narrator.open(QIODevice::WriteOnly | QIODevice::Text);
    QByteArray data = arg1.toUtf8();
    narrator.write(data);
    ui->act->setText("Updated.");

    QFile commentator(this->path+"/Narrators.txt");
    commentator.open(QIODevice::WriteOnly | QIODevice::Text);
    commentator.write("");
    commentator.close();

    commentator.open(QIODevice::Append | QIODevice::Text);

    QString symbol =" & ";
    commentator.write(ui->narratorEdit->text().toUtf8());

    if(ui->camera->text() != ""){
    commentator.write(symbol.toUtf8());
    commentator.write(ui->commentatorEdit->text().toUtf8());
    }
}

void ScoreChanger::on_cameraEdit_textChanged(const QString &arg1)
{
    QFile camera(this->path+"/Camera.txt");
    camera.open(QIODevice::WriteOnly | QIODevice::Text);
    QByteArray data = arg1.toUtf8();
    camera.write(data);
    ui->act->setText("Updated.");
}


void ScoreChanger::on_commentatorEdit_textChanged(const QString &arg1)
{
    ui->act->setText("Updating.");
    QFile comm(this->path+"/Commentator.txt");
    comm.open(QIODevice::WriteOnly | QIODevice::Text);
    QByteArray data = arg1.toUtf8();
    comm.write(data);
    ui->act->setText("Updated.");

    QFile commentator(this->path+"/Narrators.txt");
    commentator.open(QIODevice::WriteOnly | QIODevice::Text);
    commentator.write("");
    commentator.close();

    commentator.open(QIODevice::Append | QIODevice::Text);

    QString symbol =" & ";
    commentator.write(ui->narratorEdit->text().toUtf8());

    if(ui->camera->text() != ""){
    commentator.write(symbol.toUtf8());
    commentator.write(ui->commentatorEdit->text().toUtf8());
    }
}

void ScoreChanger::on_titleEdit_textChanged(const QString &arg1)
{
    QFile title(this->path+"/Title.txt");
    title.open(QIODevice::WriteOnly | QIODevice::Text);
    QByteArray data = arg1.toUtf8();
    title.write(data);
    title.close();
}

void ScoreChanger::on_timeEdit_timeChanged()
{
    QFile shedule(this->path+"/Schedule.txt");
    shedule.open(QIODevice::WriteOnly | QIODevice::Text);
    QByteArray data = ui->timeEdit->text().toUtf8();
    shedule.write(data);
    shedule.close();
}

void ScoreChanger::on_comboMap_currentTextChanged(const QString &arg1)
{
    QFile map(this->path+"/map.txt");
    map.open(QIODevice::WriteOnly | QIODevice::Text);
    QByteArray data = arg1.toUtf8();
    map.write(data);
    ui->act->setText("Updated.");
}

void ScoreChanger::on_toolButton_clicked()
{
    Dialog nMap;
    nMap.setWindowTitle("Add");
    nMap.exec();
    ui->comboMap->addItem(nMap.nMap);
    QFile maps("Map List.txt");
    maps.open(QIODevice::Append | QIODevice::Text);
    maps.write(nMap.nMap.toUtf8()+"\n");
    maps.close();
}
