#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QWidget>
#include <QVariantMap>
#include <QStringList>

#include "creatdb.h"
#include "admin_add_dlg.h"

namespace Ui {
class UserManager;
}

class UserManager : public QWidget
{
    Q_OBJECT

public:
    explicit UserManager(QWidget *parent = nullptr);
    UserManager(QWidget *parent = nullptr,QString name = nullptr);
    ~UserManager();

    void initUserManager();

    QStringList getCurrentRowData();

private slots:
    void on_pushButton_clicked();

    void ExecEdtSql(QVariantMap userInfo);
    void clearTableData();

private:
    Ui::UserManager *ui;

    admin_Add_Dlg *p_admin_Add_Dlg;

    CreatDB * My_DB;
    QString Name;
};

#endif // USERMANAGER_H
