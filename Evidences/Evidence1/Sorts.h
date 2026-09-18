#ifndef Sorts_h
#define Sorts_h

#include <vector>
using namespace std;

template <typename T>
void swap(vector<T> &list, int i, int j) {
    if (i != j) {
        //creamos una variable temporal
        T aux = list[i];
        //cambiamos i por j
        list[i] = list[j];
        //cambiamos j por aux
        list[j] = aux;
    }
}

template <typename T>
void swapSort(vector<T> &list) {
    for (int i = 0; i < list.size() - 1; i++) {
        for (int j = i + 1; j < list.size(); j++) {
            if (list[j] < list[i]) {
                 swap(list, i, j);
            }
        }
    }
 }

#endif