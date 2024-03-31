#include "fraction.h"

Fraction::Fraction() {
    this->numerator = 0;
    this->denominator = 1;
}

Fraction::Fraction(int numerator, unsigned int denominator) {
    this->numerator = numerator;
    this->denominator = denominator;
}

Fraction::Fraction(Fraction &other) {
    this->numerator = other.numerator;
    this->denominator = other.denominator;
}

Fraction::Fraction(Fraction &&other)  noexcept {
    this->numerator = other.numerator;
    this->denominator = other.denominator;
}
