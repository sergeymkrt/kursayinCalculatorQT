//
// Created by Sergey Mkrtumyan on 20.03.23.
//

#ifndef KURSAYINCALCULATOR_USERSERVICE_H
#define KURSAYINCALCULATOR_USERSERVICE_H


#include <QObject>
#include "../../Data/DbManager.h"

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
    QString hashPassword(const QString &password);
    bool authenticate(const QString &password, const QString &hash);
    DbManager *dbManager{};
};


#endif //KURSAYINCALCULATOR_USERSERVICE_H
