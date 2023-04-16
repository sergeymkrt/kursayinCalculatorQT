//
// Created by Sergey Mkrtumyan on 20.03.23.
//

#include "../Headers/UserService.h"

UserService::UserService(QObject *parent) : QObject(parent) {
    dbManager = new DbManager();
    crypt = new HashPassword();
}

void UserService::login(const QString &login, const QString &password) {
    if (!DbManager::isUserExist(login)) {
        emit Failed();
        return;
    }
    User user = dbManager->getUser(login);
    if(user.username() == "" || user.password() == "" || user.salt() == ""){
        emit Failed();
        return;
    }
    if (authenticate(password, user.salt(),user.password())){
        emit Success();
    } else {
        emit Failed();
    }
}

void UserService::registerUser(const QString &login, const QString &password) {
    if (DbManager::isUserExist(login)) {
        emit Failed();
        return;
    }
    User user(login, password);
    auto salt = HashPassword::generate_salt(8);
    user.setSalt(salt);
    auto hashedPassword = hashPassword(password,salt);
    user.setPassword(hashedPassword);

    dbManager->addUser(user);
    emit Success();
}

QString UserService::hashPassword(const QString &password, const QString &salt) {
    std::string saltString = salt.toStdString();
    auto hash = crypt->hash_password(password.toStdString() + saltString);
    return hash;
}

bool UserService::authenticate(const QString &password,const QString &salt, const QString &storedHashPass) {
    //hash the password
    auto hashedPass = crypt->hash_password(password.toStdString() + salt.toStdString());

    // Compare the hashed password with the stored value
    return hashedPass == storedHashPass;
}
