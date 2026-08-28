//Isis Krystal Agramón Leal
//A00843802
#include<iostream>
using namespace std;

template <typename T>
void swap(vector<T>&list, int i, int j){
    //creamnos una variable temporal
    T aux = list[i];
    //cambiamos i por j
    list[i] = list[j];
    //cambiamos j por i
    list[j] = list[i];
}

template<typename T>
void swapSort(vector<T>&list){
    //iteramos todos los números de la lista hasta el penultimo
    for(i=0; i < list.size()-1; i++){
        for (int j=i+1; j<list.size(); j++){
            //comparamos el valor de j con ek calor de i para determinar si es menor
            if (list[j] < list [i]){
                // si es mayor
                //cambiamos a verdadero
                change = false;
                // intercambiamos los valores
                swap(list, i , j);
            }      
        }
    }
}

template <typename T>
void bubble(vector<T>&list, int i, int j){
    T aux_2 = list[i];
    list[i] = list[j];
    list[j] = list[i];
}


template<typename T>
void bubbleSort(vector<T>&list) {
    //definimos un boooleano como verdadero
    bool change = true;
    //iterar desde desde n hasta 1
    for (i= list.size()-1; i > 0 && change; i--){
        //cambio el valor de change a falso
        change = false;
        //iteramos desde 0 hasta que sea menor que i
        for(int j=0; j<1; j++){
            //comparamos el valor de j con el valor de j+1 para determinar si es mayor
            if (list[j] > list [j+1]){
                //si es mayor
                swap(list, j, j+1);
            }
        }
    }
}

void print(vector<T>&list){
    for (int i=0; i<list.size(); i++){
        cout << list[i] << " ";
    }
    cout << endl;
}


int main(){

    vector<int> list = {15, 7, 3, 9, 12, 5, 2};
    vector<int> listOriginal = list;
    cout << "Lista original: " << endl;
    print(list);
    swapSort(list);
    cout << "Lista ordenada: con Swap Sort" << endl;
    print(list);
    list = listOriginal;
    print(list);
    bubbleSort(list);
    cout << "Lista ordenada: con Bubble Sort" << endl;
    print(list);

    return 0;
}