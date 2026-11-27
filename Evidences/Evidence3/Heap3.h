
 //Isis Krystal Agramón Leal
//A00843802

#ifndef Heap_h
#define Heap_h

#include <vector>
#include <iostream>
#include <stdexcept>
#include <functional>

using namespace std;

template <typename T>
class Heap {
private:
    vector<T> heap;
    function<bool(const T&, const T&)> compare;
    void swap(int a, int b);
    void shiftDown(int aux);

    long long comparisons = 0;

public:
    Heap() : compare(greater<T>()) {};
    Heap(vector<T> list);
    Heap(function<bool(const T&, const T&)> comp);
    Heap(vector<T> list, function<bool(const T&, const T&)> comp);
    void push(T data);
    T pop();
    void print();
    void printTree(int index, int space);

    T top();
    int size();
    bool empty();
    int height();
    long long getComparisons();
    void resetComparisons();
};

//shiftdown
template <typename T>
void Heap<T>::shiftDown(int aux) {
    //obtenemos el ultimo parent
    int lastParent = static_cast<int>(heap.size()) / 2 - 1;

    //iteramos mientras los hijos de aux sean padres
    while (aux <= lastParent) {
        //calculamos el índice de primer hijo
        int first = aux * 2 + 1;

        //validar si aux tiene 2 hijos o 1 hijo
        //definimos una variable para determinar cual hijo es mayor
        int elder;

        if (first == static_cast<int>(heap.size()) - 1) {
            //tiene un hijo
            elder = first;
        } else {
            //tiene dos hijos
            //calculamos el 2do hijo
            int second = aux * 2 + 2;

            //validamos cual es que tiene mayor prioridad
            comparisons++; //NUEVO
            elder = compare(heap[first], heap[second]) ? first : second;
        }

        //comparamos si el más grande de los hijos es mayor a aux
        comparisons++; //NUEVO

        if (compare(heap[elder], heap[aux])) {
            //el mayor de los hijos es de mayor prioridad que el padre
            swap(aux, elder);

            //cambiamos el valor de aux igual a elder
            aux = elder;
        } else {
            aux = lastParent + 1;
        }
    }
}

//constructor en base a una lista
template <typename T>
Heap<T>::Heap(vector<T> list) {
    //inicializamos el comparador
    compare = greater<T>();

    //actualizamos heap con el valor de list
    heap = list;

    //determinar cual es el último de los padres
    int lastParent = static_cast<int>(heap.size()) / 2 - 1;

    //iteramos desde el último de los padres hasta el primero
    int parent = lastParent;

    while (parent >= 0) {
        shiftDown(parent);

        //decrementamos el valor del indice del padre actual
        parent--;
    }
}

//constructor con comparador
template <typename T>
Heap<T>::Heap(function<bool(const T&, const T&)> comp) {
    compare = comp;
}

//constructor con lista y comparador
template <typename T>
Heap<T>::Heap(vector<T> list, function<bool(const T&, const T&)> comp) {
    compare = comp;
    heap = list;

    int lastParent = static_cast<int>(heap.size()) / 2 - 1;

    for (int parent = lastParent; parent >= 0; parent--) {
        shiftDown(parent);
    }
}

//swap function to swap two elements in the heap
template <typename T>
void Heap<T>::swap(int a, int b) {
    T temp = heap[a];
    heap[a] = heap[b];
    heap[b] = temp;
}

template <typename T>
T Heap<T>::pop() {
    if (heap.size() > 0) {
        T data = heap[0];
        heap[0] = heap[heap.size()-1];
        heap.pop_back();
        shiftDown(0);
        return data;
    }

    throw out_of_range("Heap is empty");
}

template <typename T>
void Heap<T>::push(T data) {
    //agregamos el elemento al final
    heap.push_back(data);

    //obtenemos el indice del elemento agregado
    int index = heap.size() - 1;

    //repetimos mientras no lleguemos a la raiz
    while (index > 0) {
        //calculamos el indice del padre
        int father = (index - 1) / 2;

        //comparamos el elemento con su padre
        comparisons++; //NUEVO

        if (compare(heap[index], heap[father])) {
            swap(index, father);
            index = father;
        } else {
            break;
        }
    }
}

//print function to print the elements of the heap
template <typename T>
void Heap<T>::print() {
    for (int i = 0; i < heap.size(); i++) {
        cout << heap[i] << " ";
    }

    cout << endl;
}

//print del tree
template <typename T>
void Heap<T>::printTree(int index, int space) {
    if (index >= heap.size()) {
        return;
    }

    space += 5;

    printTree(2 * index + 2, space);

    cout << endl;

    for (int i = 5; i < space; i++) {
        cout << " ";
    }

    cout << heap[index] << "\n";

    printTree(2 * index + 1, space);
}

//regresa el elemento de mayor prioridad
template <typename T>
T Heap<T>::top() {
    if (heap.empty()) {
        throw out_of_range("Heap is empty");
    }

    return heap[0];
}

//regresa la cantidad de elementos
template <typename T>
int Heap<T>::size() {
    return static_cast<int>(heap.size());
}

//valida si el heap está vacío
template <typename T>
bool Heap<T>::empty() {
    return heap.empty();
}

//regresa la altura del heap
template <typename T>
int Heap<T>::height() {
    int elements = heap.size();
    int h = -1;

    while (elements > 0) {
        elements = elements / 2;
        h++;
    }

    return h;
}

//regresa la cantidad de comparaciones
template <typename T>
long long Heap<T>::getComparisons() {
    return comparisons;
}

//reinicia el contador de comparaciones
template <typename T>
void Heap<T>::resetComparisons() {
    comparisons = 0;
}

#endif /* Heap_h */
