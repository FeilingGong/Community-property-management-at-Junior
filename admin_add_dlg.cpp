#include "admin_add_dlg.h"
#include "ui_admin_add_dlg.h"

#include <QDateTime>
#include <QDebug>
#include <QVariantMap>
#include <QMessageBox>

admin_Add_Dlg::admin_Add_Dlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin_Add_Dlg)
{
    ui->setupUi(this);
}

admin_Add_Dlg::~admin_Add_Dlg()
{
    delete ui;
}

void admin_Add_Dlg::on_buttonBox_accepted()
{
    //qDebug()<<"你点击了确定";
    QVariantMap userInfo;

    //取得输入框里的内容
    QString name = ui->nameEdit->text();
    QString ID = ui->IDEdit->text();
    QString phone = ui->phoneEdit->text();
    QString address = ui->addressEdit->toPlainText();
    QString prepay = ui->prepayEdit->text();
    QString remainder = ui->remainderEdit->text();
    QString password = ui->passwordEdit->text();

    QString datetime = QDateTime::currentDateTime().toString();

    qDebug()<<name<<ID<<phone<<address<<prepay<<remainder<<datetime;

    if(name.isEmpty() || ID.isEmpty() || phone.isEmpty() || address.isEmpty() || password.isEmpty())
    {
        QMessageBox::information(this,"提示","请输入有效信息");
        return;
    }
    userInfo.insert("name",name);
    userInfo.insert("ID",ID);
    userInfo.insert("phone",phone);
    userInfo.insert("address",address);
    userInfo.insert("prepay",prepay);
    userInfo.insert("remainder",remainder);
    userInfo.insert("datetime",datetime);
    userInfo.insert("password",password);

    emit signal_AddUser_Accept(userInfo); //点击确定时唤起信号，槽函数的连接在dialog的构造函数里
}

void admin_Add_Dlg::on_buttonBox_rejected()
{
    close();
}

void admin_Add_Dlg::setEditData(QStringList RowData)
{
    ui->nameEdit->setText(RowData.at(0));
    ui->IDEdit->setText(RowData.at(1));
    ui->phoneEdit->setText(RowData.at(2));
    ui->addressEdit->setText(RowData.at(3));
    ui->prepayEdit->setText(RowData.at(4));
    ui->remainderEdit->setText(RowData.at(5));
    //ui->passwordEdit->setText(RowData.at(6));
    qDebug()<<"11111111";
}
