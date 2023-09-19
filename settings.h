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

    void setSettings(QSettings *newSettings);
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged FINAL)
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged FINAL)
    Q_PROPERTY(QString user READ user WRITE setUser NOTIFY userChanged FINAL)
    Q_PROPERTY(QSettings *settings READ Settings WRITE setSettings NOTIFY settingsChanged FINAL)
signals:

    void passwordChanged();

    void usernameChanged();

    void userChanged();

    void settingsChanged();

private:
    QSettings *m_settings;
    QString m_user;
    QString m_username;
    QString m_password;

};

#endif // SETTINGS_H
