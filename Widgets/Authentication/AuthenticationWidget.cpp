//
// Created by Sergey Mkrtumyan on 20.03.23.
//

#include "AuthenticationWidget.h"
#include "../MainWindow/MainWindow.h"

AuthenticationWidget::AuthenticationWidget(QWidget *parent) {
    createLoginInput();
    createPasswordInput();
    createLoginButton();
    createRegisterButton();
    createFailMessage();
    createLayout();

    userService = new UserService(this);

    connect(userService, &UserService::Success, this, &AuthenticationWidget::Success);
    connect(userService, &UserService::Failed, this, &AuthenticationWidget::Failed);
}

void AuthenticationWidget::createLoginInput() {
    LoginInput = new QLineEdit(this);
    LoginInput->setPlaceholderText("Login");
}

void AuthenticationWidget::createPasswordInput() {
    PasswordInput = new QLineEdit(this);
    PasswordInput->setPlaceholderText("Password");
    PasswordInput->setEchoMode(QLineEdit::Password);
}

void AuthenticationWidget::createLoginButton() {
    LoginButton = new QPushButton("Login", this);
    connect(LoginButton, &QPushButton::clicked, this, &AuthenticationWidget::login);
}

void AuthenticationWidget::createRegisterButton() {
    RegisterButton = new QPushButton("Register", this);
    connect(RegisterButton, &QPushButton::clicked, this, &AuthenticationWidget::registerUser);
}

void AuthenticationWidget::registerUser() {
    userService->registerUser(LoginInput->text(), PasswordInput->text());
}

void AuthenticationWidget::login() {
    userService->login(LoginInput->text(), PasswordInput->text());
}

void AuthenticationWidget::Success() {
    FailMessage->setVisible(false);
    auto *w = new MainWindow();
    w->show();;
    this->close();
}

void AuthenticationWidget::Failed() {
    LoginInput->clear();
    PasswordInput->clear();
    FailMessage->setVisible(true);
}

void AuthenticationWidget::createFailMessage() {
    FailMessage = new QLabel("Login or password is incorrect", this);
    FailMessage->setStyleSheet("color: red");
    FailMessage->setVisible(false);
}

void AuthenticationWidget::createLayout() {
    layout = new QGridLayout(this);
    layout->addWidget(LoginInput, 0, 0, 1, 2);
    layout->addWidget(PasswordInput, 1, 0 , 1, 2);
    layout->addWidget(LoginButton, 2, 0, 1 , 1);
    layout->addWidget(RegisterButton, 2, 1, 1, 1);
    layout->addWidget(FailMessage, 3, 0, 1, 2);
}
