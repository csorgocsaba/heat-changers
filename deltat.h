#ifndef DELTAT_H
#define DELTAT_H

#include <QDialog>
#include "stream.h"
#include "vector"

namespace Ui {
class DeltaT;
}

class DeltaT : public QDialog
{
    Q_OBJECT

public:
    explicit DeltaT(QWidget *parent = 0);
    ~DeltaT();
    void setStreams(std::vector<Stream> *streamvect);

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::DeltaT *ui;
    std::vector<Stream> *streams;
};

#endif // DELTAT_H
