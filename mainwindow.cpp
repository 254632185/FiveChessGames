/*#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "chessgame.h"

#include<QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("用户登录");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_inlog_clicked()
{
    ChessGame *w = new ChessGame();
    w->show();
    this->hide();
}*/
