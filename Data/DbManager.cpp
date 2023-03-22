//
// Created by Sergey Mkrtumyan on 20.03.23.
//

#include "DbManager.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlError>
#include <QApplication>
#include <QDir>
#include <QSqlRecord>

DbManager::DbManager() {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    auto databaseName ="/Users/sergeymkrtumyan/CLionProjects/KursayinCalculator/Data/users.db";

    if(QFile::exists(databaseName)){
        qDebug() << "Database exist" ;
    }
    else{
        qDebug() << "Database not exist";
        QFile file(databaseName);
        if(file.open(QIODevice::ReadWrite)){
            file.close();
        }
    }
    m_db.setDatabaseName(databaseName);

    if (!m_db.open()) {
        qDebug() << "Error: connection with database fail";
    } else {
        qDebug() << "Database: connection ok";
    }

    if (!createTables()) {
        qDebug() << "Database: error creating tables";
    } else {
        qDebug() << "Database: tables created!";
    }
}

DbManager::~DbManager() {
    if (m_db.isOpen()) {
        m_db.close();
    }
}

bool DbManager::isOpen() const {
    return m_db.isOpen();
}

bool DbManager::createTables() {
    bool success = false;

    QSqlQuery query;

    query.prepare("CREATE TABLE IF NOT EXISTS Users ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "username TEXT UNIQUE, "
                  "password TEXT)");

    if (query.exec()) {
        success = true;
    } else {
        qDebug() << "Couldn't create the table 'users': one might already exist.";
    }

    return success;
}

bool DbManager::addUser(const User &user) {
    bool success = false;

    if (!isUserExist(user.username())) {
        QSqlQuery queryAdd;
        queryAdd.prepare(QString("INSERT INTO Users (username,password) "
                         "VALUES ('%1', '%2')").arg(user.username(),user.password()));

        qDebug() << "add user: " << user.username() << " " << user.password();
        if (queryAdd.exec()) {
            success = true;
        } else {
            qDebug() << "add user failed: " << queryAdd.lastError();
        }
    } else {
        qDebug() << "add user failed: user already exist";
    }

    return success;
}

bool DbManager::isUserExist(const QString &username) {
    bool exist = false;

    QSqlQuery checkQuery;

    checkQuery.prepare("SELECT * FROM Users WHERE Users.username = :username");
    checkQuery.bindValue(":username",username);
    checkQuery.exec();

    QSqlRecord rec = checkQuery.record();
    int cols = rec.count();

    QString temp;

    while(checkQuery.next()){
        temp = "";
        for (int i = 0; i < cols; i++) {
            temp += checkQuery.value(i).toString() + " ";
        }
        qDebug() << temp;
    }

    while (checkQuery.next()){
        qDebug() << checkQuery.value("id").toString(); // output all names
    }

    if (checkQuery.exec()) {
        if (checkQuery.next()) {
            exist = true;
        }
    }
    else {
        qDebug() << "user exist failed: " << checkQuery.lastError();
    }

    return exist;
}

bool DbManager::removeUser(const QString &username) {

    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM Users WHERE username = (:username)");
    deleteQuery.bindValue(":username", username);

    if(deleteQuery.exec()){
        return true;
    } else {
        qDebug() << "remove user failed: " << deleteQuery.lastError();
        return false;
    }
}

User DbManager::getUser(const QString &username) {
    QSqlQuery getUserQuery;
    getUserQuery.prepare("SELECT * FROM Users WHERE username = (:username)");
    getUserQuery.bindValue(":username", username);

    if(getUserQuery.exec()){
        if(getUserQuery.next()){
            return {getUserQuery.value(1).toString(), getUserQuery.value(2).toString()};
        }
    } else {
        qDebug() << "Get user failed: " << getUserQuery.lastError();
    }
}



