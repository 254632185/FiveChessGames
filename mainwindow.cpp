#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "regis.h"
#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QPalette>
#include <QPixmap>
#include <QDebug>

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
    ui->let_username->setGeometry(QRect(180, 170, 200, 50));
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

    // QComboBox 控件用于显示用户名列表
    cb_username = new QComboBox(this);
    cb_username->setGeometry(QRect(180, 170, 200, 50));  // 与 QLineEdit 同位置
    cb_username->hide();  // 初始隐藏 ComboBox

    // 连接信号和槽，确保当 ComboBox 值变化时同步 QLineEdit
    connect(cb_username, &QComboBox::currentTextChanged, ui->let_username, &QLineEdit::setText);

    // 连接信号和槽，确保当 QLineEdit 值变化时同步 ComboBox
    connect(ui->let_username, &QLineEdit::textChanged, [this](const QString& text) {
        int index = cb_username->findText(text);
        if (index != -1) {
            cb_username->setCurrentIndex(index);  // 如果有匹配的用户名，设置为当前选中项
        } else {
            cb_username->setCurrentIndex(-1);  // 没有匹配项则取消选中
        }
    });

    // 加载用户信息
    loadUsers();

    // 设置背景图片
    setMainWindowBackground();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 跳转到游戏界面
void MainWindow::on_btn_inlog_clicked()
{
    QString username = ui->let_username->text();
    QString password = ui->let_passwd1->text();

    qDebug() << "Input Username:" << username;
    qDebug() << "Input Password:" << password;

    if (username.isEmpty()) {
        QMessageBox::warning(this, "错误", "请输入用户名！");
        return;
    }

    if (validateUser(username, password)) {
        ChessGame *w = new ChessGame();
        w->show();
        this->hide();
    } else {
        QMessageBox::warning(this, "错误", "用户名或密码错误！");
    }
}

// 跳转到注册界面
void MainWindow::on_but_reg_clicked()
{
    regis *registrationWindow = new regis();
    registrationWindow->show();
    this->hide();
}

// 退出
void MainWindow::on_but_quit_clicked()
{
    this->close();
}

void MainWindow::setMainWindowBackground()
{
    // 创建一个调色板并设置背景图片
    QPalette palette;
    QPixmap backgroundImage(":/new/prefix1/images/60a4925e91b742165dd8073befa54376.jpg");
    QPixmap scaledBackground = backgroundImage.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    palette.setBrush(QPalette::Window, QBrush(scaledBackground));
    this->setAutoFillBackground(true);
    this->setPalette(palette);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    setMainWindowBackground();  // 更新背景图片以适应新的窗口大小
}

// 显示密码
void MainWindow::on_radioButton_clicked(bool checked)
{
    if (checked) {
        ui->let_passwd1->setEchoMode(QLineEdit::Normal);
    } else {
        ui->let_passwd1->setEchoMode(QLineEdit::Password);
    }
}

// 当用户选择不同的用户名时，自动填充对应的密码
void MainWindow::on_cb_username_currentIndexChanged(int index)
{
    QString selectedUsername = ui->cb_username->itemText(index);

    QFile file("users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开用户信息文件";
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        if (fields.size() == 2 && fields[0] == selectedUsername) {
            ui->let_passwd1->setText(fields[1]);
            break;
        }
    }
    file.close();
}

// 加载用户信息
void MainWindow::loadUsers()
{
    QFile file("users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开用户信息文件";
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        if (fields.size() == 2) {
            QString username = fields[0];
            cb_username->addItem(username);  // 添加用户名到下拉框
        }
    }
    file.close();

    // 如果有用户，显示 ComboBox 并隐藏 QLineEdit
    if (cb_username->count() > 0) {
        cb_username->show();
        ui->let_username->hide();
    } else {
        cb_username->hide();
        ui->let_username->show();
    }
}

// 验证用户
bool MainWindow::validateUser(const QString& username, const QString& password)
{
    QFile file("users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开用户信息文件";
        return false;
    }

    QTextStream in(&file);
    bool found = false;
    while (!in.atEnd()) {
        QString line = in.readLine();
        line = line.trimmed();
        QStringList parts = line.split(",");

        if (parts.size() == 2) {
            QString storedUsername = parts[0].trimmed();
            QString storedPassword = parts[1].trimmed();

            qDebug() << "Comparing:" << storedUsername << "with" << username;
            qDebug() << "Comparing:" << storedPassword << "with" << password;

            if (storedUsername == username && storedPassword == password) {
                found = true;
                break;
            }
        }
    }

    file.close();

    if (found) {
        qDebug() << "验证成功";
    } else {
        qDebug() << "验证失败";
    }

    return found;
}

// 保存用户
void MainWindow::saveUser(const QString& username, const QString& password)
{
    QFile file("users.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "无法保存用户信息");
        return;
    }

    QTextStream out(&file);
    out << username.trimmed() << "," << password.trimmed() << "\n";
    file.close();
}
