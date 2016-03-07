#ifndef INPUT_H
#define INPUT_H

#include "stream.h"

#include <QDialog>

namespace Ui {
class Input;
}

class Input : public QDialog
{
    Q_OBJECT

public:
    explicit Input(QWidget *parent = 0);
    ~Input();
    void setStreams(std::vector<Stream> *streamvect);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    std::vector<Stream> *streams;
    Ui::Input *ui;
};

#endif // INPUT_H
