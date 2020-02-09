#include "creatdb.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

CreatDB::CreatDB()
{

}
void CreatDB::initDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("SqliteName.db");

    bool ok = db.open();
    if(ok)
    {
        qDebug()<<"数据库打开成功";
        QSqlQuery query;
        query.exec("create table UserManager (create_date datetime, "
                   "name varchar(20) ,id varchar(20)  primary key, "
                   " phone varchar(12) ,address varchar(50) ,"
                   " prepay varchar(20) ,remainder varchar(20) ,password varchar(20)  )");

    }
    else {
        QMessageBox::about(nullptr,"提示","打开数据库失败");
    }
}

QList<QStringList> CreatDB::selectDataFromBase()
{
    QList<QStringList> allData;

    QSqlQuery query("SELECT * FROM UserManager"); //userManager是表的名字

    while(query.next())
    {
        QStringList rowData;
        rowData<<query.value(1).toString();
        rowData<<query.value(2).toString();
        rowData<<query.value(3).toString();
        rowData<<query.value(4).toString();

        rowData<<query.value(5).toString();
        rowData<<query.value(6).toString();
        rowData<<query.value(7).toString();

        allData.append(rowData);

    }
    return allData;
}
