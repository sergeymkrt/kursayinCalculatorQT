//
// Created by Sergey Mkrtumyan on 17.03.23.
//

#ifndef KURSAYINCALCULATOR_CALCULATOR_H
#define KURSAYINCALCULATOR_CALCULATOR_H

#include <string>
class Calculator {
public:
    static double evaluateExpression(std::string *infixExpression);
private:
    static std::string InfixToPostfix(std::string *infixExpression);
    static int getPrecedence(char c);
    static std::vector<std::string> splitString(const std::string& str);
    static bool tryParseDouble(const std::string& str, double& value);
};


#endif //KURSAYINCALCULATOR_CALCULATOR_H
