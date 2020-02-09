#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include "adminmanager.h"
#include "usermanager.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_loginButton_clicked();

    void on_exitButton_clicked();

private:
    Ui::LoginWindow *ui;

    UserManager * pUserManager ; //声明对象指针，未初始化？
    AdminManager * pAdminManager;

    CreatDB * My_DB; //登录时 打开数据库，用于比对密码
};

#endif // LOGINWINDOW_H
