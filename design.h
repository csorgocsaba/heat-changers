#ifndef DESIGN_H
#define DESIGN_H

#include <QDialog>
#include <stream.h>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsItem>

struct heatchanger{
    double hot;
    double cold;
    double kW;
    double temperature;
};

struct streamstruct{
    bool haveChanger = false;
    bool type;
    double min;
    double max;
    double capacity;
    double hight;
};

namespace Ui {
class Design;
}

class Design : public QDialog
{
    Q_OBJECT

public:
    explicit Design(QWidget *parent = 0);
    ~Design();
    void giveData(std::vector<Stream> streamvect, std::vector<double> pboundaries, double pPinch);

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::Design *ui;
    QGraphicsScene *scene;
    std::vector<Stream> streams;
    double pinch;
    double hPinch;
    double cPinch;
    std::vector<double> boundaries;
    QVector<streamstruct> aboveThePinch, caboveThePinch;
    QVector<streamstruct> belowThePinch, cbelowThePinch;
    QVector<heatchanger> heatchangers;
};

#endif // DESIGN_H
