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

template <typename T>
void bubbleSort(vector<T> &list) {
    bool change = true;
    for (int i = list.size() - 1; i > 0 && change; i--) {
        change = false;
        for (int j = 0; j < i; j++) {
            if (list[j] > list[j + 1]) {
                change = true;
                swap(list, j, j + 1);
            }
        }
    }
}

template <typename T>
void selectionSort(vector<T> &list) {

    for (int i = 0; i < list.size() - 1; i++) {
        int min = i;
        for (int j = i + 1; j < list.size(); j++) {
            if (list[j] < list[min]) {
                min = j;
            }
            if (min != i) {
                swap(list, min, i);
            }
        }
    }
}

template <typename T>
void insertionSort(vector<T> &list) {

    for (int i = 1; i < list.size(); i++) {
        int j = i;
        while (j > 0) {
            if (list[j] < list[j - 1]) {
                swap(list, j, j - 1);
                j--;
            }
            else {
                break;
            }
        }
    }
}

#endif