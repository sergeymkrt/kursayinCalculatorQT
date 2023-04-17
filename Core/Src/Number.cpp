//
// Created by Sergey Mkrtumyan on 17.03.23.
//

#include "../Headers/Number.h"
#include "QtMath"

Number::Number(double value) {
    Value = value;
}
Number::Number(){
    Value = 0;
}

Number Number::operator+(Number number) const {
  Number temp;
  asm("FADD %d0, %d1, %d2\n\t"          // ARM64 assembly code to add a and b and store the result in result
    :"=w" (temp.Value)                  // output operand
    :"w"(this->Value),"w"(number.Value) // input operands
    );
  return temp;
}

Number Number::operator-(Number number) const {
    Number temp;
    asm("FSUB %d0, %d1, %d2\n\t"            // ARM64 assembly code to add a and b and store the result in result
        :"=w" (temp.Value)                  // output operand
        :"w"(this->Value),"w"(number.Value) // input operands
    );
    return temp;
}

Number Number::operator*(Number other) const {
    Number temp;
    asm("FMUL %d0, %d1, %d2\n\t"             // ARM64 assembly code to add a and b and store the result in result
        :"=w" (temp.Value)                   // output operand
        :"w"(this->Value),"w"(other.Value)   // input operands
    );
    return temp;
}

Number Number::operator/(Number other) const {
    Number temp;
    asm("FDIV %d0, %d1, %d2\n\t"            // ARM64 assembly code to add a and b and store the result in result
        :"=w" (temp.Value)                  // output operand
        :"w"(this->Value),"w"(other.Value)  // input operands
    );
    return temp;
}

Number Number::operator%(Number other) const {
    Number temp;
    asm("FDIV %d0, %d1, %d2\n\t"
        "FRINTM %d0, %d0\n\t"
        "FMUL %d0, %d0, %d2\n\t"
        "FSUB %d0, %d3, %d0\n\t"
        :"=w" (temp.Value)
        :"w"(this->Value),"w"(other.Value),"w"(this->Value)
    );
    return temp;
}

Number Number::operator^(Number other) const {
    Number result;
    double base = this->Value;
    double exponent = other.Value;

    asm("LDR D0, %[exponent]\n\t"
        "LDR D1, %[base]\n\t"
        "FMOV D2, #1.0\n\t"
        "FMOV D3, #1.0\n\t"
        "loop:\n\t"
        "   FCMP D0, #0.0\n\t"      // compare exponent to zero
        "   BLE 1f\n\t"             // branch if exponent is less than or equal to zero//
        "   FMUL D2, D2, D1\n\t"    // multiply result by base
        "   FSUB D0, D0, D3\n\t"    // decrement exponent
        "   B loop\n\t"             // branch to loop
        "1:\n\t"
        "   FMOV %[result], D2\n\t" // move the result to the output variable

        : [result] "=&r" (result.Value)
        : [exponent]"m" (exponent), [base] "m" (base)
        : "d0", "d1", "d2", "d3"
    );

    return result;
}

Number Number::operator<<(int bits) const {
    // shift left by bits
    return Number(this->Value * std::ldexp(1.0,bits));
}

Number Number::operator>>(int bits) const {
    // shift right by bits
    return Number(this->Value * std::ldexp(1.0,-bits));
}

bool Number::operator==(Number other) const {
    return this->Value == other.Value;
}

Number& Number::operator=(Number other) {
    this->Value = other.Value;
    return *this;
}

bool Number::operator!=(Number other) const {
    return this->Value != other.Value;
}
