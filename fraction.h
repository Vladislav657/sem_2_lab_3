#include <iostream>

using namespace std;

#ifndef LAB_3_FRACTION_H
#define LAB_3_FRACTION_H

class Fraction{
private:
    int numerator;
    unsigned denominator;

public:
    Fraction();

    Fraction(int numerator, unsigned denominator);

    Fraction(Fraction& other);

    Fraction(Fraction&& other) noexcept;

    friend istream& operator >> (istream& in, Fraction& fraction);

    friend ostream& operator << (ostream& out, Fraction& fraction);

    Fraction operator + (Fraction& other) const;

    Fraction operator - (Fraction& other) const;

    Fraction operator * (Fraction& other) const;

    Fraction operator / (Fraction& other) const;

    Fraction operator += (Fraction& other);

    Fraction operator -= (Fraction& other);

    Fraction operator *= (Fraction& other);

    Fraction operator /= (Fraction& other);

    bool operator == (Fraction& other) const;

    bool operator >= (Fraction& other) const;

    bool operator <= (Fraction& other) const;

    bool operator > (Fraction& other) const;

    bool operator < (Fraction& other) const;

    Fraction operator = (Fraction& other);

    explicit operator double() const;

    explicit operator float () const;

    explicit operator string () const;

    friend Fraction operator ""_F (const char *value);
};

#endif //LAB_3_FRACTION_H
