#include "design.h"
#include "ui_design.h"
#include <iostream>

#define BLOWUP 2
#define SHIFT 50
#define SQUARESIZE 20


Design::Design(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Design)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
}

Design::~Design()
{
    delete ui;
}

void Design::giveData(std::vector<Stream> streamvect, std::vector<double> pboundaries, double pPinch){
    streams=streamvect;
    boundaries = pboundaries;
    pinch=pPinch;
    double deltaTmin = streams.begin()->getDeltaTmin(), hight=0, maxhight = streams.size()*25;
    double  endOfLine=boundaries[0]+deltaTmin;
    hPinch = pinch+deltaTmin/2, cPinch = pinch-deltaTmin/2;

    QPen redPen(Qt::red);
    QPen bluePen(Qt::blue);
    QPen blackPen(Qt::black);
    redPen.setWidth(4);
    bluePen.setWidth(4);
    QBrush whiteBrush(Qt::white);
    QBrush yellowBrush(Qt::yellow);
    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);


    QGraphicsLineItem *line;
    QGraphicsTextItem *textDiagramData, *textDiagramData_2;
    QGraphicsRectItem *square;
    QGraphicsEllipseItem *round;
//    QVector<streamstruct> aboveThePinch, caboveThePinch;
//    QVector<streamstruct> belowThePinch, cbelowThePinch;
//    QVector<heatchanger> heatchangers;

    for(int i = 0; i < (int)streams.size(); i++){
        if(streams[i].getType()){

            streamstruct astream;
            astream.type = true;
            astream.capacity = streams[i].getHCF();
            astream.hight = hight;
            astream.max = streams[i].getTS();
            if(streams[i].getTT()>hPinch){
                astream.min = streams[i].getTT();
            } else {
                astream.min = hPinch;
            }
            if(astream.max>hPinch){
                aboveThePinch.push_back(astream);
            }


            streamstruct bstream;
            bstream.type = true;
            bstream.capacity = streams[i].getHCF();
            bstream.hight = hight;
            bstream.min = streams[i].getTT();
            if(streams[i].getTS()>hPinch){
                bstream.max = hPinch;
            } else {
                bstream.max = streams[i].getTS();
            }
            if(bstream.min<hPinch){
                belowThePinch.push_back(bstream);
            }



            line = scene->addLine(streams[i].getTT()*BLOWUP+2, -maxhight+hight*SHIFT, streams[i].getTS()*BLOWUP, -maxhight+hight*SHIFT, redPen);
            line = scene->addLine(streams[i].getTT()*BLOWUP, -maxhight+hight*SHIFT, streams[i].getTT()*BLOWUP+SQUARESIZE*0.5, -maxhight+hight*SHIFT-SQUARESIZE*0.5, redPen);
            line = scene->addLine(streams[i].getTT()*BLOWUP, -maxhight+hight*SHIFT, streams[i].getTT()*BLOWUP+SQUARESIZE*0.5, -maxhight+hight*SHIFT+SQUARESIZE*0.5, redPen);

            square = scene->addRect(streams[i].getTS()*BLOWUP, -maxhight+hight*SHIFT-SQUARESIZE*0.5, SQUARESIZE, SQUARESIZE, redPen, whiteBrush);

            textDiagramData = scene->addText(QString::number(streams[i].getHCF())+" (kW/°C)");
            textDiagramData->setX(endOfLine*BLOWUP);
            textDiagramData->setY(-maxhight+hight*SHIFT-11);

            textDiagramData = scene->addText(QString::number(streams[i].getTS())+"°");
            textDiagramData->setX(streams[i].getTS()*BLOWUP-30);
            textDiagramData->setY(-maxhight+hight*SHIFT);

            textDiagramData = scene->addText(QString::number(streams[i].getTT())+"°");
            textDiagramData->setX(streams[i].getTT()*BLOWUP+10);
            textDiagramData->setY(-maxhight+hight*SHIFT);

            textDiagramData_2 = scene->addText(QString::number(i+1));
            textDiagramData_2->setX(streams[i].getTS()*BLOWUP+3);
            textDiagramData_2->setY(-maxhight+hight*SHIFT-11);
            hight++;
        }
    }

    line = scene->addLine(hPinch*BLOWUP, -maxhight-0.5*SHIFT, hPinch*BLOWUP, -maxhight+hight*SHIFT-0.5*SHIFT, blackPen);

    textDiagramData_2 = scene->addText(QString::number(hPinch)+"°");
    textDiagramData_2->setX(hPinch*BLOWUP);
    textDiagramData_2->setY(-maxhight+hight*SHIFT-30);

    textDiagramData_2 = scene->addText("Pinch");
    textDiagramData_2->setX(cPinch*BLOWUP);
    textDiagramData_2->setY(-maxhight+hight*SHIFT-10);

    textDiagramData_2 = scene->addText(QString::number(cPinch)+"°");
    textDiagramData_2->setX(cPinch*BLOWUP);
    textDiagramData_2->setY(-maxhight+hight*SHIFT+10);

    hight++;

    line = scene->addLine(cPinch*BLOWUP, -maxhight+hight*SHIFT-0.5*SHIFT, cPinch*BLOWUP, +maxhight+0.5*SHIFT, blackPen);

    for(int i = 0; i < (int)streams.size(); i++){
        if(!streams[i].getType()){

            streamstruct astream;
            astream.type = false;
            astream.capacity = streams[i].getHCF();
            astream.hight = hight;
            astream.max = streams[i].getTT();
            if(streams[i].getTS()>cPinch){
                astream.min = streams[i].getTS();
            } else {
                astream.min = cPinch;
            }
            if(astream.max>cPinch){
                caboveThePinch.push_back(astream);
            }


            streamstruct bstream;
            bstream.type = false;
            bstream.capacity = streams[i].getHCF();
            bstream.hight = hight;
            bstream.min = streams[i].getTS();
            if(streams[i].getTT()>cPinch){
                bstream.max = cPinch;
            } else {
                bstream.max = streams[i].getTT();
            }
            if(bstream.min<cPinch){
                cbelowThePinch.push_back(bstream);
            }

            line = scene->addLine(streams[i].getTT()*BLOWUP-2, -maxhight+hight*SHIFT, streams[i].getTS()*BLOWUP, -maxhight+hight*SHIFT, bluePen);
            line = scene->addLine(streams[i].getTT()*BLOWUP, -maxhight+hight*SHIFT, streams[i].getTT()*BLOWUP-SQUARESIZE*0.5, -maxhight+hight*SHIFT-SQUARESIZE*0.5, bluePen);
            line = scene->addLine(streams[i].getTT()*BLOWUP, -maxhight+hight*SHIFT, streams[i].getTT()*BLOWUP-SQUARESIZE*0.5, -maxhight+hight*SHIFT+SQUARESIZE*0.5, bluePen);

            square = scene->addRect(streams[i].getTS()*BLOWUP-SQUARESIZE, -maxhight+hight*SHIFT-SQUARESIZE*0.5, SQUARESIZE, SQUARESIZE, bluePen, whiteBrush);

            textDiagramData = scene->addText(QString::number(streams[i].getHCF())+" (kW/°C)");
            textDiagramData->setX(endOfLine*BLOWUP);
            textDiagramData->setY(-maxhight+hight*SHIFT-11);

            textDiagramData = scene->addText(QString::number(streams[i].getTS())+"°");
            textDiagramData->setX(streams[i].getTS()*BLOWUP);
            textDiagramData->setY(-maxhight+hight*SHIFT);

            textDiagramData = scene->addText(QString::number(streams[i].getTT())+"°");
            textDiagramData->setX(streams[i].getTT()*BLOWUP-40);
            textDiagramData->setY(-maxhight+hight*SHIFT);

            textDiagramData = scene->addText(QString::number(i+1));
            textDiagramData->setX(streams[i].getTS()*BLOWUP-16);
            textDiagramData->setY(-maxhight+hight*SHIFT-11);
            hight++;
        }
    }

    while(caboveThePinch.size() > aboveThePinch.size()){
        int hot = -1, cold = -1;
        double coldMinQ = 1.0/0.0, hotMaxCP = 0, newHotCP;
        for(int h = 0; h < aboveThePinch.size(); h++){
            if(!aboveThePinch[h].haveChanger && aboveThePinch[h].capacity>hotMaxCP){
                hotMaxCP = aboveThePinch[h].capacity;
                hot = h;
            }
        }

        for(int c = 0; c < caboveThePinch.size(); c++){
            double length = (caboveThePinch[c].max-caboveThePinch[c].min);
            if(length*caboveThePinch[c].capacity<coldMinQ){
                coldMinQ = length*caboveThePinch[c].capacity;
                cold = c;
            }
        }
        double length = (aboveThePinch[hot].max - aboveThePinch[hot].min);
        newHotCP=coldMinQ/length;
        aboveThePinch[hot].capacity = aboveThePinch[hot].capacity-newHotCP;

        streamstruct astream;
        astream.type= false;
        astream.min=aboveThePinch[hot].min;
        astream.max=aboveThePinch[hot].max;
        astream.capacity=newHotCP;
        astream.hight=aboveThePinch[hot].hight+0.5;
        aboveThePinch.push_back(astream);

        line = scene->addLine(astream.min*BLOWUP-2, -maxhight+astream.hight*SHIFT, astream.max*BLOWUP, -maxhight+astream.hight*SHIFT, redPen);
        line = scene->addLine(astream.min*BLOWUP-2, -maxhight+astream.hight*SHIFT, astream.min*BLOWUP-2, -maxhight+aboveThePinch[hot].hight*SHIFT, redPen);
        line = scene->addLine(astream.max*BLOWUP, -maxhight+astream.hight*SHIFT, astream.max*BLOWUP, -maxhight+aboveThePinch[hot].hight*SHIFT, redPen);

        textDiagramData = scene->addText(QString::number(astream.capacity)+" (kW/°C)");
        textDiagramData->setX(astream.max *BLOWUP+36);
        textDiagramData->setY(-maxhight+astream.hight*SHIFT-11);

        textDiagramData = scene->addText(QString::number(aboveThePinch[hot].capacity)+" (kW/°C)");
        textDiagramData->setX(aboveThePinch[hot].max *BLOWUP+36);
        textDiagramData->setY(-maxhight+aboveThePinch[hot].hight*SHIFT-11);
    }

    while(belowThePinch.size() > cbelowThePinch.size()){
        int hot = -1, cold = -1;
        double hotMinQ = 1.0/0.0, coldMaxCP = 0, newColdCP;
        for(int c = 0; c < cbelowThePinch.size(); c++){
            if(!cbelowThePinch[c].haveChanger && cbelowThePinch[c].capacity>coldMaxCP){
                coldMaxCP = cbelowThePinch[c].capacity;
                cold = c;
            }
        }

        for(int h = 0; h < belowThePinch.size(); h++){
            double length = (belowThePinch[h].max-belowThePinch[h].min);
            if(length*belowThePinch[h].capacity<hotMinQ){
                hotMinQ = length*belowThePinch[h].capacity;
                hot = h;
            }
        }
        double length = (cbelowThePinch[cold].max - cbelowThePinch[cold].min);
        newColdCP=hotMinQ/length;
        cbelowThePinch[cold].capacity = cbelowThePinch[cold].capacity-newColdCP;
        std::cout<<"cbelowThePinch[cold].capacity = "<<cbelowThePinch[cold].capacity<<std::endl;
        std::cout<<"newColdCP = "<<newColdCP<<std::endl;

        streamstruct astream;
        astream.type= false;
        astream.min=cbelowThePinch[cold].min;
        astream.max=cbelowThePinch[cold].max;
        astream.capacity=newColdCP;
        astream.hight=cbelowThePinch[cold].hight+0.5;
        cbelowThePinch.push_back(astream);

        line = scene->addLine(astream.min*BLOWUP-2, -maxhight+astream.hight*SHIFT, astream.max*BLOWUP, -maxhight+astream.hight*SHIFT, bluePen);
        line = scene->addLine(astream.min*BLOWUP-2, -maxhight+astream.hight*SHIFT, astream.min*BLOWUP-2, -maxhight+cbelowThePinch[cold].hight*SHIFT, bluePen);
        line = scene->addLine(astream.max*BLOWUP, -maxhight+astream.hight*SHIFT, astream.max*BLOWUP, -maxhight+cbelowThePinch[cold].hight*SHIFT, bluePen);

        textDiagramData = scene->addText(QString::number(astream.capacity)+" (kW/°C)");
        textDiagramData->setX(astream.min *BLOWUP-146);
        textDiagramData->setY(-maxhight+astream.hight*SHIFT-11);

        textDiagramData = scene->addText(QString::number(cbelowThePinch[cold].capacity)+" (kW/°C)");
        textDiagramData->setX(cbelowThePinch[cold].min *BLOWUP-146);
        textDiagramData->setY(-maxhight+cbelowThePinch[hot].hight*SHIFT-11);
    }



    std::cout<<std::endl<<"aboveThePinch";
    for(int a = 0; a < aboveThePinch.size(); a++){
        std::cout<<aboveThePinch[a].min<<"\t"<<aboveThePinch[a].max<<"\t"<<aboveThePinch[a].capacity<<"\t"<<aboveThePinch[a].hight<<std::endl;
    }
    std::cout<<std::endl<<"belowThePinch";
    for(int b = 0 ; b <belowThePinch.size(); b++){
        std::cout<<belowThePinch[b].min<<"\t"<<belowThePinch[b].max<<"\t"<<belowThePinch[b].capacity<<"\t"<<belowThePinch[b].hight<<std::endl;
    }

    std::cout<<std::endl<<"caboveThePinch";

    for(int a = 0; a < aboveThePinch.size(); a++){
        std::cout<<caboveThePinch[a].min<<"\t"<<caboveThePinch[a].max<<"\t"<<caboveThePinch[a].capacity<<"\t"<<caboveThePinch[a].hight<<std::endl;
    }
    std::cout<<std::endl<<"cbelowThePinc";
    for(int b = 0 ; b <belowThePinch.size(); b++){
        std::cout<<cbelowThePinch[b].min<<"\t"<<cbelowThePinch[b].max<<"\t"<<cbelowThePinch[b].capacity<<"\t"<<cbelowThePinch[b].hight<<std::endl;
    }

 /*   bool w = true;

        while(w){
            int hot = -1, cold = -1, hotMaxCP = 0, coldMaxCP = 0;
            for(int h = 0; h < belowThePinch.size(); h++){
                if(!belowThePinch[h].haveChanger && belowThePinch[h].capacity>hotMaxCP){
                    hotMaxCP = belowThePinch[h].capacity;
                    hot = h;
                }
            }
            for(int c = 0; c < cbelowThePinch.size(); c++){
                if(!cbelowThePinch[c].haveChanger && cbelowThePinch[c].capacity>coldMaxCP){
                    coldMaxCP = cbelowThePinch[c].capacity;
                    cold = c;
                }
            }

            if(cold!=-1 && hot!=-1){
                heatchanger changer;
                changer.hot = belowThePinch[hot].hight;
                changer.cold = cbelowThePinch[cold].hight;
                int hotCP = (belowThePinch[hot].max - belowThePinch[hot].min)*belowThePinch[hot].capacity;
                int coldCP = (cbelowThePinch[cold].max - cbelowThePinch[cold].min)*cbelowThePinch[cold].capacity;
                if(hotCP > coldCP){
                    changer.kW = coldCP;
                    changer.temperature = belowThePinch[hot].max-changer.kW/belowThePinch[hot].capacity;
                } else {
                    changer.kW = hotCP;
                    changer.temperature = cbelowThePinch[cold].min+changer.kW/cbelowThePinch[cold].capacity;
                }
                heatchangers.push_back(changer);
                belowThePinch[hot].haveChanger = true;
                belowThePinch[hot].max = changer.temperature;
                cbelowThePinch[cold].haveChanger = true;
            }
            if(cold==-1 || hot==-1){
                w = false;
            }
        }

    w = true;

    while(w){
        int hot = -1, cold = -1, hotMaxCP = 0, coldMaxCP = 0;
        for(int h = 0; h < aboveThePinch.size(); h++){
            if(!aboveThePinch[h].haveChanger && aboveThePinch[h].capacity>hotMaxCP){
                hotMaxCP = aboveThePinch[h].capacity;
                hot = h;
            }
        }
        for(int c = 0; c < caboveThePinch.size(); c++){
            if(!caboveThePinch[c].haveChanger && caboveThePinch[c].capacity>coldMaxCP){
                coldMaxCP = caboveThePinch[c].capacity;
                cold = c;
            }
        }

        if(cold!=-1 && hot!=-1){
            heatchanger changer;
            changer.hot = aboveThePinch[hot].hight;
            changer.cold = caboveThePinch[cold].hight;
            int hotCP = (aboveThePinch[hot].max - aboveThePinch[hot].min)*aboveThePinch[hot].capacity;
            int coldCP = (caboveThePinch[cold].max - caboveThePinch[cold].min)*caboveThePinch[cold].capacity;
            if(hotCP > coldCP){
                changer.kW = coldCP;
                changer.temperature = aboveThePinch[hot].max-changer.kW/aboveThePinch[hot].capacity;
            } else {
                changer.kW = hotCP;
                changer.temperature = caboveThePinch[cold].min+changer.kW/caboveThePinch[cold].capacity;
            }
            heatchangers.push_back(changer);
            aboveThePinch[hot].haveChanger = true;
            caboveThePinch[cold].haveChanger = true;
            caboveThePinch[cold].min = changer.temperature;
        }
        if(cold==-1 || hot==-1){
            w = false;
        }
    }

    for(int i = 0; i < heatchangers.size(); i++){
        line = scene->addLine(heatchangers[i].temperature*BLOWUP, -maxhight+heatchangers[i].cold*SHIFT, heatchangers[i].temperature*BLOWUP, -maxhight+heatchangers[i].hot*SHIFT, blackPen);
        round = scene->addEllipse(heatchangers[i].temperature*BLOWUP-0.5*SQUARESIZE, -maxhight+heatchangers[i].cold*SHIFT-0.5*SQUARESIZE, SQUARESIZE, SQUARESIZE, blackPen, yellowBrush);
        textDiagramData = scene->addText(QString::number(i+1));
        textDiagramData->setX(heatchangers[i].temperature*BLOWUP-6);
        textDiagramData->setY(-maxhight+heatchangers[i].cold*SHIFT-11);

        textDiagramData = scene->addText(QString::number(heatchangers[i].temperature)+"°C");
        textDiagramData->setX(heatchangers[i].temperature*BLOWUP-16);
        textDiagramData->setY(-maxhight+heatchangers[i].cold*SHIFT+11);

        round = scene->addEllipse(heatchangers[i].temperature*BLOWUP-0.5*SQUARESIZE, -maxhight+heatchangers[i].hot*SHIFT-0.5*SQUARESIZE, SQUARESIZE, SQUARESIZE, blackPen, yellowBrush);
        textDiagramData = scene->addText(QString::number(i+1));
        textDiagramData->setX(heatchangers[i].temperature*BLOWUP-6);
        textDiagramData->setY(-maxhight+heatchangers[i].hot*SHIFT-11);
    }

    for(int i = 0; i < belowThePinch.size(); i++){
        if(belowThePinch[i].max!=belowThePinch[i].min){
            round = scene->addEllipse((belowThePinch[i].min+(belowThePinch[i].max-belowThePinch[i].min)/2)*BLOWUP-0.5*SQUARESIZE, -maxhight+belowThePinch[i].hight*SHIFT-0.5*SQUARESIZE, SQUARESIZE, SQUARESIZE, bluePen, whiteBrush);
            textDiagramData = scene->addText("C");
            textDiagramData->setX((belowThePinch[i].min+(belowThePinch[i].max-belowThePinch[i].min)/2)*BLOWUP-6);
            textDiagramData->setY(-maxhight+belowThePinch[i].hight*SHIFT-11);
            textDiagramData = scene->addText(QString::number(belowThePinch[i].capacity*(belowThePinch[i].max-belowThePinch[i].min))+"kW");
            textDiagramData->setX((belowThePinch[i].min+(belowThePinch[i].max-belowThePinch[i].min)/2)*BLOWUP-16);
            textDiagramData->setY(-maxhight+belowThePinch[i].hight*SHIFT-30);
        }
    }

    for(int i = 0; i < caboveThePinch.size(); i++){
        if(caboveThePinch[i].max!=caboveThePinch[i].min){
            round = scene->addEllipse((caboveThePinch[i].min+(caboveThePinch[i].max-caboveThePinch[i].min)/2)*BLOWUP-0.5*SQUARESIZE, -maxhight+caboveThePinch[i].hight*SHIFT-0.5*SQUARESIZE, SQUARESIZE, SQUARESIZE, redPen, whiteBrush);
            textDiagramData = scene->addText("H");
            textDiagramData->setX((caboveThePinch[i].min+(caboveThePinch[i].max-caboveThePinch[i].min)/2)*BLOWUP-6);
            textDiagramData->setY(-maxhight+caboveThePinch[i].hight*SHIFT-11);
            textDiagramData = scene->addText(QString::number(caboveThePinch[i].capacity*(caboveThePinch[i].max-caboveThePinch[i].min))+"kW");
            textDiagramData->setX((caboveThePinch[i].min+(caboveThePinch[i].max-caboveThePinch[i].min)/2)*BLOWUP-16);
            textDiagramData->setY(-maxhight+caboveThePinch[i].hight*SHIFT-30);
        }
    }*/
}

void Design::on_pushButton_2_clicked()
{
    int maxhight = streams.size()*25;

    QPen redPen(Qt::red);
    QPen bluePen(Qt::blue);
    QPen blackPen(Qt::black);
    redPen.setWidth(4);
    bluePen.setWidth(4);
    QBrush whiteBrush(Qt::white);
    QBrush yellowBrush(Qt::yellow);
    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);


    QGraphicsLineItem *line;
    QGraphicsTextItem *textDiagramData, *textDiagramData_2;
    QGraphicsRectItem *square;
    QGraphicsEllipseItem *round;


    bool w = true;

        while(w){
            int hot = -1, cold = -1, hotMaxCP = 0, coldMaxCP = 0;
            for(int h = 0; h < belowThePinch.size(); h++){
                if(!belowThePinch[h].haveChanger && belowThePinch[h].capacity>hotMaxCP){
                    hotMaxCP = belowThePinch[h].capacity;
                    hot = h;
                }
            }
            for(int c = 0; c < cbelowThePinch.size(); c++){
                if(!cbelowThePinch[c].haveChanger && cbelowThePinch[c].capacity>coldMaxCP){
                    coldMaxCP = cbelowThePinch[c].capacity;
                    cold = c;
                }
            }

            if(cold!=-1 && hot!=-1){
                heatchanger changer;
                changer.hot = belowThePinch[hot].hight;
                changer.cold = cbelowThePinch[cold].hight;
                double hotCP = (belowThePinch[hot].max - belowThePinch[hot].min)*belowThePinch[hot].capacity;
                double coldCP = (cbelowThePinch[cold].max - cbelowThePinch[cold].min)*cbelowThePinch[cold].capacity;
                if(hotCP >= coldCP){
                    changer.kW = coldCP;
                    changer.temperature = belowThePinch[hot].max-changer.kW/belowThePinch[hot].capacity;
                } else {
                    changer.kW = hotCP;
                    changer.temperature = cbelowThePinch[cold].min+changer.kW/cbelowThePinch[cold].capacity;
                }
                heatchangers.push_back(changer);
                belowThePinch[hot].haveChanger = true;
                belowThePinch[hot].max = changer.temperature;
                cbelowThePinch[cold].haveChanger = true;
                cbelowThePinch[cold].min = changer.temperature;
            }
            if(cold==-1 || hot==-1){
                w = false;
            }
        }

    w = true;

    while(w){
        int hot = -1, cold = -1, hotMaxCP = 0, coldMaxCP = 0;
        for(int h = 0; h < aboveThePinch.size(); h++){
            if(!aboveThePinch[h].haveChanger && aboveThePinch[h].capacity>hotMaxCP){
                hotMaxCP = aboveThePinch[h].capacity;
                hot = h;
            }
        }
        for(int c = 0; c < caboveThePinch.size(); c++){
            if(!caboveThePinch[c].haveChanger && caboveThePinch[c].capacity>coldMaxCP){
                coldMaxCP = caboveThePinch[c].capacity;
                cold = c;
            }
        }

        if(cold!=-1 && hot!=-1){
            heatchanger changer;
            changer.hot = aboveThePinch[hot].hight;
            changer.cold = caboveThePinch[cold].hight;
            double hotCP = (aboveThePinch[hot].max - aboveThePinch[hot].min)*aboveThePinch[hot].capacity;
            double coldCP = (caboveThePinch[cold].max - caboveThePinch[cold].min)*caboveThePinch[cold].capacity;
            if(hotCP >= coldCP){
                changer.kW = coldCP;
                changer.temperature = aboveThePinch[hot].max-changer.kW/aboveThePinch[hot].capacity;
            } else {
                changer.kW = hotCP;
                changer.temperature = caboveThePinch[cold].min+changer.kW/caboveThePinch[cold].capacity;
            }
            heatchangers.push_back(changer);
            aboveThePinch[hot].haveChanger = true;
            caboveThePinch[cold].haveChanger = true;
            caboveThePinch[cold].min = changer.temperature;
            aboveThePinch[hot].max = changer.temperature;
        }
        if(cold==-1 || hot==-1){
            w = false;
        }
    }

    for(int i = 0; i < heatchangers.size(); i++){
        line = scene->addLine(heatchangers[i].temperature*BLOWUP, -maxhight+heatchangers[i].cold*SHIFT, heatchangers[i].temperature*BLOWUP, -maxhight+heatchangers[i].hot*SHIFT, blackPen);
        round = scene->addEllipse(heatchangers[i].temperature*BLOWUP-0.5*SQUARESIZE, -maxhight+heatchangers[i].cold*SHIFT-0.5*SQUARESIZE, SQUARESIZE, SQUARESIZE, blackPen, yellowBrush);
        textDiagramData = scene->addText(QString::number(i+1));
        textDiagramData->setX(heatchangers[i].temperature*BLOWUP-6);
        textDiagramData->setY(-maxhight+heatchangers[i].cold*SHIFT-11);

        textDiagramData = scene->addText(QString::number(heatchangers[i].temperature)+"°C");
        textDiagramData->setX(heatchangers[i].temperature*BLOWUP-16);
        textDiagramData->setY(-maxhight+heatchangers[i].cold*SHIFT+7);

        round = scene->addEllipse(heatchangers[i].temperature*BLOWUP-0.5*SQUARESIZE, -maxhight+heatchangers[i].hot*SHIFT-0.5*SQUARESIZE, SQUARESIZE, SQUARESIZE, blackPen, yellowBrush);
        textDiagramData = scene->addText(QString::number(i+1));
        textDiagramData->setX(heatchangers[i].temperature*BLOWUP-6);
        textDiagramData->setY(-maxhight+heatchangers[i].hot*SHIFT-11);

        textDiagramData = scene->addText(QString::number(heatchangers[i].kW)+"kW");
        textDiagramData->setX(heatchangers[i].temperature*BLOWUP-16);
        textDiagramData->setY(-maxhight+heatchangers[i].cold*SHIFT+19);
    }

    for(int i = 0; i < belowThePinch.size(); i++){
        if(belowThePinch[i].max!=belowThePinch[i].min){
            round = scene->addEllipse((belowThePinch[i].min+(belowThePinch[i].max-belowThePinch[i].min)/2)*BLOWUP-0.5*SQUARESIZE, -maxhight+belowThePinch[i].hight*SHIFT-0.5*SQUARESIZE, SQUARESIZE, SQUARESIZE, bluePen, whiteBrush);
            textDiagramData = scene->addText("C");
            textDiagramData->setX((belowThePinch[i].min+(belowThePinch[i].max-belowThePinch[i].min)/2)*BLOWUP-6);
            textDiagramData->setY(-maxhight+belowThePinch[i].hight*SHIFT-11);
            textDiagramData = scene->addText(QString::number(belowThePinch[i].capacity*(belowThePinch[i].max-belowThePinch[i].min))+"kW");
            textDiagramData->setX((belowThePinch[i].min+(belowThePinch[i].max-belowThePinch[i].min)/2)*BLOWUP-16);
            textDiagramData->setY(-maxhight+belowThePinch[i].hight*SHIFT-30);
        }
    }

    /*for(int i = 0; i < aboveThePinch.size(); i++){
        if(aboveThePinch[i].min>hPinch){
            if(aboveThePinch[i].max!=aboveThePinch[i].min){
                round = scene->addEllipse((aboveThePinch[i].min+(aboveThePinch[i].max-aboveThePinch[i].min)/2)*BLOWUP-0.5*SQUARESIZE, -maxhight+aboveThePinch[i].hight*SHIFT-0.5*SQUARESIZE, SQUARESIZE, SQUARESIZE, bluePen, whiteBrush);
                textDiagramData = scene->addText("C");
                textDiagramData->setX((aboveThePinch[i].min+(aboveThePinch[i].max-aboveThePinch[i].min)/2)*BLOWUP-6);
                textDiagramData->setY(-maxhight+aboveThePinch[i].hight*SHIFT-11);
                textDiagramData = scene->addText(QString::number(aboveThePinch[i].capacity*(aboveThePinch[i].max-aboveThePinch[i].min))+"kW");
                textDiagramData->setX((aboveThePinch[i].min+(aboveThePinch[i].max-aboveThePinch[i].min)/2)*BLOWUP-16);
                textDiagramData->setY(-maxhight+aboveThePinch[i].hight*SHIFT-30);
            }
        }
    }*/

    for(int i = 0; i < caboveThePinch.size(); i++){
        if(caboveThePinch[i].max!=caboveThePinch[i].min){
            round = scene->addEllipse((caboveThePinch[i].min+(caboveThePinch[i].max-caboveThePinch[i].min)/2)*BLOWUP-0.5*SQUARESIZE, -maxhight+caboveThePinch[i].hight*SHIFT-0.5*SQUARESIZE, SQUARESIZE, SQUARESIZE, redPen, whiteBrush);
            textDiagramData = scene->addText("H");
            textDiagramData->setX((caboveThePinch[i].min+(caboveThePinch[i].max-caboveThePinch[i].min)/2)*BLOWUP-6);
            textDiagramData->setY(-maxhight+caboveThePinch[i].hight*SHIFT-11);
            textDiagramData = scene->addText(QString::number(caboveThePinch[i].capacity*(caboveThePinch[i].max-caboveThePinch[i].min))+"kW");
            textDiagramData->setX((caboveThePinch[i].min+(caboveThePinch[i].max-caboveThePinch[i].min)/2)*BLOWUP-16);
            textDiagramData->setY(-maxhight+caboveThePinch[i].hight*SHIFT-30);
        }
    }

    /*for(int i = 0; i < cbelowThePinch.size(); i++){
        if(cbelowThePinch[i].max<cPinch){
            if(cbelowThePinch[i].max!=cbelowThePinch[i].min){
                round = scene->addEllipse((cbelowThePinch[i].min+(cbelowThePinch[i].max-cbelowThePinch[i].min)/2)*BLOWUP-0.5*SQUARESIZE, -maxhight+cbelowThePinch[i].hight*SHIFT-0.5*SQUARESIZE, SQUARESIZE, SQUARESIZE, redPen, whiteBrush);
                textDiagramData = scene->addText("H");
                textDiagramData->setX((cbelowThePinch[i].min+(cbelowThePinch[i].max-cbelowThePinch[i].min)/2)*BLOWUP-6);
                textDiagramData->setY(-maxhight+cbelowThePinch[i].hight*SHIFT-11);
                textDiagramData = scene->addText(QString::number(cbelowThePinch[i].capacity*(cbelowThePinch[i].max-cbelowThePinch[i].min))+"kW");
                textDiagramData->setX((cbelowThePinch[i].min+(cbelowThePinch[i].max-cbelowThePinch[i].min)/2)*BLOWUP-16);
                textDiagramData->setY(-maxhight+cbelowThePinch[i].hight*SHIFT-30);
            }
        }
    }*/

}
