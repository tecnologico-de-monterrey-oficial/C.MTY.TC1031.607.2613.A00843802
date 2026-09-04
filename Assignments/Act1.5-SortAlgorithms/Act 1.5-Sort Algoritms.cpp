//Isis Krystal Agramón Leal
//A00843802

#include <iostream>
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
    //iteramos todos los elementos de la lista hasta el penultimo
    for (int i=0; i < list.size()-1; i++) {
        for (int j=i+1; j<list.size(); j++) {
            //comparamos el valor de j con el valor de i para determinar si es menor
            if (list[j] < list[i]) {
                //si es menor
                //intercambiamos los valores
                swap(list, i, j);
            }
        }
    }
}

template <typename T>
void bubbleSort(vector<T> &list) {
    //definimos un booleano como verdadero
    bool change = true;
    //iterar desde n hasta 1
    for (int i=list.size()-1; i>0 && change; i--) {
        //cambio el valor de change a falso
        change = false;
        //iteramos desde 0 hasta que sea menor que i
        for (int j=0; j<i; j++) {
            //comparamos el valor de j con el valor de j+1 para determinar si es mayor
            if (list[j] > list[j+1]) {
                //si es mayor
                //cambiamos change a verdadero
                change = true;
                //intercambiamos los valores
                swap(list, j, j+1);
            }
        }
    }
}

//Selection Sort
template <typename T>
void selectionSort(vector<T> &list) {
    //iteramos toda la lista desde el principio hasta uno antes del final
    for (int i=0; i<list.size()-1; i++) {
        //hacemos el indice de la posición i como el más chico
        int min = i;
        //iteramos desde el siguiente índice hasta el final
        for (int j=i+1; j<list.size(); j++) {
            //comparamos el valor de j contra min
            if (list[j] < list[min]) {
                //si es menor
                //Actualizamos el valor de min
                min = j;
            }
        }
        //intercambiamos el valor de min por el valor de i
        swap(list, min, i);
    }
}

//Insertion Sort
template <typename T>
void insertionSort(vector<T> &list) {
    //iteramos la lista desde la segunda posición hasta el final
    for (int i=1; i<list.size(); i++) {
        //iteramos desde i hasta 0
        //declaramos un contador para ver donde vamos
        int j = i;
        while (j>0 && list[j] < list[j-1]) {
            //Intercambiamos j con j-1
            swap(list, j, j-1);
            //decrementamos j
            j--;
        }
    }
}

//Quick Sort
template <typename T>
int quickSortAux(vector<T> &list, int left, int right) {
    //tomamos el último elemento como pivote
    T pivot = list[right];
    //aux empieza una posición antes de left
    int aux = left - 1;
    //recorremos la lista desde left hasta antes del pivote
    for (int index = left; index < right; index++) {
        //comparamos el valor de index con el pivote
        if (list[index] < pivot) {
            //avanzamos aux
            aux++;
            //intercambiamos los valores
            swap(list, aux, index);
        }
    }

    //colocamos el pivote en su posición
    swap(list, aux + 1, right);

    //regresamos la posición del pivote
    return aux + 1;
}

//Quick Sort
template <typename T>
void quickSort(vector<T> &list, int left, int right) {

    if (left < right) {
        //obtenemos la posición del pivote
        int pivot = quickSortAux(list, left, right);
        //ordenamos la parte izquierda
        quickSort(list, left, pivot - 1);
        //ordenamos la parte derecha
        quickSort(list, pivot + 1, right);
    }
}

template <typename T>
void print(vector<T> &list) {
    for (int i=0; i<list.size(); i++) {
        cout << list[i] << " ";
    }
    cout << endl;
}

int main() {

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
    list = listOriginal;
    print(list);
    selectionSort(list);
    cout << "Lista ordenada: con Selection Sort" << endl;
    print(list);
    list = listOriginal;
    print(list);
    insertionSort(list);
    cout << "Lista ordenada: con Insertion Sort" << endl;
    print(list);
    list = listOriginal;
    print(list);
    quickSort(list, 0, list.size() - 1);
    cout << "Lista ordenada: con Quick Sort" << endl;
    print(list);
    
    return 0;
}