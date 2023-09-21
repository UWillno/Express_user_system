#include "settings.h"
#include "singleton.h"
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
    model = new QSqlTableModel(this,m_db);
    model1 = new QSqlQueryModel(this);
    //    model->setTable("area");
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

bool Sql::login(const QString &user, const QString &pwd)
{
    //     SELECT EXISTS(SELECT * FROM `user` WHERE `user`='123' and pass=MD5('123123'))
    QSqlQuery query = QSqlQuery(m_db);
    query.prepare("SELECT * FROM `user` WHERE `user`=:user and pass=MD5(:pwd);");
    query.bindValue(":user",user);
    query.bindValue(":pwd",pwd);
    query.exec();
    //    qint32 i = 0 ;
    while (query.next()) {
        //        return query.value(0).toInt() != 0;
        //        qInfo() << i;
        bool ok;

        query.value(0).toInt(&ok);
        if(ok){
            Singleton<Settings>::GetInstance().setUser(user);
            Singleton<Settings>::GetInstance().setUsername(query.value(4).toString());
            Singleton<Settings>::GetInstance().setPassword(pwd);
            //            qInfo()<< query.value(3);
            query.value(3).toInt() !=0 ?
                Singleton<Settings>::GetInstance().setIsVip("会员") :
            Singleton<Settings>::GetInstance().setIsVip("非会员");
        }
        return ok;

    }
    return false;
    //    return i!=0;
}

void Sql::selectWD()
{
    model->clear();
    model->setTable("area");
    model->select();
    qInfo() << model->columnCount();

    model->removeColumn(0);

    qInfo() << model->columnCount();
    int searchColumnIndex = model->columnCount();
    model->setHeaderData(searchColumnIndex, Qt::Horizontal, tr("Search Column"));
    for (int row = 0; row < model->rowCount(); ++row) {
        QModelIndex index = model->index(row, model->columnCount());
        QVariant searchData =model->data(model->index(row, 0)).toString()+
                              model->data(model->index(row, 1)).toString()+
                              model->data(model->index(row, 2)).toString()+
                              model->data(model->index(row, 3)).toString()+
                              model->data(model->index(row, 4)).toString()+
                              model->data(model->index(row, 5)).toString();
        model->setData(index, searchData);
    }
}

bool Sql::addDelivery(const QStringList &list)
{
    QSqlQuery query = QSqlQuery(m_db);
    query.prepare("INSERT into delivery VALUES(NULL, :send_name, :send_tel, :send_area,:send_address , :hav_name, :hav_tel, :hav_area, :hav_address, :goods_type, :weight, NOW(), NULL, 0, NULL, NULL)");
    query.bindValue(":send_name",list[0]);
    query.bindValue(":send_tel",list[1]);
    query.bindValue(":send_area",list[2]);
    query.bindValue(":send_address",list[3]);
    query.bindValue(":hav_name",list[4]);
    query.bindValue(":hav_tel",list[5]);
    query.bindValue(":hav_area",list[6]);
    query.bindValue(":hav_address",list[7]);
    query.bindValue(":goods_type",list[8]);
    query.bindValue(":weight",list[9].toDouble());
    query.exec();
    return commitDB(&query);

}

void Sql::selectDelivery(const qint64 &id)
{
    QSqlQuery query = QSqlQuery(m_db);
    query.prepare("SELECT arrival_state,commit_time,sign_time,arrival_time,receipt_time FROM `delivery` WHERE id =:id;");
    query.bindValue(":id",id);
    query.exec();
    QVariantList list;
    while (query.next()) {
        list.append(query.value(0));
        list.append(query.value(1));
        list.append(query.value(2));
        list.append(query.value(3));
        list.append(query.value(4));
    }
    qInfo() << list;
    if(!list.isEmpty())
        emit selectDeliveryS(list);
}

bool Sql::beVip()
{
    QSqlQuery query = QSqlQuery(m_db);
    query.prepare("UPDATE `user` SET is_vip =1  WHERE user = :user AND pass = MD5(:pwd) AND username = :username;");
    query.bindValue(":user",Singleton<Settings>::GetInstance().user());
    query.bindValue(":pwd",Singleton<Settings>::GetInstance().password());
    query.bindValue(":username",Singleton<Settings>::GetInstance().username());
    query.exec();
    if(commitDB(&query)){
        Singleton<Settings>::GetInstance().setIsVip("会员");
        return true;
    }
    return false;
}

void Sql::selectNews()
{
    model1->clear();
    model1->setQuery("SELECT * FROM `news`",m_db);
    qInfo() << model1->rowCount();
    model1->removeColumn(0);

}
