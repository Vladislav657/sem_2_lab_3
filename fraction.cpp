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
    int g = gcd(numerator, denominator);
    if (denominator == 0){
        this->numerator = 0;
        this->denominator = 1;
    } else if (denominator < 0){
        this->numerator = -numerator / g;
        this->denominator = -denominator / g;
    } else{
        this->numerator = numerator / g;
        this->denominator = denominator / g;
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
    int n = 0, d = 1;
    bool flag = false;
    string f;
    in >> f;
    char *frac = new char [f.size()];
    for (int i = 0; i < f.size(); ++i){
        frac[i] = f[i];
        if (f[i] == '/') flag = true;
    }
    int c = flag ? sscanf(frac, "%d/%d", &n, &d) : sscanf(frac, "%d", &n);
    int g = gcd(n, d);
    if (flag && c != 2 || !flag && c != 1 || d == 0){
        fraction.numerator = 0;
        fraction.denominator = 1;
        return in;
    } else if (d < 0){
        fraction.numerator = -n / g;
        fraction.denominator = -d / g;
    } else {
        fraction.numerator = n / g;
        fraction.denominator = d / g;
    }
    return in;
}

ostream &operator<<(ostream &out, Fraction &fraction) {
    if (fraction.numerator == 0 || fraction.denominator == 1) out << fraction.numerator;
    else out << fraction.numerator << '/' << fraction.denominator;
    return out;
}

Fraction Fraction::operator + (Fraction &other) const {
    int n1 = this->numerator * other.denominator;
    int n2 = other.numerator * this->denominator;
    int d = this->denominator * other.denominator;
    int g = gcd(n1 + n2, d);
    return {(n1 + n2) / g, d / g};
}

Fraction Fraction::operator - (Fraction &other) const {
    int n1 = this->numerator * other.denominator;
    int n2 = other.numerator * this->denominator;
    int d = this->denominator * other.denominator;
    int g = gcd(n1 - n2, d);
    return {(n1 - n2) / g, d / g};
}

Fraction Fraction::operator * (Fraction &other) const {
    int n = this->numerator * other.numerator;
    int d = this->denominator * other.denominator;
    int g = gcd(n, d);
    return {n / g, d / g};
}

Fraction Fraction::operator / (Fraction &other) const {
    int n, d;
    if (other.numerator == 0) return {0, 1};
    else if (other.numerator < 0) {
        n = this->numerator * -other.denominator;
        d = this->denominator * -other.numerator;
    } else {
        n = this->numerator * other.denominator;
        d = this->denominator * other.numerator;
    }
    int g = gcd(n, d);
    return {n / g, d / g};
}

Fraction Fraction::operator += (Fraction &other) {
    this->numerator = this->numerator * other.denominator + other.numerator * this->denominator;
    this->denominator = this->denominator * other.denominator;
    int g = gcd(this->numerator, this->denominator);
    this->numerator /= g;
    this->denominator /= g;
    return *this;
}

Fraction Fraction::operator -= (Fraction &other) {
    this->numerator = this->numerator * other.denominator - other.numerator * this->denominator;
    this->denominator = this->denominator * other.denominator;
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

Fraction Fraction::operator-() const {
    return {-this->numerator, this->denominator};
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
    if (this->numerator == 0 || this->denominator == 1) return to_string(this->numerator);
    return to_string(this->numerator) + '/' + to_string(this->denominator);
}

Fraction operator ""_F(const char *value, size_t size) {
    int n = 0, d = 1;
    bool flag = false;
    for (int i = 0; i < size; ++i) if (value[i] == '/') flag = true;
    int c = flag ? sscanf(value, "%d/%d", &n, &d) : sscanf(value, "%d", &n);
    int g = gcd(n, d);
    if (flag && c != 2 || !flag && c != 1 || d == 0) return {0, 1};
    else if (d < 0) return {-n / g, -d / g};
    return {n / g, d / g};
}
