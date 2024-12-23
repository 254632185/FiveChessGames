
#include "chessgame.h"
#include "mainwindow.h"
#include <QApplication>

#include "regis.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
