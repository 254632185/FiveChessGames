#include "regis.h"
#include "ui_regis.h"
#include "mainwindow.h"
#include "chessgame.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QRegExp>

regis::regis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::regis)
{
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

    // 连接信号与槽
    connect(ui->radioButton, SIGNAL(clicked(bool)), this, SLOT(on_radioButton_clicked(bool)));
    connect(ui->radioButton_2, SIGNAL(clicked(bool)), this, SLOT(on_radioButton_2_clicked(bool)));
}

regis::~regis()
{
    delete ui;
}

void regis::on_btn_inlog_clicked()
{
    QString username = ui->lineEdit_4->text();
    QString str1 = ui->let_passwd1->text();
    QString str2 = ui->let_passwd2->text();

    if (str1 != str2) {
        QMessageBox::warning(this, "警告", "两次输入不同");
        return;
    }

    if (!validateUsername(username)) {
        QMessageBox::warning(this, "无效的用户名", "用户名只能包含字母和数字，长度不超过6个字符。");
        return;
    }

    if (!validatePassword(str1)) {
        QMessageBox::warning(this, "无效的密码", "密码只能包含字母和数字，长度在6到12个字符之间。");
        return;
    }

    saveUser(username, str1);
    MainWindow *w = new MainWindow();
    w->show();
    this->hide();
}

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

bool regis::validateUsername(const QString &username)
{
    QRegExp usernameRegex("^[a-zA-Z0-9]{1,6}$");
    return usernameRegex.exactMatch(username);
}

bool regis::validatePassword(const QString &password)
{
    QRegExp passwordRegex("^[a-zA-Z0-9]{6,12}$");
    return passwordRegex.exactMatch(password);
}

void regis::saveUser(const QString &username, const QString &password)
{
    QFile file("users.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "无法保存用户信息");
        return;
    }

    QTextStream out(&file);
    out << username << "," << password << "\n";
    file.close();
}
