#include "chessgame.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChessGame w;
    w.show();
    return a.exec();
}
