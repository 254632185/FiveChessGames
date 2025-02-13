#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chessgame.h"

#include <QWidget>
#include "ui_chessgame.h"
#include <QComboBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_btn_inlog_clicked();
    void on_but_reg_clicked();
    void on_but_quit_clicked();
    void on_radioButton_clicked(bool checked);
    void on_cb_username_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    QComboBox *cb_username;
    void loadUsers();
    bool validateUser(const QString& username, const QString& password);
    void saveUser(const QString& username, const QString& password);
    void setMainWindowBackground();
};

#endif // MAINWINDOW_H
