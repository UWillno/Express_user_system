#include "settings.h"

Settings::Settings(QObject *parent)
    : QObject{parent}
{

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

void Settings::setSettings(QSettings *newSettings)
{
    if (m_settings == newSettings)
        return;
    m_settings = newSettings;
    emit settingsChanged();
}
