//
// Created by Sergey Mkrtumyan on 17.03.23.
//

#ifndef KURSAYINCALCULATOR_NUMBER_H
#define KURSAYINCALCULATOR_NUMBER_H


class Number {
public:
    double Value;
    explicit Number(double value);

    Number operator+(Number other) const;
    Number operator-(Number other) const;
    Number operator*(Number other) const;
    Number operator/(Number other) const;
    Number operator%(Number other) const;
    Number operator^(Number other) const;
};


#endif //KURSAYINCALCULATOR_NUMBER_H
