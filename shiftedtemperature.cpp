#include "shiftedtemperature.h"
#include "ui_shiftedtemperature.h"

#include <iostream>
#include <QTextEdit>

ShiftedTemperature::ShiftedTemperature(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShiftedTemperature)
{
    ui->setupUi(this);
    QStringList header, empty;
    header /*<< "No." */<< "type" << "Ts\n(°C)" << "Tt\n(°C)" << "T*s\n(°C)" << "T*t\n(°C)" << "CP\n(kW/°C)";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    empty<<"";
    ui->tableWidget_2->setColumnCount(1);
    ui->tableWidget_3->setColumnCount(1);
    ui->tableWidget_2->setHorizontalHeaderLabels(empty);
    ui->tableWidget_3->setHorizontalHeaderLabels(empty);
}

ShiftedTemperature::~ShiftedTemperature()
{
    delete ui;
}

void ShiftedTemperature::setStreams(std::vector<Stream> streamvect){
    streams=streamvect;
    std::cout<<"Run ShiftedTemperature::setStreams"<<std::endl;
    int idx = 1 ;
    std::vector<double> candidateBoundaries;
    for(std::vector<Stream>::iterator j = streams.begin(); j!=streams.end(); j++, idx++){
        double Ts, Tt, ATs, ATt, HCF;
        QString Type;
        if(j->getType()){
            Type="Hot";
        } else{
            Type="Cold";
        }
        Ts=j->getTS();
        Tt=j->getTT();
        ATs=j->getATS();
        ATt=j->getATT();
        HCF=j->getHCF();
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        //ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(QString::number(idx)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(Type));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(QString::number(Ts)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, new QTableWidgetItem(QString::number(Tt)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3, new QTableWidgetItem(QString::number(ATs)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 4, new QTableWidgetItem(QString::number(ATt)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 5, new QTableWidgetItem(QString::number(HCF)));
        candidateBoundaries.push_back(ATs);
        candidateBoundaries.push_back(ATt);
    }
    QString deltaTmin = QString::number(streams.begin()->getDeltaTmin())+" (°C)";
    ui->label_7->setText(deltaTmin);
    std::cout<<idx<<std::endl;
    int row = (idx-1)*2;
    std::cout<<row<<std::endl;
    //ui->tableWidget_2->setColumnCount(1);

    ui->tableWidget_2->setRowCount(row);
    //ui->tableWidget_3->setColumnCount(1);
    ui->tableWidget_3->setRowCount(row);

    std::sort(candidateBoundaries.rbegin(), candidateBoundaries.rend());

    for(int j = 0; j<(int)candidateBoundaries.size(); j++){
        ui->tableWidget_2->setItem(j, 0, new QTableWidgetItem(QString::number(candidateBoundaries[j])));
        if(j==0){
            boundaries.push_back(candidateBoundaries[j]);
        }else{
            if(candidateBoundaries[j]!=candidateBoundaries[j-1]){
                boundaries.push_back(candidateBoundaries[j]);
            }
        }
    }
    for(int j = 0; j<(int)boundaries.size(); j++){
        ui->tableWidget_3->setItem(j, 0, new QTableWidgetItem(QString::number(boundaries[j])));
    }
}


void ShiftedTemperature::on_pushButton_clicked()
{
    ProblemTable p;
    p.giveData(streams, boundaries);
    p.setModal(true);
    p.exec();
}
