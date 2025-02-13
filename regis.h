#ifndef REGIS_H
#define REGIS_H

#include <QWidget>
#include "ui_regis.h"
#include "mainwindow.h"
#include "chessgame.h"

class regis : public QWidget
{
    Q_OBJECT

public:
    explicit regis(QWidget *parent = nullptr);
    ~regis();

private slots:
    void on_btn_inlog_clicked();
    void on_btn_quit_clicked();
    void on_radioButton_clicked(bool checked);
    void on_radioButton_2_clicked(bool checked);

private:
    Ui::regis *ui;
    bool validateUsername(const QString& username);
    bool validatePassword(const QString& password);
    void saveUser(const QString& username, const QString& password);
};

#endif // REGIS_H
