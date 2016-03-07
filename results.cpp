#include "results.h"
#include "ui_results.h"

#include "design.h"

Results::Results(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Results)
{
    ui->setupUi(this);
}

Results::~Results()
{
    delete ui;
}

void Results::giveData(std::vector<Stream> streamvect, std::vector<double> pboundaries, QMap<double, double> pheatBalance, double pQHminOpposite, double pQCmin, double pPinch){
    qHmin = -pQHminOpposite;
    qCmin = pQCmin;
    pinch = pPinch;
    streams = streamvect;
    boundaries=pboundaries;
    double deltaTmin = streams.begin()->getDeltaTmin();

    ui->label_6->setText(QString::number(qHmin)+" kW");
    ui->label_7->setText(QString::number(qCmin)+" kW");
    ui->label_8->setText(QString::number(pinch)+" °C");
    ui->label_9->setText(QString::number(pinch+deltaTmin/2)+" °C");
    ui->label_10->setText(QString::number(pinch-deltaTmin/2)+" °C");
}


void Results::on_pushButton_clicked()
{
    Design d;
    d.giveData(streams, boundaries, pinch);
    d.setModal(true);
    d.exec();
}
