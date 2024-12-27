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
    // 设置窗口的尺寸
    setMinimumSize(600, 800);
    setMaximumSize(600, 800);

    ui->setupUi(this);
    this->setWindowTitle("用户注册");
    ui->let_passwd1->setEchoMode(QLineEdit::Password);
    ui->let_passwd2->setEchoMode(QLineEdit::Password);

    // 设置用户名输入框
    ui->lineEdit_4->setGeometry(QRect(200, 200, 200, 30));
    ui->label_3->setGeometry(QRect(120, 200, 70, 30));

    // 设置密码输入框
    ui->let_passwd1->setGeometry(QRect(200, 250, 200, 30));
    ui->label_4->setGeometry(QRect(120, 250, 70, 30));

    // 设置密码重输入框
    ui->let_passwd2->setGeometry(QRect(200, 300, 200, 30));
    ui->lab_5->setGeometry(QRect(120, 300, 70, 30));

    // 设置显示密码复选框
    ui->radioButton->setGeometry(QRect(420, 250, 150, 30));

    // 设置重显示密码复选框
    ui->radioButton_2->setGeometry(QRect(420, 300, 150, 30));

    // 设置注册按钮
    ui->btn_inlog->setGeometry(QRect(200, 350, 100, 50));

    // 设置退出按钮
    ui->btn_quit->setGeometry(QRect(400, 350, 100, 50));
}

regis::~regis()
{
    delete ui;
}

//跳转到登录界面
void regis::on_btn_inlog_clicked()
{
    QString str1 = ui->let_passwd1->text();
    QString str2 = ui->let_passwd2->text();
    if (str1 != str2) {
        QMessageBox::warning(this, "警告", "两次输入不同");
        return;
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
    if (checked) {
        ui->let_passwd1->setEchoMode(QLineEdit::Normal);
    } else {
        ui->let_passwd1->setEchoMode(QLineEdit::Password);
    }
}

void regis::on_radioButton_2_clicked(bool checked)
{
    if (checked) {
        ui->let_passwd2->setEchoMode(QLineEdit::Normal);
    } else {
        ui->let_passwd2->setEchoMode(QLineEdit::Password);
    }
}

