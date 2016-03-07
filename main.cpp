#include "mainwindow.h"
#include <QApplication>
#include "stream.h"
#include <iostream>
#include <vector>

using namespace std;

/*struct streams{
    vector<Stream> streamvect;
};

void SaveStream(streams streamvector, Stream stream){
    streamvector.streamvect.push_back(stream);
}*/

int main(int argc, char *argv[])
{
    //streams streamvector;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return a.exec();
}
