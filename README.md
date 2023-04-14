# kursayinCalculatorQT
Almost the same calculator that i wrote in .NET MAUI , but in QT C++ :)

To run current project, you need to have installed QT 6.2.1 and C++ compiler.

I used CLion IDE to write this project, but you can use any IDE you want, but in CLion there is QT support, so yeah.

Also you can use Qt Creator.

Database is SqLite , using QtSql module.

For hashing passwords i used QCryptographicHash and Sha256, but i will change it to my own implementation of a hashing algorithm from scratch.

I will add more features in future, but for now it's just a calculator.

The main idea of this proejct, is to have authentication system, and to have a database with users, and their passwords, and to have a calculator that will be able to save your calculations, and to have a history of them.

Using Infix to Postfix algorithm to transform infix expression to postfix expression, and then to calculate it.

Overloaded operators and used assembly implementation to handle them.