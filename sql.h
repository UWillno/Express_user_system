#ifndef SQL_H
#define SQL_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

class Sql : public QObject
{
    Q_OBJECT
public:
    explicit Sql(QObject *parent = nullptr);

    bool commitDB(QSqlQuery *query);

    bool signUp(const QStringList &list);

    bool login(const QString& user,const QString &pwd);

    void selectWD();

    bool addDelivery(const QStringList &list);

    void selectDelivery(const qint64 &id);

    bool beVip();

    void selectNews();

    QSqlTableModel *model;
    QSqlQueryModel *model1;
signals:
    void selectDeliveryS(QVariantList list);

private:
    QSqlDatabase m_db;

};

#endif // SQL_H
