#ifndef ADMINMANAGER_H
#define ADMINMANAGER_H

#include <QWidget>
#include <creatdb.h>
#include <QVariantMap>
#include "admin_add_dlg.h"

namespace Ui {
class AdminManager;
}

class AdminManager : public QWidget
{
    Q_OBJECT

public:
    explicit AdminManager(QWidget *parent = nullptr);
    ~AdminManager();

    void appendRowData(QStringList RowData); //显示列表上加一行新的数据

    void clearTableData(); //清除表格

    QString getCurrentID(); //得到当前选中表格项目中ID

    QStringList getCurrentRowData(); //得到当前行的数据,填充编辑框用
    void setCurrentRow(int x,int y); //保证删除选择过后 当前的Currentrow 指向别处

    void Refresh(QList<QStringList> allData); //刷新列表

private:
    void ExecAddSql(QVariantMap userInfo); //增加数据
    void ExecEdtSql(QVariantMap userInfo); //编辑数据
    void ExecDelSql(QString ID); //删除数据

private slots:
    void find();

    void on_Button_refresh_clicked();

    void on_Button_add_clicked();

    void on_Button_edit_clicked();

    void on_Button_del_clicked();

private:
    Ui::AdminManager *ui;

    CreatDB * My_DB; //声明数据库的对象指针
    admin_Add_Dlg * p_admin_Add_Dlg;
};

#endif // ADMINMANAGER_H
