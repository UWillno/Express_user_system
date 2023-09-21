#include "settings.h"

Settings::Settings(QObject *parent)
    : QObject{parent}
{
    m_settings = new QSettings("config.ini",QSettings::IniFormat,this);
    QObject::connect(this,&Settings::passwordChanged,this,[&]{
        m_settings->setValue("password",password());
    });
    QObject::connect(this,&Settings::userChanged,this,[&]{
        m_settings->setValue("user",user());
    });
    QObject::connect(this,&Settings::usernameChanged,this,[&]{
        m_settings->setValue("username",username());
    });
    QObject::connect(this,&Settings::isVipChanged,this,[&]{
        m_settings->setValue("isVip",isVip());
    });
}

QString Settings::password() const
{
    return m_password;
}

void Settings::setPassword(const QString &newPassword)
{
    if (m_password == newPassword)
        return;
    m_password = newPassword;
    emit passwordChanged();
}

QString Settings::username() const
{
    return m_username;
}

void Settings::setUsername(const QString &newUsername)
{
    if (m_username == newUsername)
        return;
    m_username = newUsername;
    emit usernameChanged();
}

QString Settings::user() const
{
    return m_user;
}

void Settings::setUser(const QString &newUser)
{
    if (m_user == newUser)
        return;
    m_user = newUser;
    emit userChanged();
}


void Settings::init()
{
    setUser(m_settings->value("user").toString());
    setUsername(m_settings->value("username").toString());
    setPassword(m_settings->value("password").toString());
    setIsVip(m_settings->value("isVip").toString());
}

QString Settings::isVip() const
{
    return m_isVip;
}

void Settings::setIsVip(const QString &newIsVip)
{
    if (m_isVip == newIsVip)
        return;
    m_isVip = newIsVip;
    emit isVipChanged();
}


