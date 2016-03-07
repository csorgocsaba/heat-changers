#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "input.h"
#include "stream.h"
#include "shiftedtemperature.h"
#include <vector>
#include <iostream>
#include <QTextStream>
#include "deltat.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ide vannak beégetve a streamek
    /*Stream stream;
    stream.setDeltaTmin(10);
    stream.setType(true);
    stream.setTS(180);
    stream.setTT(80);
    stream.setHCF(20);
    stream.setATS();
    stream.setATT();
    streams.push_back(stream);

    stream.setType(false);
    stream.setTS(60);
    stream.setTT(100);
    stream.setHCF(80);
    stream.setATS();
    stream.setATT();
    streams.push_back(stream);

    stream.setType(true);
    stream.setTS(130);
    stream.setTT(40);
    stream.setHCF(40);
    stream.setATS();
    stream.setATT();
    streams.push_back(stream);

    stream.setType(false);
    stream.setTS(30);
    stream.setTT(120);
    stream.setHCF(36);
    stream.setATS();
    stream.setATT();
    streams.push_back(stream);*/

    Stream stream;
    stream.setDeltaTmin(50);
    stream.setType(true);
    stream.setTS(750);
    stream.setTT(350);
    stream.setHCF(45);
    stream.setATS();
    stream.setATT();
    streams.push_back(stream);

    stream.setType(true);
    stream.setTS(550);
    stream.setTT(250);
    stream.setHCF(40);
    stream.setATS();
    stream.setATT();
    streams.push_back(stream);

    stream.setType(false);
    stream.setTS(300);
    stream.setTT(900);
    stream.setHCF(43);
    stream.setATS();
    stream.setATT();
    streams.push_back(stream);

    stream.setType(false);
    stream.setTS(200);
    stream.setTT(550);
    stream.setHCF(20);
    stream.setATS();
    stream.setATT();
    streams.push_back(stream);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Input i;
    i.setStreams(&streams);
    i.setModal(true);
    i.exec();
    //i = new Input(this);
    //i->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    ShiftedTemperature s;
    s.setStreams(streams);
    s.setModal(true);
    s.exec();
    std::cout<<"No.\tType\tTs\tTt\tT*s\tT*t\tCP"<<std::endl;
    int idx = 1 ;
    for(std::vector<Stream>::iterator j = streams.begin(); j!=streams.end(); j++, idx++){
        int Ts, Tt, ATs, ATt, HCF;
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
        std::cout<<idx<<"\t";
        QTextStream(stdout) << Type <<"\t";
        std::cout<<Ts<<"\t"<<Tt<<"\t"<<ATs<<"\t"<<ATt<<"\t"<<HCF<<"\t"<<std::endl;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    DeltaT d;
    d.setStreams(&streams);
    d.setModal(true);
    d.exec();
}
