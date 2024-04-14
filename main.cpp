#include <iostream>
#include "fraction.h"

using namespace std;


int main(){
    Fraction f1 = Fraction(10, 15);
    Fraction f2 = Fraction(-7, 11);
    Fraction f3 = -f1;

    cout << f3 << " " << f1 << endl;

    auto d = (double) f1;
    auto f = (float) f2;
    auto s = (string) f2;

    Fraction add = f1 + f2;
    Fraction sub = f3 - f1;
    Fraction mul = f3 * f2;
    Fraction div = f1 / f2;

    cout << add << ' ' << sub << ' ' << mul << ' ' << div << endl;
    cout << d << " " << f << " " << s << endl;

    bool b = f1 > f2;
    cout << b << " " << f3 << endl;

    Fraction f6 = "10/-5"_F;
    cout << f6 << endl;

    cout << f1 << ' ' << f2 << ' ' << f3 << endl;

    f1 += f2;
    cout << f1 << endl;

    f1 = f3;
    cout << f1;

    return 0;
}
