#ifndef HEATCASCADE_H
#define HEATCASCADE_H

#include <QDialog>
#include "stream.h"
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsItem>


namespace Ui {
class HeatCascade;
}

class HeatCascade : public QDialog
{
    Q_OBJECT

public:
    explicit HeatCascade(QWidget *parent = 0);
    ~HeatCascade();
    void giveData(std::vector<Stream> streamvect, std::vector<double> pboundaries, QMap<double, double> pheatBalance);

private slots:
    void on_pushButton_clicked();

private:
    Ui::HeatCascade *ui;
    std::vector<Stream> streams;
    std::vector<double> boundaries;
    QMap<double, double> heatBalance;
    QGraphicsScene *scene, *scene_2;
    double qHminOpposite = 0, qCmin = 0, pinch;
};

#endif // HEATCASCADE_H
