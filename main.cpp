#include <iostream>
#include "fraction.h"

using namespace std;

int main(){
    Fraction f1 = Fraction(2, 3);
    Fraction f2 = Fraction(1, 5);
    Fraction f3 = f1;
    auto d = (double) f1;
    auto f = (float) f2;
    auto s = (string) f2;
    cout << d << " " << f << " " << s << endl;
    bool b = f1 > f2;
    cout << b << " " << f3;
    cout << "9/3";
    return 0;
}
