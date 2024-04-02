#include "fraction.h"

Fraction::Fraction() {
    this->numerator = 0;
    this->denominator = 1;
}

Fraction::Fraction(int numerator, unsigned denominator) {
    if (denominator == 0){
        this->numerator = 0;
        this->denominator = 1;
    } else {
        this->numerator = numerator;
        this->denominator = denominator;
    }
}

Fraction::Fraction(Fraction &other) {
    this->numerator = other.numerator;
    this->denominator = other.denominator;
}

Fraction::Fraction(Fraction &&other)  noexcept {
    this->numerator = other.numerator;
    this->denominator = other.denominator;
}

istream &operator>>(istream &in, Fraction &fraction) {
    int n;
    unsigned d;
    string f;
    in >> f;
    char *frac = new char [f.size()];
    for (int i = 0; i < f.size(); ++i) frac[i] = f[i];
    sscanf(frac, "%d/%u", &n, &d);
    if (d <= 0) return in;
    fraction.numerator = n;
    fraction.denominator = d;
    return in;
}

ostream &operator<<(ostream &out, Fraction &fraction) {
    out << fraction.numerator << '/' << fraction.denominator;
    return out;
}

Fraction Fraction::operator + (Fraction &other) const {
    int n1, n2;
    unsigned d;
    if (other.denominator % this->denominator == 0){
        n1 = this->numerator * (int)(other.denominator / this->denominator);
        n2 = other.numerator;
        d = other.denominator;
    } else if (this->denominator % other.denominator == 0){
        n1 = this->numerator;
        n2 = other.numerator * (int)(this->denominator / other.denominator);
        d = this->denominator;
    } else {
        n1 = this->numerator * (int)other.denominator;
        n2 = other.numerator * (int)this->denominator;
        d = this->denominator * other.denominator;
    }
    return {n1 + n2, d};
}

Fraction Fraction::operator - (Fraction &other) const {
    int n1, n2;
    unsigned d;
    if (other.denominator % this->denominator == 0){
        n1 = this->numerator * (int)(other.denominator / this->denominator);
        n2 = other.numerator;
        d = other.denominator;
    } else if (this->denominator % other.denominator == 0){
        n1 = this->numerator;
        n2 = other.numerator * (int)(this->denominator / other.denominator);
        d = this->denominator;
    } else {
        n1 = this->numerator * (int)other.denominator;
        n2 = other.numerator * (int)this->denominator;
        d = this->denominator * other.denominator;
    }
    return {n1 - n2, d};
}

Fraction Fraction::operator * (Fraction &other) const {
    return {this->numerator * other.numerator, this->denominator * other.denominator};
}

Fraction Fraction::operator / (Fraction &other) const {
    if (other.numerator == 0) return {0, 1};
    return {this->numerator * (int)other.denominator, this->denominator * other.numerator};
}

Fraction Fraction::operator += (Fraction &other) {
    if (other.denominator % this->denominator == 0){
        this->numerator = this->numerator * (int)(other.denominator / this->denominator) + other.numerator;
        this->denominator = other.denominator;
    } else if (this->denominator % other.denominator == 0){
        this->numerator = this->numerator + other.numerator * (int)(this->denominator / other.denominator);
    } else {
        this->numerator = this->numerator * (int)other.denominator + other.numerator * (int)this->denominator;
        this->denominator = this->denominator * other.denominator;
    }
    return *this;
}

Fraction Fraction::operator -= (Fraction &other) {
    if (other.denominator % this->denominator == 0){
        this->numerator = this->numerator * (int)(other.denominator / this->denominator) - other.numerator;
        this->denominator = other.denominator;
    } else if (this->denominator % other.denominator == 0){
        this->numerator = this->numerator - other.numerator * (int)(this->denominator / other.denominator);
    } else {
        this->numerator = this->numerator * (int)other.denominator - other.numerator * (int)this->denominator;
        this->denominator = this->denominator * other.denominator;
    }
    return *this;
}

Fraction Fraction::operator*=(Fraction &other) {
    this->numerator *= other.numerator;
    this->denominator *= other.denominator;
    return *this;
}

Fraction Fraction::operator/=(Fraction &other) {
    if (other.numerator != 0){
        this->numerator *= (int)other.denominator;
        this->denominator *= other.numerator;
    }
    return *this;
}

bool Fraction::operator == (Fraction &other) const {
    return (long double) this->numerator / this->denominator == (long double) other.numerator / other.denominator;
}

bool Fraction::operator >= (Fraction &other) const {
    return (long double) this->numerator / this->denominator >= (long double) other.numerator / other.denominator;
}

bool Fraction::operator <= (Fraction &other) const {
    return (long double) this->numerator / this->denominator <= (long double) other.numerator / other.denominator;
}

bool Fraction::operator > (Fraction &other) const {
    return (long double) this->numerator / this->denominator > (long double) other.numerator / other.denominator;
}

bool Fraction::operator < (Fraction &other) const {
    return (long double) this->numerator / this->denominator < (long double) other.numerator / other.denominator;
}

Fraction Fraction::operator = (Fraction &other) {
    return {other.numerator, other.denominator};
}

Fraction::operator double() const {
    return (double) this->numerator / (double)this->denominator;
}

Fraction::operator float() const {
    return (float) this->numerator / (float)this->denominator;
}

Fraction::operator string() const {
    return to_string(this->numerator) + '/' + to_string(this->denominator);
}

Fraction operator ""_F(const char *value) {
    int n;
    unsigned d;
    sscanf(value, "%d/%u", &n, &d);
    if (d <= 0) return {0, 1};
    return {n, d};
}
