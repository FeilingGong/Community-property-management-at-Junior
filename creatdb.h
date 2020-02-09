#ifndef CREATDB_H
#define CREATDB_H

#include <QList>


class CreatDB
{
public:
    CreatDB();

    void initDB();
    QList<QStringList> selectDataFromBase();
};

#endif // CREATDB_H
