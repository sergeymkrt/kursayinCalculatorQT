//
// Created by Sergey Mkrtumyan on 17.03.23.
//

#ifndef KURSAYINCALCULATOR_NUMBER_H
#define KURSAYINCALCULATOR_NUMBER_H


class Number {
public:
    double Value;
    explicit Number(double value);
    explicit Number();

    Number operator+(Number other) const;
    Number operator-(Number other) const;
    Number operator*(Number other) const;
    Number operator/(Number other) const;
    Number operator%(Number other) const;
    Number operator^(Number other) const;
    Number operator<<(int bits) const;
    Number operator>>(int bits) const;
    bool operator==(Number other) const;
    bool operator!=(Number other) const;
    Number& operator=(Number other);
};


#endif //KURSAYINCALCULATOR_NUMBER_H
