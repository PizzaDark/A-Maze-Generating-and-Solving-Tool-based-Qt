#include "mainwindow.h"
#include "entrance.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Entrance w;
    w.show();
    return a.exec();
}
