//
// Created by Sergey Mkrtumyan on 20.03.23.
//

#ifndef KURSAYINCALCULATOR_USER_H
#define KURSAYINCALCULATOR_USER_H


#include <QString>

class User {
public:
    User(QString username, QString password)
        : m_username(std::move(username)), m_password(std::move(password))
    {
    }

    [[nodiscard]] QString username() const { return m_username; }
    [[nodiscard]] QString password() const { return m_password; }

    void setUsername(const QString &username) { m_username = username; }
    void setPassword(const QString &password) { m_password = password; }

private:
    QString m_username;
    QString m_password;
};


#endif //KURSAYINCALCULATOR_USER_H
