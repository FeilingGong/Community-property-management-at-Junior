#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QVariantMap>
#include <QMessageBox>
#include <QDebug>

#include <QSqlQuery>
#include<QSqlQueryModel>

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    My_DB = new CreatDB();
    My_DB->initDB();

    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_loginButton_clicked()
{
//    QVariantMap NameandPassword;

    QString name = ui->nameEdit->text();
    QString Password = ui->passwordEdit->text();

//    NameandPassword.insert("name",name);
//    NameandPassword.insert("password",Password);

    qDebug()<<"点击按钮";


    if(ui->adminButton->isChecked())
    {
        if(name=="admin" && Password=="admin")
        {
            QMessageBox::about(this,"提示","管理员登录成功");
            this->hide();
            pAdminManager = new AdminManager;

            pAdminManager->show();

            QList<QStringList> allData = My_DB->selectDataFromBase(); //获取数据库里所有的数据
            pAdminManager->Refresh(allData); //刷新表格使显示信息


        }
        else if (name.isEmpty() || Password.isEmpty()) {
            QMessageBox::information(this,"提示","请输入有效身份");
        }
        else {
            QMessageBox::information(this,"提示","账户名或密码错误");
        }

    }
    else if (ui->userButton->isChecked()) {


        QString inputName=ui->nameEdit->text();
        QString inputPassword=ui->passwordEdit->text();


        qDebug()<<inputName<<inputPassword;

        QSqlQuery query;

        QString sql;
        sql = QString("SELECT * FROM UserManager WHERE name =='%1' ").arg(inputName);

        bool ok = query.exec(sql);

//        if(!ok)
//        {
//            qDebug()<<"选取数据失败";
//        }


        QString name ;
        QString password ;
        while (query.next())
        {
            name = query.value(1).toString();
            password = query.value(7).toString();

        }


        qDebug()<<name<<password;

        qDebug()<<"111111111";


        if(!name.isEmpty() && inputPassword == password)
        {
            QMessageBox::about(nullptr,"提示","用户登录成功");

            this->hide();
            pUserManager = new UserManager(nullptr,name);

            pUserManager->initUserManager(); //调用有参构造函数

            pUserManager->show();


        }
        else if (name.isEmpty() || password.isEmpty()) {
            QMessageBox::about(nullptr,"提示","请输入有效账户密码");
        }
        else
        {
            QMessageBox::about(nullptr,"提示","用户名或密码错误");
        }




    }
    else {
        QMessageBox::information(this,"提示","请选择登录身份");
    }
}

void LoginWindow::on_exitButton_clicked()
{
    close();
}
