#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "regis.h"
#include "chessgame.h"

#include<QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("用户登录");
    ui->let_passwd->setEchoMode(QLineEdit::Password);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//跳转到游戏界面
void MainWindow::on_btn_inlog_clicked()
{
    ChessGame *w = new ChessGame();
    w->show();
    this->hide();
}

//跳转到注册界面
void MainWindow::on_but_reg_clicked()
{
    regis *w = new regis();
    w->show();
    this->hide();
}

//退出
void MainWindow::on_but_quit_clicked()
{
    this->close();
}

//显示密码
void MainWindow::on_radioButton_clicked(bool checked)
{
    if(checked)
    {
        //显示Normal, NoEcho, Password, PasswordEchoOnEdit
        ui->let_passwd->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->let_passwd->setEchoMode(QLineEdit::Password);
    }
}
