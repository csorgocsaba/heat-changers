#include "deltat.h"
#include "ui_deltat.h"

DeltaT::DeltaT(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeltaT)
{
    ui->setupUi(this);
}

DeltaT::~DeltaT()
{
    delete ui;
}
void DeltaT::setStreams(std::vector<Stream> *streamvect){
    streams=streamvect;
}

void DeltaT::on_pushButton_2_clicked()
{
    streams->begin()->setDeltaTmin(ui->lineEdit->text().toDouble());
    for(std::vector<Stream>::iterator j = streams->begin(); j!=streams->end(); j++){
        j->setATT();
        j->setATS();
    }
}
