#include "sql.h"

Sql::Sql(QObject *parent)
    : QObject{parent}
{
    m_db=QSqlDatabase::addDatabase("QMYSQL","uwillno");
    m_db.setHostName("");
    m_db.setPort(3306);
    m_db.setDatabaseName("express");
    m_db.setUserName("root");
    m_db.setPassword("123456");
    m_db.open();
}

bool Sql::commitDB(QSqlQuery *query)
{
    if (query->isActive())
    {
        m_db.commit();
        return true;
    }
    else
    {
        m_db.rollback();
        return false;
    }
}

bool Sql::signUp(const QStringList &list)
{
    QSqlQuery query = QSqlQuery(m_db);
    if(list.length()==3){
        query.prepare("INSERT INTO `user` VALUES(0,:user,MD5(:pwd),0,:username);");
        query.bindValue(":user",list[0]);
        query.bindValue(":pwd",list[1]);
        query.bindValue(":username",list[2]);
        query.exec();
    }
    return commitDB(&query);
}
