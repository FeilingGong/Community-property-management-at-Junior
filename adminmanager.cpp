#include "adminmanager.h"
#include "ui_adminmanager.h"
#include <QDebug>
#include <QVariantMap>
#include <QSqlQuery>
#include <QMessageBox>

#include "admin_Add_Dlg.h"

AdminManager::AdminManager(QWidget *parent) :QWidget(parent),ui(new Ui::AdminManager)
{

    My_DB = new CreatDB;
    My_DB->initDB();

    ui->setupUi(this);
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"户主"<<"编号"<<"联系电话"<<"联系地址"<<"预付金额"<<"待付金额");

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //设置表格列项的填充模式
    ui->textEdit->setText("恒大御龙天峰，近千亩生态大盘，以舒居理念，打造恒大城东新作。建面约90-110㎡实用三房，建面约110-130㎡舒居三房，建面约130-140㎡阔景四房，新风系统、智能门禁系统；更有恒大影城、恒大超五星会所、大型超市、主力店餐饮、书店、邻里互动 等；A1地块打造177000㎡法式叠水园林。");

    connect(ui->lineEdit_findname,SIGNAL(textChanged(QString)),this,SLOT(find()));//将字符变化的事件，与某函数连接

}

AdminManager::~AdminManager()
{
    delete ui;

}
void AdminManager::find()
{
    QString find,sql0;

    find=ui->lineEdit_findname->text();

    if(find.isEmpty())
    {

        QList<QStringList> allData = My_DB->selectDataFromBase(); //获取数据库里所有的数据
        this->Refresh(allData); //刷新表格使显示信息
    }



    QList<QStringList> result;

    sql0 = QString("SELECT * FROM UserManager WHERE name LIKE '%1' ").arg(find);
    QSqlQuery query; //userManager是表的名字
    bool ok = query.exec(sql0);
    if(ok)
    {
        qDebug()<<"查询成功";
    }
    else {
        qDebug()<<"查询失败";
    }

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

        result.append(rowData);

    }
    Refresh(result);

    qDebug()<<"搜索框变化";
}
void AdminManager::appendRowData(QStringList rowData)
{


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

void AdminManager::clearTableData()
{
    //清除表格
    int rowCount = ui->tableWidget->rowCount();
    for(int r = rowCount-1 ; r >=0 ; r--)
    {
        ui->tableWidget->removeRow(r);
    }
}

QString AdminManager::getCurrentID()
{
    QString ID;
    int row = ui->tableWidget->currentRow();
    if(row != -1)
    {
        ID = ui->tableWidget->item(row,1)->text();
    }

//    QString test;
//    test = ui->tableWidget->item(0,2)->text();
//    qDebug()<<"This is debug 第一行编号为:"<<test;
    return ID;
}

QStringList AdminManager::getCurrentRowData()
{
    QStringList RowData;
    int row = ui->tableWidget->currentRow();
    if(row != -1)
    {
        RowData << ui->tableWidget->item(row , 0)->text();
        RowData << ui->tableWidget->item(row , 1)->text();
        RowData << ui->tableWidget->item(row , 2)->text();
        RowData << ui->tableWidget->item(row , 3)->text();
        RowData << ui->tableWidget->item(row , 4)->text();
        RowData << ui->tableWidget->item(row , 5)->text();
    }
    qDebug()<<"第几行"<<row;
    return RowData;
}

void AdminManager::setCurrentRow(int x=-1,int y=-1)
{
    ui->tableWidget->setCurrentCell(x,y);
}

void AdminManager::Refresh(QList<QStringList> allData)
{

    this->clearTableData(); //清除数据

    if(!allData.isEmpty())
    {

        QListIterator<QStringList> itr(allData); //迭代器

        while(itr.hasNext())
        {
            this->appendRowData(itr.next());  //一次添加一行数据
        }
    }
}
//--------------------------------------------------------------------------------------------
void AdminManager::ExecAddSql(QVariantMap userInfo)
{
    qDebug()<<"信号到达！！！";
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
    sql =  QString("insert into UserManager (create_date , name ,id ,phone ,address ,prepay , remainder ,password)"
                   " VALUES ('%1', '%2' , '%3' , '%4' , '%5' , '%6' , '%7' ,'%8' )")
             .arg(create_date).arg(name).arg(id).arg(phone).arg(address).arg(prepay).arg(remainder).arg(password);

    QSqlQuery query;
    bool ok = query.exec(sql);

    if(ok)
    {
        QMessageBox::information(nullptr,"提示","数据添加成功");
    }
    else {
        QMessageBox::information(nullptr,"提示","数据添加失败"
                                              "可能原因:键值重复");
    }

    qDebug()<<"正在刷新数据";

    QList<QStringList> allData = My_DB->selectDataFromBase(); //获取数据库里所有的数据
    this->Refresh(allData); //刷新表格使显示信息


}

void AdminManager::ExecEdtSql(QVariantMap userInfo)
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


    QList<QStringList> allData = My_DB->selectDataFromBase(); //获取数据库里所有的数据
    this->Refresh(allData); //刷新表格使显示信息
}

void AdminManager::ExecDelSql(QString ID)
{
    QString sql;
    sql = QString("DELETE FROM UserManager"
                  " where id = '%8' ").arg(ID);

    QSqlQuery query;
    bool ok = query.exec(sql);

    QList<QStringList> allData = My_DB->selectDataFromBase(); //获取数据库里所有的数据
    this->Refresh(allData); //刷新表格使显示信息

    if(ok)
    {
        QMessageBox::information(this ,"提示" , "数据删除成功!");
    }
    else
        {
        QMessageBox::information(this ,"提示" , "数据删除失败!");
    }
}


//--------------------------------------------------------------------------------------------
void AdminManager::on_Button_refresh_clicked()
{

    ui->lineEdit_findname->clear();
    QList<QStringList> allData = My_DB->selectDataFromBase(); //获取数据库里所有的数据
    this->Refresh(allData); //刷新表格使显示信息
}

void AdminManager::on_Button_add_clicked()
{

    p_admin_Add_Dlg = new admin_Add_Dlg; //采用指针方式创建才能用show来显示
    p_admin_Add_Dlg->setAttribute(Qt::WA_DeleteOnClose); //记得释放内存
    p_admin_Add_Dlg->show();

    void(admin_Add_Dlg:: * signal_AddUser)(QVariantMap) = &admin_Add_Dlg::signal_AddUser_Accept; //连接带参数的信号和槽时，需要创建函数指针

    void(AdminManager:: * ExecAdd)(QVariantMap) = &AdminManager::ExecAddSql;

    connect(p_admin_Add_Dlg,signal_AddUser,this,ExecAdd); //连接确定按钮 和 数据库添加函数
}

void AdminManager::on_Button_edit_clicked()
{
    QString ID = this->getCurrentID(); //得到用户选择的数据的ID


    if(ID.isEmpty())
    {
        QMessageBox::information(nullptr,"提示","请选择一条需要编辑的数据");
        return;
    }


    qDebug()<<ID;


    p_admin_Add_Dlg = new admin_Add_Dlg; //采用指针方式创建才能用show来显示
    p_admin_Add_Dlg->setAttribute(Qt::WA_DeleteOnClose); //记得释放内存

    //qDebug()<<"点击了修改";

    QStringList rowData = this->getCurrentRowData();

    qDebug()<<"大小"<<rowData.size();
    p_admin_Add_Dlg->setEditData(rowData);

    p_admin_Add_Dlg->show();



    this->setCurrentRow(-1,-1);  //设置坐标变回为-1


    void(admin_Add_Dlg:: * signal_AddUser)(QVariantMap) = &admin_Add_Dlg::signal_AddUser_Accept; //连接带参数的信号和槽时，需要创建函数指针

    void(AdminManager:: * ExecEdt)(QVariantMap) = &AdminManager::ExecEdtSql;

    connect(p_admin_Add_Dlg,signal_AddUser,this,ExecEdt); //连接确定按钮 和 数据库修改函数

}

void AdminManager::on_Button_del_clicked()
{
    QString ID = this->getCurrentID(); //得到用户选择的数据的ID
    this->setCurrentRow(-1,-1);  //设置坐标为-1

    if(ID.isEmpty())
    {
        QMessageBox::information(nullptr,"提示","请选择一条数据");
        return;
    }
    qDebug()<<ID;

    QMessageBox::StandardButton del= QMessageBox::question(this,"提示","确定删除该住户数据?");
    if(del == QMessageBox::Yes)
    {
        ExecDelSql(ID);
    }
}
