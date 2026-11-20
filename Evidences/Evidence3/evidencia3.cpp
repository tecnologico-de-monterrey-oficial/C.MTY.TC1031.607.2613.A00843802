//Isis Krystal Agramón Leal
//A008483802

#include <iostream>
#include "Heap3.h"

using namespace std;

int main() {
    Heap<int> heap{less<int>()};

    heap.push(30);
    heap.push(10);
    heap.push(50);
    heap.push(20);

    cout << "Heap: ";
    heap.print();

    cout << "Mayor: " << heap.pop() << endl;

    cout << "Heap despues de pop: ";
    heap.print();

    return 0;
}