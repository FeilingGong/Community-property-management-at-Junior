#include "usermanager.h"
#include "ui_usermanager.h"

#include "admin_add_dlg.h"
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
UserManager::UserManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserManager)
{
    ui->setupUi(this);

    My_DB = new CreatDB;
    My_DB->initDB();

    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"户主"<<"编号"<<"联系电话"<<"联系地址"<<"预付金额"<<"待付金额");

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //设置表格列项的填充模式

}

//重载构造函数
UserManager::UserManager(QWidget *parent, QString name) : QWidget(parent),ui(new Ui::UserManager)
{
    ui->setupUi(this);
    UserManager::Name = name;

    My_DB = new CreatDB;
    My_DB->initDB();

    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"户主"<<"编号"<<"联系电话"<<"联系地址"<<"预付金额"<<"待付金额");

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //设置表格列项的填充模式
    qDebug()<<"执行了第二个构造方法";
}


UserManager::~UserManager()
{
    delete ui;
}


QStringList UserManager::getCurrentRowData()
{
    QString NAme = UserManager::Name;

    qDebug()<<NAme;

    QSqlQuery query;

    QString sql;
    sql = QString("SELECT * FROM UserManager WHERE name =='%1' ").arg(NAme);

    bool ok = query.exec(sql);

        if(!ok)
        {
            qDebug()<<"读取数据失败";
        }

        QString Name ;
        QString ID ;
        QString phone ;
        QString address ;
        QString prepay ;
        QString remainder ;
        QString password ;
        while (query.next())
        {
            Name = query.value(1).toString();
            ID = query.value(2).toString();
            phone = query.value(3).toString();
            address = query.value(4).toString();
            prepay = query.value(5).toString();
            remainder = query.value(6).toString();
            password = query.value(7).toString();

        }
    qDebug()<<Name<<ID<<phone<<address<<prepay<<remainder<<password;


    QStringList rowData;

    rowData.append(Name);
    rowData.append(ID);
    rowData.append(phone);
    rowData.append(address);
    rowData.append(prepay);
    rowData.append(remainder);
    rowData.append(password );

    return rowData;
}

void UserManager::initUserManager()
{
    QStringList rowData = this->getCurrentRowData();

    int row = ui->tableWidget->rowCount();

    ui->tableWidget->insertRow(row);

    //qDebug()<<"rowData size"<<rowData.at(6);

    for(int i  = 0 ; i < rowData.size()-1 ; i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(rowData.at(i));
        ui->tableWidget->setItem(row , i , item);
    }
}




void UserManager::on_pushButton_clicked()
{

    QString name = this->Name;

    qDebug()<<name;


    p_admin_Add_Dlg = new admin_Add_Dlg; //采用指针方式创建才能用show来显示
    p_admin_Add_Dlg->setAttribute(Qt::WA_DeleteOnClose); //记得释放内存

    qDebug()<<"点击了修改";

    QStringList rowData = this->getCurrentRowData();

    qDebug()<<"大小"<<rowData.size();
    p_admin_Add_Dlg->setEditData(rowData);
    p_admin_Add_Dlg->show();



    void(admin_Add_Dlg:: * signal_AddUser)(QVariantMap) = &admin_Add_Dlg::signal_AddUser_Accept; //连接带参数的信号和槽时，需要创建函数指针

    void(UserManager:: * ExecEdt)(QVariantMap) = &UserManager::ExecEdtSql;

    connect(p_admin_Add_Dlg,signal_AddUser,this,ExecEdt); //连接确定按钮 和 数据库修改函数
}

void UserManager::ExecEdtSql(QVariantMap userInfo)
{
    qDebug()<<"到达最终函数";

    QString create_date = userInfo.value("datetime").toString(); //还原各个信息字符串
    QString name = userInfo.value("name").toString();
    QString id = userInfo.value("ID").toString();
    QString phone = userInfo.value("phone").toString();
    QString address = userInfo.value("address").toString();
    QString prepay = userInfo.value("prepay").toString();
    QString remainder = userInfo.value("remainder").toString();
    QString password = userInfo.value("password").toString();


    qDebug()<<name<<id<<phone<<address<<prepay<<remainder<<create_date;

    QString sql;
    sql =  QString("UPDATE UserManager " "set create_date = '%1' ,name = '%2' ,id = '%3' ,"
                                        "phone = '%4',address = '%5',prepay = '%6', remainder = '%7',password = '%8' "
                                       " where id = '%9' ")
             .arg(create_date).arg(name).arg(id).arg(phone).arg(address).arg(prepay).arg(remainder).arg(password).arg(id);



    QSqlQuery query;
    bool ok = query.exec(sql);

    if(ok)
    {
        QMessageBox::information(nullptr,"提示","数据修改成功");
    }
    else {
        QMessageBox::information(nullptr,"提示","数据修改失败");
    }

    qDebug()<<"正在刷新数据";

    clearTableData();

    initUserManager();

}

void UserManager::clearTableData()
{
    //清除表格
    int rowCount = ui->tableWidget->rowCount();
    for(int r = rowCount-1 ; r >=0 ; r--)
    {
        ui->tableWidget->removeRow(r);
    }
}
