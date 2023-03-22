//
// Created by Sergey Mkrtumyan on 20.03.23.
//

#ifndef KURSAYINCALCULATOR_AUTHENTICATIONWIDGET_H
#define KURSAYINCALCULATOR_AUTHENTICATIONWIDGET_H


#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include "../../Core/Headers/UserService.h"

class AuthenticationWidget : public QWidget{
    Q_OBJECT

public:
    explicit AuthenticationWidget(QWidget *parent = nullptr);

private:
    void createLayout();
    void createLoginInput();
    void createPasswordInput();
    void createLoginButton();
    void createRegisterButton();
    void createFailMessage();

    void login();
    void registerUser();


    UserService *userService{};

    QGridLayout *layout{};
    QLineEdit *LoginInput{};
    QLineEdit *PasswordInput{};
    QLabel *FailMessage{};
    QPushButton *LoginButton{};
    QPushButton *RegisterButton{};
private slots:
    void Success();
    void Failed();
};


#endif //KURSAYINCALCULATOR_AUTHENTICATIONWIDGET_H
