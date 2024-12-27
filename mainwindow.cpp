#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "regis.h"
#include "chessgame.h"
#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // 设置窗口的尺寸
    setMinimumSize(600, 800);
    setMaximumSize(600, 800);

    ui->setupUi(this);
    this->setWindowTitle("用户登录");
    ui->let_passwd1->setEchoMode(QLineEdit::Password);

    // 设置用户名输入框
    ui->let_name->setGeometry(QRect(180, 170, 200, 50));
    ui->label->setGeometry(QRect(120, 170, 200, 50));

    // 设置密码输入框
    ui->let_passwd1->setGeometry(QRect(180, 250, 200, 50));
    ui->label_2->setGeometry(QRect(130, 250, 200, 50));

    // 设置显示密码复选框
    ui->radioButton->setGeometry(QRect(400, 250, 200, 50));

    // 设置登录按钮
    ui->btn_inlog->setGeometry(QRect(100, 350, 100, 50));

    // 设置注册按钮
    ui->but_reg->setGeometry(QRect(250, 350, 100, 50));

    // 设置退出按钮
    ui->but_quit->setGeometry(QRect(400, 350, 100, 50));
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
        // 显示Normal, NoEcho, Password, PasswordEchoOnEdit
        ui->let_passwd1->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->let_passwd1->setEchoMode(QLineEdit::Password);
    }
}

