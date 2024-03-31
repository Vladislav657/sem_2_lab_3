#include <iostream>

using namespace std;

#ifndef LAB_3_FRACTION_H
#define LAB_3_FRACTION_H

class Fraction{
    int numerator;
    unsigned denominator;

    Fraction();

    Fraction(int numerator, unsigned denominator);

    Fraction(Fraction& other);

    Fraction(Fraction&& other) noexcept;

    friend istream& operator >> (istream& in, Fraction& fraction);

    friend ostream& operator << (ostream& out, Fraction& fraction);

    Fraction& operator + (Fraction& other);

    Fraction& operator - (Fraction& other);

    Fraction& operator * (Fraction& other);

    Fraction& operator / (Fraction& other);

    Fraction& operator += (Fraction& other);

    Fraction& operator -= (Fraction& other);

    Fraction& operator *= (Fraction& other);

    Fraction& operator /= (Fraction& other);

    bool operator == (Fraction& other);

    bool operator >= (Fraction& other);

    bool operator <= (Fraction& other);

    bool operator > (Fraction& other);

    bool operator < (Fraction& other);

    Fraction& operator = (Fraction& other);

    operator double();

    operator float ();

    operator string ();

    friend Fraction& operator ""_f (const char *value);
};

#endif //LAB_3_FRACTION_H
