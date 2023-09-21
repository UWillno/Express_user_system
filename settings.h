#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>


class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = nullptr);

    QString password() const;
    void setPassword(const QString &newPassword);

    QString username() const;
    void setUsername(const QString &newUsername);

    QString user() const;
    void setUser(const QString &newUser);

    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged FINAL)
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged FINAL)
    Q_PROPERTY(QString user READ user WRITE setUser NOTIFY userChanged FINAL)
    Q_PROPERTY(QString isVip READ isVip WRITE setIsVip NOTIFY isVipChanged FINAL)

    QString isVip() const;
    void setIsVip(const QString &newIsVip);

public slots:
    void init();



signals:

    void passwordChanged();

    void usernameChanged();

    void userChanged();


    void isVipChanged();

private:
    QSettings *m_settings;
    QString m_user;
    QString m_username;
    QString m_password;
    QString m_isVip;




};

#endif // SETTINGS_H
