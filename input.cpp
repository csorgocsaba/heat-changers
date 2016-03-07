#include "input.h"
#include "ui_input.h"
#include "stream.h"
#include <iostream>

Input::Input(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Input)
{
    ui->setupUi(this);
}

Input::~Input()
{
    delete ui;
}

void Input::setStreams(std::vector<Stream> *streamvect){
    streams=streamvect;
    std::cout<<"Run Input::setStreams"<<std::endl;
}

void Input::on_pushButton_clicked()
{
    Stream *stream = new Stream;
    if(ui->radiobuttomHot->isChecked()){
        std::cout<<"HOT radio buttom is checked"<<std::endl;
        stream->setType(true);
    } else if(ui->radioButtonCold->isChecked()){
        std::cout<<"COLD radio buttom is checked"<<std::endl;
        stream->setType(false);
    } else{
        //TODO exception non data
    }
    stream->setTS(ui->lineEditTs->text().toDouble());
    stream->setTT(ui->lineEditTt->text().toDouble());
    stream->setHCF(ui->lineEditHCF->text().toDouble());
    stream->setATS();
    stream->setATT();
    streams->push_back(*stream);
    ui->lineEditTs->clear();
    ui->lineEditTt->clear();
    ui->lineEditHCF->clear();
}

void Input::on_pushButton_2_clicked()
{

}
