//Isis Krystal Agramón Leal
//A00843802

#include <iostream>
using namespace std;

int main(){

    int x = 42;
    int *p = &x;

    cout << x << endl;
    cout << &x << endl;
    cout << p << endl;
    cout << *p << endl;

    cout << "Valores de q: " << endl;
    int* q = new int(5);
    cout << q << endl;
    cout << *q << endl;

    delete q;
    cout << q << endl;
    cout << *q << endl;

    return 0;
}