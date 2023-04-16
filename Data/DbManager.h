//
// Created by Sergey Mkrtumyan on 20.03.23.
//

#ifndef KURSAYINCALCULATOR_DBMANAGER_H
#define KURSAYINCALCULATOR_DBMANAGER_H


#include <QString>
#include <QSqlDatabase>
#include "../Entities/User.h"

class DbManager {
public:
    explicit DbManager();
    ~DbManager();

    [[nodiscard]] bool isOpen() const;
    static bool createTables();
    bool addUser(const User &user);
    static bool isUserExist(const QString &login);
    bool removeUser(const QString &login);
    User getUser(const QString &login);
private:
    QSqlDatabase m_db;
};


#endif //KURSAYINCALCULATOR_DBMANAGER_H
