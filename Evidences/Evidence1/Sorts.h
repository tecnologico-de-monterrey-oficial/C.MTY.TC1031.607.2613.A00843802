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
        }
        if (min != i) {
            swap(list, min, i);
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

template <typename T>
int getPivot(vector<T> &list, int left, int right) {
    int aux = left - 1;
    int pivot = right;
    for (int i = left; i < pivot; i++) {
        if (list[i] < list[pivot]) {
            aux++;
            swap(list, aux, i);
        }
    }
    aux++;
    swap(list, aux, pivot);
    return aux;
}

template <typename T>
void quickSort(vector<T> &list, int left, int right) {
    if (left < right) {
        int pivot = getPivot(list, left, right);
        quickSort(list, left, pivot - 1);
        quickSort(list, pivot + 1, right);
    }
}

template <typename T>
void mergeSort(vector<T> &list, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(list, left, mid);
        mergeSort(list, mid + 1, right);
        merge(list, left, mid, right);
    }
}

template <typename T>
void merge(vector<T> &list, int left, int mid, int right) {
    vector<T> leftList;
    vector<T> rightList;
    for (int i = left; i <= mid; i++) {
    leftList.push_back(list[i]);
    }

    for (int j = mid + 1; j <= right; j++) {
    rightList.push_back(list[j]);
    }
    int index = left;
    int i = 0;
    int j = 0;
    while (i < leftList.size() && j < rightList.size()) {
        if (leftList[i] < rightList[j]) {
            list[index] = leftList[i];
            i++;
        }
        else {
            list[index] = rightList[j];
            j++;
        }
        index++;
    }
    while (i < leftList.size()) {
        list[index] = leftList[i];
        i++;
        index++;
    }
    while (j < rightList.size()) {
        list[index] = rightList[j];
        j++;
        index++;
    }
}

template <typename T>
void shellSort(vector<T> &list) {
    for (int gap = list.size() / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < list.size(); i++) {
            T temp = list[i];
            int j = i;
            while (j >= gap && list[j - gap] > temp) {
                list[j] = list[j - gap];
                j -= gap;
            }
            list[j] = temp;
        }
    }
}
#endif