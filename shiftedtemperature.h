#ifndef SHIFTEDTEMPERATURE_H
#define SHIFTEDTEMPERATURE_H

#include <QDialog>
#include <vector>
#include "stream.h"
#include "problemtable.h"

namespace Ui {
class ShiftedTemperature;
}

class ShiftedTemperature : public QDialog
{
    Q_OBJECT

public:
    explicit ShiftedTemperature(QWidget *parent = 0);
    ~ShiftedTemperature();
    void setStreams(std::vector<Stream> streamvect);

private slots:

    void on_pushButton_clicked();

private:
    Ui::ShiftedTemperature *ui;
    std::vector<Stream> streams;
    std::vector<double> boundaries;
};

#endif // SHIFTEDTEMPERATURE_H
