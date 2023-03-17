//
// Created by Sergey Mkrtumyan on 17.03.23.
//

#include "Number.h"
#include "QtMath"
Number::Number(double value) {
    Value = value;
}

Number Number::operator+(Number number) const {
    return Number(this->Value + number.Value);
}

Number Number::operator-(Number number) const {
    return Number(this->Value - number.Value);
}

Number Number::operator*(Number other) const {
    return Number(this->Value * other.Value);
}

Number Number::operator/(Number other) const {
    return Number(this->Value / other.Value);
}

Number Number::operator%(Number other) const {
    return Number(fmod(this->Value, other.Value));
}

Number Number::operator^(Number other) const {
    return Number(qPow(this->Value, other.Value));
}
