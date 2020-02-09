#include "loginwindow.h"
#include <QApplication>
#include <QFont>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFont font("Times",12,QFont::Thin);  //字体设置
    a.setFont(font);

    LoginWindow w;
    w.show();

    return a.exec();
}
