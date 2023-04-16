//
// Created by Sergey Mkrtumyan on 20.03.23.
//

#ifndef KURSAYINCALCULATOR_USERSERVICE_H
#define KURSAYINCALCULATOR_USERSERVICE_H


#include <QObject>
#include "../../Data/DbManager.h"
#include "HashPassword.h"

class UserService : public QObject {
    Q_OBJECT
public:
    explicit UserService(QObject *parent = nullptr);

    void login(const QString &login, const QString &password);
    void registerUser(const QString &login, const QString &password);

signals:
    void Success();
    void Failed();

private:
    QString hashPassword(const QString &password, const QString &salt);
    bool authenticate(const QString &password,const QString &salt, const QString &hash);
    DbManager *dbManager{};
    HashPassword *crypt;
};


#endif //KURSAYINCALCULATOR_USERSERVICE_H
