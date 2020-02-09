#ifndef ADMIN_ADD_DLG_H
#define ADMIN_ADD_DLG_H

#include <QDialog>
#include <QVariantMap>

namespace Ui {
class admin_Add_Dlg;
}

class admin_Add_Dlg : public QDialog
{
    Q_OBJECT

public:
    explicit admin_Add_Dlg(QWidget *parent = nullptr);
    ~admin_Add_Dlg();

    void setEditData(QStringList RowData); //设置编辑框文字

signals:
    void signal_AddUser_Accept(QVariantMap userInfo);


private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();



private:
    Ui::admin_Add_Dlg *ui;
};

#endif // ADMIN_ADD_DLG_H
