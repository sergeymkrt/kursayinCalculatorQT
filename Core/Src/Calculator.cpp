//
// Created by Sergey Mkrtumyan on 17.03.23.
//

#include <stack>
#include <regex>
#include <QDebug>
#include "../Headers/Calculator.h"
#include "../Headers/Number.h"

double Calculator::evaluateExpression(std::string *infixExpression) {
    //regex for shifting
    std::regex shiftRegex(R"(\d+\s*(<<|>>)\s*\d+)");

    //check if the expression is shifting or not
    if (std::regex_match(*infixExpression, shiftRegex)) {
        //split the expression
        std::vector<std::string> tokens = splitString(*infixExpression);

        //get the number ( string to double )
        double number = std::stod(tokens[0]);

        //get the bits ( string to int )
        int bits = std::stoi(tokens[2]);

        //check if the expression is left shifting or right shifting
        if (tokens[1] == "<<") {
            //left shifting
            return (int)number << bits;
        } else {
            //right shifting
            return (int)number >> bits;
        }
    }


    auto postfixExpression = Calculator::InfixToPostfix(infixExpression);
    auto stack = new std::stack<Number>();
    auto tokens = splitString(postfixExpression);
    for (const std::string& token : tokens) {
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
        case '^':
            return 3;
        case '+':
        case '-':
            return 2;
        default:
            return -1;
    }
}

std::vector<std::string> Calculator::splitString(const std::string &str) {
    std::vector<std::string> result;
    size_t pos = 0, last_pos = 0;
    while ((pos = str.find(' ', last_pos)) != std::string::npos) {
        std::string word = str.substr(last_pos, pos - last_pos);
        result.push_back(word);
        last_pos = pos + 1;
    }
    std::string word = str.substr(last_pos);
    result.push_back(word);

    //remove empty strings
    result.erase(std::remove(result.begin(), result.end(), ""), result.end());

    return result;
}

//take as input str and value as references
//try to parse str to double and if it is successful then return true and assign the value to value
bool Calculator::tryParseDouble(const std::string &str, double &value) {
    try{
        value = std::stod(str);
        return true;
    }
    catch(const std::invalid_argument& e){
        return false;
    }
}
