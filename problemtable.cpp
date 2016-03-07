#include "problemtable.h"
#include "ui_problemtable.h"

#include <iostream>
#include "heatcascade.h"

#define COLUMNWIDTH 75
#define ROWHIGHT 25
#define SHIFT 15

ProblemTable::ProblemTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProblemTable)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);


}

ProblemTable::~ProblemTable()
{
    delete ui;
}

void ProblemTable::giveData(std::vector<Stream> streamvect, std::vector<double> pboundaries)
{
    streams = streamvect;
    boundaries = pboundaries;

    QBrush redBrush(Qt::red);
    QBrush yellowBrush(Qt::yellow);
    QPen blackPen(Qt::black);
//    blackPen.setWidth(6);
    QPen redPen(Qt::red);
    QPen bluePen(Qt::blue);
    QFont a("Times", 8);

    QGraphicsLineItem *line1, *line2, *line3, *tableB;
    QGraphicsTextItem *textTableHead, *textTableData;

    int tableHigh = (boundaries.size()+2)*ROWHIGHT;
    int tableWidth = (boundaries.size())*SHIFT+(5*COLUMNWIDTH);

//****************************************************************************************************
//Draw table and fill in the first column
//****************************************************************************************************
    for(int i=0; i<2; i++){
        tableB = scene->addLine(-tableWidth/2+i*COLUMNWIDTH, tableHigh/2, -tableWidth/2+i*COLUMNWIDTH, -tableHigh/2, blackPen);
    }
    for(int i=0; i<5; i++){
        tableB = scene->addLine(tableWidth/2-i*COLUMNWIDTH, tableHigh/2, tableWidth/2-i*COLUMNWIDTH, -tableHigh/2, blackPen);
    }
    tableB = scene->addLine(-tableWidth/2, -tableHigh/2, tableWidth/2, -tableHigh/2, blackPen);
    tableB = scene->addLine(-tableWidth/2, -tableHigh/2+2*ROWHIGHT, tableWidth/2, -tableHigh/2+2*ROWHIGHT, blackPen);
    for(int i=0; i<boundaries.size(); i++){
        tableB = scene->addLine(-tableWidth/2, -tableHigh/2+(i+3)*ROWHIGHT, tableWidth/2, -tableHigh/2+(i+3)*ROWHIGHT, blackPen);
        textTableData=scene->addText(QString::number(boundaries[i]));
        textTableData->setX(-tableWidth/2);
        textTableData->setY(-tableHigh/2+(i+2)*ROWHIGHT);
/*
 *  count and save heat balace
 */
        double deltaTinv, cp;
        if(i==0){
            heatBalance[boundaries[i]]=0;
        } else {
            cp=0;
            deltaTinv=boundaries[i-1]-boundaries[i];
            for(int j = 0; j < streams.size(); j++){
                if(streams[j].getType()){
                    if(streams[j].getATS()>boundaries[i-1]-1 && streams[j].getATT()<boundaries[i]+1){
                        cp = cp + streams[j].getHCF();
                        std::cout<<"meleg, cp = "<<cp<<std::endl;
                    }
                }
                if(!streams[j].getType()){
                    if(streams[j].getATS()<boundaries[i-1]-1 && streams[j].getATT()>boundaries[i]+1){
                        cp = cp -streams[j].getHCF();
                        std::cout<<"hideg, cp = "<<cp<<std::endl;
                    }
                }
            }
            double sumproduct = cp*deltaTinv;
            heatBalance[boundaries[i]]=sumproduct;
            std::cout<<boundaries[i]<<" "<<deltaTinv<<" * "<<cp<<" = "<<sumproduct<<std::endl;
/*
 * fill in the table
 */
            textTableData=scene->addText(QString::number(deltaTinv));
            textTableData->setX(tableWidth/2-4*COLUMNWIDTH);
            textTableData->setY(-tableHigh/2+(i+2)*ROWHIGHT);

            textTableData=scene->addText(QString::number(cp));
            textTableData->setX(tableWidth/2-3*COLUMNWIDTH);
            textTableData->setY(-tableHigh/2+(i+2)*ROWHIGHT);

            textTableData=scene->addText(QString::number(sumproduct));
            textTableData->setX(tableWidth/2-2*COLUMNWIDTH);
            textTableData->setY(-tableHigh/2+(i+2)*ROWHIGHT);
            if(deltaTinv*cp<0){
                textTableData=scene->addText("D");
                textTableData->setX(tableWidth/2-1*COLUMNWIDTH);
                textTableData->setY(-tableHigh/2+(i+2)*ROWHIGHT);
            } else{
                textTableData=scene->addText("S");
                textTableData->setX(tableWidth/2-1*COLUMNWIDTH);
                textTableData->setY(-tableHigh/2+(i+2)*ROWHIGHT);
            }
        }




    }
    tableB = scene->addLine(-tableWidth/2, tableHigh/2, tableWidth/2, tableHigh/2, blackPen);

//****************************************************************************************************
//Init head of table
//****************************************************************************************************

    textTableHead = scene->addText("Invertal\nTemperature");
    textTableHead->setX(-tableWidth/2);
    textTableHead->setY(-tableHigh/2);

    textTableHead = scene->addText("Stream\nPopulation");
    textTableHead->setX(-tableWidth/2+COLUMNWIDTH);
    textTableHead->setY(-tableHigh/2);

    textTableHead = scene->addText("deltaTinvertal");
    textTableHead->setX(tableWidth/2-4*COLUMNWIDTH);
    textTableHead->setY(-tableHigh/2);

    textTableHead = scene->addText("SUM CPH -\nSUM CPC");
    textTableHead->setX(tableWidth/2-3*COLUMNWIDTH);
    textTableHead->setY(-tableHigh/2);

    textTableHead = scene->addText("Heat\nBalance");
    textTableHead->setX(tableWidth/2-2*COLUMNWIDTH);
    textTableHead->setY(-tableHigh/2);

    textTableHead = scene->addText("Surplus\nDeficit");
    textTableHead->setX(tableWidth/2-1*COLUMNWIDTH);
    textTableHead->setY(-tableHigh/2);

//****************************************************************************************************
//Draw the lines
//****************************************************************************************************

    for(int i = 0; i < streams.size(); i++){
        QGraphicsLineItem *line;
        int arrowB, arrowE;
        for(int j = 0; j<boundaries.size(); j++){
            if(streams[i].getATS()==boundaries[j]){
                arrowB=j+1;
            }
            if(streams[i].getATT()==boundaries[j]){
                arrowE=j+1;
            }
        }
        if(streams[i].getType()){
            line = scene->addLine(-tableWidth/2+1*COLUMNWIDTH+(i+1)*SHIFT, -tableHigh/2+(arrowB+2)*ROWHIGHT, -tableWidth/2+1*COLUMNWIDTH+(i+1)*SHIFT, -tableHigh/2+(arrowE+2)*ROWHIGHT, redPen );
            line = scene->addLine(-tableWidth/2+1*COLUMNWIDTH+(i+1)*SHIFT+2, -tableHigh/2+(arrowE+2)*ROWHIGHT-5, -tableWidth/2+1*COLUMNWIDTH+(i+1)*SHIFT, -tableHigh/2+(arrowE+2)*ROWHIGHT, redPen );
            line = scene->addLine(-tableWidth/2+1*COLUMNWIDTH+(i+1)*SHIFT-2, -tableHigh/2+(arrowE+2)*ROWHIGHT-5, -tableWidth/2+1*COLUMNWIDTH+(i+1)*SHIFT, -tableHigh/2+(arrowE+2)*ROWHIGHT, redPen );
        } else {
            line = scene->addLine(-tableWidth/2+1*COLUMNWIDTH+(i+1)*SHIFT, -tableHigh/2+(arrowB+2)*ROWHIGHT, -tableWidth/2+1*COLUMNWIDTH+(i+1)*SHIFT, -tableHigh/2+(arrowE+2)*ROWHIGHT, bluePen );
            line = scene->addLine(-tableWidth/2+1*COLUMNWIDTH+(i+1)*SHIFT+2, -tableHigh/2+(arrowE+2)*ROWHIGHT+5, -tableWidth/2+1*COLUMNWIDTH+(i+1)*SHIFT, -tableHigh/2+(arrowE+2)*ROWHIGHT, bluePen );
            line = scene->addLine(-tableWidth/2+1*COLUMNWIDTH+(i+1)*SHIFT-2, -tableHigh/2+(arrowE+2)*ROWHIGHT+5, -tableWidth/2+1*COLUMNWIDTH+(i+1)*SHIFT, -tableHigh/2+(arrowE+2)*ROWHIGHT, bluePen );
        }
    }
}

void ProblemTable::on_pushButton_clicked()
{
    HeatCascade h;
    h.giveData(streams, boundaries, heatBalance);
    h.setModal(true);
    h.exec();
}

/*void ProblemTable::on_pushButton_2_clicked()
{
    s.setStreams(streams);
    s.setModal(true);
    s.exec();
}*/
