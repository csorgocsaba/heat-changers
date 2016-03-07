#ifndef RESULTS_H
#define RESULTS_H

#include <QDialog>
#include "stream.h"


namespace Ui {
class Results;
}

class Results : public QDialog
{
    Q_OBJECT

public:
    explicit Results(QWidget *parent = 0);
    ~Results();
    void giveData(std::vector<Stream> streamvect, std::vector<double> pboundaries, QMap<double, double> pheatBalance, double pQHmin, double pQCmin, double pPinch);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Results *ui;
    std::vector<Stream> streams;
    std::vector<double> boundaries;
    //QMap<int, int> heatBalance;
    double qHmin, qCmin, pinch;
};

#endif // RESULTS_H
