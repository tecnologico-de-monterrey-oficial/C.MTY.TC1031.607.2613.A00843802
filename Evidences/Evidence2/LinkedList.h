//Isis Krystal Agramón Leal
//A00843802

#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>
#include <stdexcept>
#include "Node.h"

using namespace std;

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}
    void addFirst(T data);
    void addLast(T data);
    bool deleteFirst();
    int getSize();
    T getData(int index);
    void print();
};

template <typename T>
void LinkedList<T>::addFirst(T data) {
    if(head == nullptr){
        Node<T>* node = new Node<T>(data);
        head = node;
        tail = head;
        size++;
    }else{
        //crear un nodo nuevo
        Node<T>* node = new Node<T>(data);
        //actualizo el next del nodo nuevo para que apunte a head
        node->next = head;
        //actualizo head
        head = node;
        size++;
    }
}

template <typename T>
void LinkedList<T>::addLast(T data) {
    //validamos si la lista vacía
    if (head != nullptr) {
        //la lista no esta vacía
        tail->next = new Node<T>(data);
        tail = tail->next;
    } else {
        //la lista esta vacía
        head = new Node<T>(data);
        tail = head;
    }
    //incrementamos size
    size++;
}

template <typename T>
bool LinkedList<T>::deleteFirst() {
    //validamos que la lista no este vacia
    if (head == nullptr) {
        return false;
    }
    //guardamos el primer nodo
    Node<T>* aux = head;
    //actualizamos head
    head = head->next;
    //si la lista queda vacia, actualizamos tail
    if (head == nullptr) {
        tail = nullptr;
    }
    //borramos el primer nodo
    delete aux;
    size--;
    return true;
}

template <typename T>
int LinkedList<T>::getSize() {
    //regresamos el tamaño de la lista
    return size;
}

template <typename T>
T LinkedList<T>::getData(int index) {
    //validamos que la posicion exista
    if (index < 0 || index >= size) {
        throw out_of_range("La posición no existe en la lista");
    }

    Node<T>* aux = head;
    //recorremos hasta llegar a la posicion
    for (int i = 0; i < index; i++) {
        aux = aux->next;
    }

    return aux->data;
}

template <typename T>
void LinkedList<T>::print() {
    // creamos un apuntador auxiliar que apunte a head
    Node<T>* aux = head;
    // recorremos la lista mientras aux sea diferente de nullptr
    while (aux != nullptr) {
        cout << aux->data;
        aux = aux->next;
        if (aux != nullptr) {
            cout << "-";
        }
    }

    cout << endl;
}





#endif /* LinkedList_h */