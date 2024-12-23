#include "regis.h"
#include "ui_regis.h"
#include "chessgame.h"
#include "mainwindow.h"
#include <QString>
#include <QMessageBox>


regis::regis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::regis)
{
    ui->setupUi(this);
    this->setWindowTitle("用户注册");

    ui->let_passwd1->setEchoMode(QLineEdit::Normal);
    ui->let_passwd2->setEchoMode(QLineEdit::Normal);
}

regis::~regis()
{
    delete ui;
}

//跳转到登录界面
void regis::on_btn_inlog_clicked()
{
    QString str1=ui->let_passwd1->text();
    QString str2=ui->let_passwd1->text();
    int i=QString::compare(str1,str2);
    if(i)
    {
        QMessageBox::about(this,"警告","两次输入不同");
    }

    MainWindow *w = new MainWindow();
    w->show();
    this->hide();

}

//退出
void regis::on_btn_quit_clicked()
{
    this->close();
}



void regis::on_radioButton_clicked(bool checked)
{
    if(checked)
    {
        //显示Normal, NoEcho, Password, PasswordEchoOnEdit
        ui->let_passwd1->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->let_passwd1->setEchoMode(QLineEdit::Password);
    }
}

void regis::on_radioButton_2_clicked(bool checked)
{
    if(checked)
    {
        //显示Normal, NoEcho, Password, PasswordEchoOnEdit
        ui->let_passwd2->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->let_passwd2->setEchoMode(QLineEdit::Password);
    }
}
