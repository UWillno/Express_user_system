#ifndef SQL_H
#define SQL_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>

class Sql : public QObject
{
    Q_OBJECT
public:
    explicit Sql(QObject *parent = nullptr);

    bool commitDB(QSqlQuery *query);

    bool signUp(const QStringList &list);

signals:


private:
    QSqlDatabase m_db;
};

#endif // SQL_H
