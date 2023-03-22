//
// Created by Sergey Mkrtumyan on 20.03.23.
//

#include "../Headers/UserService.h"
#include "../../Data/DbManager.h"
#include <QCryptographicHash>
#include <QRandomGenerator>

UserService::UserService(QObject *parent) : QObject(parent) {
    dbManager = new DbManager();
}

void UserService::login(const QString &login, const QString &password) {
    if (!dbManager->isUserExist(login)) {
        emit Failed();
        return;
    }
    User user = dbManager->getUser(login);
    if (authenticate(password, user.password())) {
        emit Success();
    } else {
        emit Failed();
    }
}

void UserService::registerUser(const QString &login, const QString &password) {
    if (dbManager->isUserExist(login)) {
        emit Failed();
        return;
    }
    User user(login, password);
    auto hashedPassword = hashPassword(password);
    user.setPassword(hashedPassword);

    dbManager->addUser(user);
    emit Success();
}

QString UserService::hashPassword(const QString &password) {
    // Generate a random 8-byte salt
    QByteArray salt(8, Qt::Uninitialized);
    QRandomGenerator::securelySeeded().generate(reinterpret_cast<quint8*>(salt.data()), reinterpret_cast<quint8*>(salt.data() + salt.size()));

    // Hash the password with the salt using the SHA-256 algorithm
    QByteArray data = salt + password.toUtf8();
    QByteArray hash = QCryptographicHash::hash(data, QCryptographicHash::Sha256);

    // Return the salt and hashed password as a string
    return {salt.toHex() + hash.toHex()};
}

bool UserService::authenticate(const QString &password, const QString &hash) {
    // Extract the salt and hashed password from the stored value
    QByteArray storedData = QByteArray::fromHex(hash.toUtf8());
    QByteArray storedSalt = storedData.left(8);
    QByteArray storedHashedPassword = storedData.mid(8);

    // Hash the password entered by the user with the salt from the stored value
    QByteArray data = storedSalt + password.toUtf8();
    QByteArray hashedPassword = QCryptographicHash::hash(data, QCryptographicHash::Sha256);

    // Compare the hashed password with the stored value
    return hashedPassword == storedHashedPassword;
}
