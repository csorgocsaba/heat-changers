#ifndef PROBLEMTABLE_H
#define PROBLEMTABLE_H

#include <QDialog>
#include "stream.h"
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include "shiftedtemperature.h"


namespace Ui {
class ProblemTable;
}

class ProblemTable : public QDialog
{
    Q_OBJECT

public:
    explicit ProblemTable(QWidget *parent = 0);
    ~ProblemTable();
    void giveData (std::vector<Stream> streamvect, std::vector<double> pboundaries);

private slots:
    void on_pushButton_clicked();

    //void on_pushButton_2_clicked();

private:
    Ui::ProblemTable *ui;
    std::vector<Stream> streams;
    std::vector<double> boundaries;
    QMap<double, double> heatBalance;
    QGraphicsScene *scene;
    //ShiftedTemperature s;
};

#endif // PROBLEMTABLE_H
