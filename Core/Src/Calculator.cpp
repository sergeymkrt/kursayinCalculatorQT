//
// Created by Sergey Mkrtumyan on 17.03.23.
//

#include <stack>
#include <regex>
#include <sstream>
#include "../Headers/Calculator.h"
#include "../Headers/Number.h"

double Calculator::evaluateExpression(std::string *infixExpression) {
    auto postfixExpression = Calculator::InfixToPostfix(infixExpression);
    auto stack = new std::stack<Number>();
    auto tokens = splitString(postfixExpression);
    for (std::string token : tokens) {
        double value;
        if (tryParseDouble(token,value))
        {
            stack->push(Number(value));
        }
        else
        {
            auto operand2 = stack->top();
            stack->pop();
            auto operand1 = stack->top();
            stack->pop();

            if(token == "+"){
                stack->push(operand1 + operand2);
            }
            else if(token == "-"){
                stack->push(operand1 - operand2);
            }
            else if(token == "*"){
                stack->push(operand1 * operand2);
            }
            else if(token == "/"){
                stack->push(operand1 / operand2);
            }
            else if(token == "%"){
                stack->push(operand1 % operand2);
            }
            else if(token == "^"){
                stack->push(operand1 ^ operand2);
            }

        }
    }
    return stack->top().Value;
}

std::string Calculator::InfixToPostfix(std::string *infixExpression) {
    auto stack = new std::stack<char>();
    std::string output;
    char _out;
    bool isDecimal = false;

    std::regex characters("[a-zA-Z]");

    //loop over infixExpression
    for (char c : *infixExpression) {
        auto isAlphabet = std::regex_match(std::string(1, c), characters, std::regex_constants::match_default);

        if(isdigit(c) || isAlphabet || c == '.'){
            output += c;
            if(c == '.'){
                isDecimal = true;
            }
        }
        else if(c == ' '){
            if(isDecimal){
                isDecimal = false;
            }
            else{
                output += ' ';
            }
        }
        else{
            switch(c){
                case '+':
                case '-':
                case '*':
                case '/':
                case '%':
                case '^':
                    while(!stack->empty() && getPrecedence(c) <= getPrecedence(stack->top())){
                        _out = stack->top();
                        stack->pop();
                        output += " ";
                        output += _out;
                    }
                    stack->push(c);
                    output += " ";
                    break;
                case '(':
                    stack->push(c);
                    break;
                case ')':
                    while (!stack->empty() && (_out = stack->top()) != '(')
                    {
                        stack->pop();
                        output += " ";
                        output += _out;
                        output += " ";
                    }
                    if (!stack->empty() && (_out = stack->top()) == '(')
                        stack->pop();
                    break;
                default:
                    continue;
            }
        }
    }

    while(!stack->empty()){
        _out = stack->top();
        stack->pop();
        output += " ";
        output += _out;
        output += " ";
    }
    return output;
}

int Calculator::getPrecedence(char c) {
    switch (c)
    {
        case '*':
        case '/':
        case '%':
            return 3;
        case '+':
        case '-':
            return 2;
        case '^':
            return 1;
        default:
            return -1;
    }
}

std::vector<std::string> Calculator::splitString(const std::string &str) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, ' ')) {
        if (!token.empty()) {
            result.push_back(token);
        }
    }
    return result;
}

bool Calculator::tryParseDouble(const std::string &str, double &value) {
    std::istringstream iss(str);
    iss >> value;
    return !iss.fail() && iss.eof();
}
