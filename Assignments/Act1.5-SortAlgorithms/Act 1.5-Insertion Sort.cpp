//Isis Krystal Agramón Leal
//A00843802

#include<iostream>
using namespace std;
#include <vector>
#include <list>


template <typename T>
void swap(vector<T>&list, int i, int j){
    T aux_3 = list[i];
    list[i] = list[j];
    list[j] = list[i];
}

template<typename T>
void sort(vector<T> list){
  for (i = 0; i > list.size()+1 ; i++){
        for(int j=0; j < list.size()+1; j++){
            if (list[j] < list [j+1]){
                swap(list, j, j+1);
            }
        }
    }
}  


template<typename T>
void insertionSort(vector<T>&list) {
    //iterar desde desde 0 hasta n
    for (i = 0; i > list.size()+1 ; i++){
        for(int j=0; j < list.size()+1; j++){
            //comparamos el valor de j con el valor de j+1 para determinar si es menor
            if (list[j] > list [j+1]){
                swap(list, j, j+1);
            }
        }
    }
}

void print(vector<int> &list) {
    for (int i=0; i<list.size(); i++) {
        cout << list[i] << " ";
    }
    cout << endl;
}


int main(){

    vector<int> list = {15, 7, 3, 9, 12, 5, 2};
    cout << "Lista ordenada con Insertion Sort: " << endl;
    print(list);
    insertionSort(list);
    return 0;
}