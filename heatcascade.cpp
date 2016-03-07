#include "heatcascade.h"
#include "ui_heatcascade.h"

#include <iostream>
#include "results.h"
#include <QMessageBox>

#define ROWHIGHT 20
#define SHIFT 40

HeatCascade::HeatCascade(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HeatCascade)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene_2 = new QGraphicsScene(this);
    ui->graphicsView_2->setScene(scene_2);

}

HeatCascade::~HeatCascade()
{
    delete ui;
}

void HeatCascade::giveData (std::vector<Stream> streamvect, std::vector<double> pboundaries, QMap<double, double> pheatBalance){
    streams=streamvect;
    boundaries=pboundaries;
    heatBalance=pheatBalance;

    QPen blackPen(Qt::black);

    int index = 0;

    int diagramHigh = boundaries.size()*2*ROWHIGHT-1;
    int diagramWidth = 4*SHIFT;

    QGraphicsLineItem *line;
    QGraphicsTextItem *textDiagramData;

    for(QMap<double, double>::iterator i = heatBalance.end()-1; i != heatBalance.begin()-1; i--, index++){
        textDiagramData=scene->addText(QString::number(i.key())+" (°C)");
        textDiagramData->setX(-diagramWidth/2);
        textDiagramData->setY(-diagramHigh/2+(index*2)*ROWHIGHT);
        qCmin = qCmin + i.value();
        if(qHminOpposite > qCmin){
            qHminOpposite = qCmin;
            pinch = i.key();
        }
        textDiagramData=scene->addText(QString::number(qCmin)+" (kW)");
        textDiagramData->setX(-diagramWidth/2+SHIFT*3);
        textDiagramData->setY(-diagramHigh/2+(index*2)*ROWHIGHT);

        if(index==0){

        } else {
            if(i.value()>0){
                textDiagramData=scene->addText("(+"+QString::number(i.value())+")");
            }else{
                textDiagramData=scene->addText("("+QString::number(i.value())+")");
            }
            textDiagramData->setX(-diagramWidth/2+SHIFT);
            textDiagramData->setY(-diagramHigh/2+(index*2-1)*ROWHIGHT);
            line = scene->addLine(-diagramWidth/2+SHIFT*3, -diagramHigh/2-1*ROWHIGHT+(index*2)*ROWHIGHT, -diagramWidth/2+SHIFT*2, -diagramHigh/2-1.5*ROWHIGHT+(index*2+1)*ROWHIGHT, blackPen);
            line = scene->addLine(-diagramWidth/2+SHIFT*2, -diagramHigh/2-1*ROWHIGHT+(index*2+1)*ROWHIGHT, -diagramWidth/2+SHIFT*3, -diagramHigh/2+0.5*ROWHIGHT+(index*2)*ROWHIGHT, blackPen);
        }
    }

    qCmin = -qHminOpposite;
    index=0;
    for(QMap<double, double>::iterator i = heatBalance.end()-1; i != heatBalance.begin()-1; i--, index++){
        textDiagramData=scene_2->addText(QString::number(i.key())+" (°C)");
        textDiagramData->setX(-diagramWidth/2);
        textDiagramData->setY(-diagramHigh/2+(index*2)*ROWHIGHT);
        qCmin = qCmin + i.value();


        textDiagramData=scene_2->addText(QString::number(qCmin)+" (kW)");
        textDiagramData->setX(-diagramWidth/2+SHIFT*3);
        textDiagramData->setY(-diagramHigh/2+(index*2)*ROWHIGHT);

        if(index==0){

        } else {
            if(i.value()>0){
                textDiagramData=scene_2->addText("(+"+QString::number(i.value())+")");
            }else{
                textDiagramData=scene_2->addText("("+QString::number(i.value())+")");
            }
            textDiagramData->setX(-diagramWidth/2+SHIFT);
            textDiagramData->setY(-diagramHigh/2+(index*2-1)*ROWHIGHT);
            line = scene_2->addLine(-diagramWidth/2+SHIFT*3, -diagramHigh/2-1*ROWHIGHT+(index*2)*ROWHIGHT, -diagramWidth/2+SHIFT*2, -diagramHigh/2-1.5*ROWHIGHT+(index*2+1)*ROWHIGHT, blackPen);
            line = scene_2->addLine(-diagramWidth/2+SHIFT*2, -diagramHigh/2-1*ROWHIGHT+(index*2+1)*ROWHIGHT, -diagramWidth/2+SHIFT*3, -diagramHigh/2+0.5*ROWHIGHT+(index*2)*ROWHIGHT, blackPen);
        }
    }
}

void HeatCascade::on_pushButton_clicked()
{
    if(qCmin <= 0 || qHminOpposite >= 0){
        QMessageBox::warning(this, "", "There is not pinch");

    }else{
        Results r;
        r.giveData(streams, boundaries, heatBalance, qHminOpposite, qCmin, pinch);
        r.setModal(true);
        r.exec();
    }
}
