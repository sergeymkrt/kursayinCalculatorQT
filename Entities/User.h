//
// Created by Sergey Mkrtumyan on 20.03.23.
//

#ifndef KURSAYINCALCULATOR_USER_H
#define KURSAYINCALCULATOR_USER_H


#include <QString>
#include <utility>

class User {
public:
    User(){
        m_username = "";
        m_password = "";
        _salt = "";
    }
    User(QString username, QString password)
        : m_username(std::move(username)), m_password(std::move(password))
    {
    }
    User(QString username, QString password, QString salt){
        m_username = std::move(username);
        m_password = std::move(password);
        _salt = std::move(salt);
    }

    [[nodiscard]] QString username() const { return m_username; }
    [[nodiscard]] QString password() const { return m_password; }
    [[nodiscard]] QString salt() const { return _salt; }

    void setUsername(const QString &username) { m_username = username; }
    void setPassword(const QString &password) { m_password = password; }
    void setSalt(const QString &salt) { _salt = salt; }

private:
    QString m_username;
    QString m_password;
    QString _salt;
};

#endif //KURSAYINCALCULATOR_USER_H
