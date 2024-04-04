#include "fraction.h"

int gcd(int x, int y) {
    if (x < 0) x = -x;
    if (y < 0) y = -y;
    while (x != 0 && y != 0){
        if (x > y) x %= y;
        else y %= x;
    }
    return x + y;
}

Fraction::Fraction() {
    this->numerator = 0;
    this->denominator = 1;
}

Fraction::Fraction(int numerator, int denominator) {
    if (denominator == 0){
        this->numerator = 0;
        this->denominator = 1;
    } else if (denominator < 0){
        this->numerator = -numerator;
        this->denominator = -denominator;
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
    int d;
    string f;
    in >> f;
    char *frac = new char [f.size()];
    for (int i = 0; i < f.size(); ++i) frac[i] = f[i];
    sscanf(frac, "%d/%d", &n, &d);
    if (d == 0){
        fraction.numerator = 0;
        fraction.denominator = 1;
        return in;
    } else if (d < 0){
        fraction.numerator = -n;
        fraction.denominator = -d;
    }
    fraction.numerator = n;
    fraction.denominator = d;
    return in;
}

ostream &operator<<(ostream &out, Fraction &fraction) {
    if (fraction.numerator == 0) out << fraction.numerator;
    else out << fraction.numerator << '/' << fraction.denominator;
    return out;
}

Fraction Fraction::operator + (Fraction &other) const {
    int n1, n2, d;
    if (other.denominator % this->denominator == 0){
        n1 = this->numerator * (other.denominator / this->denominator);
        n2 = other.numerator;
        d = other.denominator;
    } else if (this->denominator % other.denominator == 0){
        n1 = this->numerator;
        n2 = other.numerator * (this->denominator / other.denominator);
        d = this->denominator;
    } else {
        n1 = this->numerator * other.denominator;
        n2 = other.numerator * this->denominator;
        d = this->denominator * other.denominator;
    }
    return {n1 + n2, d};
}

Fraction Fraction::operator - (Fraction &other) const {
    int n1, n2, d;
    if (other.denominator % this->denominator == 0){
        n1 = this->numerator * (other.denominator / this->denominator);
        n2 = other.numerator;
        d = other.denominator;
    } else if (this->denominator % other.denominator == 0){
        n1 = this->numerator;
        n2 = other.numerator * (this->denominator / other.denominator);
        d = this->denominator;
    } else {
        n1 = this->numerator * other.denominator;
        n2 = other.numerator * this->denominator;
        d = this->denominator * other.denominator;
    }
    return {n1 - n2, d};
}

Fraction Fraction::operator * (Fraction &other) const {
    return {this->numerator * other.numerator, this->denominator * other.denominator};
}

Fraction Fraction::operator / (Fraction &other) const {
    int n, d;
    if (other.numerator == 0) return {0, 1};
    else if (other.numerator < 0) {
        n = this->numerator * other.denominator;
        d = this->denominator * other.numerator;
        int g = gcd(n, d);
        n = -n / g;
        d = -d / g;
    }
    n = this->numerator * other.denominator;
    d = this->denominator * other.numerator;
    int g = gcd(n, d);
    n = n / g;
    d = d / g;
    return {n, d};
}

Fraction Fraction::operator += (Fraction &other) {
    if (other.denominator % this->denominator == 0){
        this->numerator = this->numerator * (other.denominator / this->denominator) + other.numerator;
        this->denominator = other.denominator;
    } else if (this->denominator % other.denominator == 0){
        this->numerator = this->numerator + other.numerator * (this->denominator / other.denominator);
    } else {
        this->numerator = this->numerator * other.denominator + other.numerator * this->denominator;
        this->denominator = this->denominator * other.denominator;
    }
    int g = gcd(this->numerator, this->denominator);
    this->numerator /= g;
    this->denominator /= g;
    return *this;
}

Fraction Fraction::operator -= (Fraction &other) {
    if (other.denominator % this->denominator == 0){
        this->numerator = this->numerator * (other.denominator / this->denominator) - other.numerator;
        this->denominator = other.denominator;
    } else if (this->denominator % other.denominator == 0){
        this->numerator = this->numerator - other.numerator * (this->denominator / other.denominator);
    } else {
        this->numerator = this->numerator * other.denominator - other.numerator * this->denominator;
        this->denominator = this->denominator * other.denominator;
    }
    int g = gcd(this->numerator, this->denominator);
    this->numerator /= g;
    this->denominator /= g;
    return *this;
}

Fraction Fraction::operator*=(Fraction &other) {
    this->numerator *= other.numerator;
    this->denominator *= other.denominator;
    int g = gcd(this->numerator, this->denominator);
    this->numerator /= g;
    this->denominator /= g;
    return *this;
}

Fraction Fraction::operator/=(Fraction &other) {
    if (other.numerator == 0) return *this;
    else if (other.numerator < 0){
        this->numerator *= -other.denominator;
        this->denominator *= -other.numerator;
    } else {
        this->numerator *= other.denominator;
        this->denominator *= other.numerator;
    }
    int g = gcd(this->numerator, this->denominator);
    this->numerator /= g;
    this->denominator /= g;
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
    this->numerator = other.numerator;
    this->denominator = other.denominator;
    return *this;
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

Fraction operator ""_F(const char *value, size_t) {
    int n, d;
    sscanf(value, "%d/%d", &n, &d);
    if (d == 0) return {0, 1};
    else if (d < 0) return {-n, -d};
    int g = gcd(n, d);
    return {n / g, d / g};
}
