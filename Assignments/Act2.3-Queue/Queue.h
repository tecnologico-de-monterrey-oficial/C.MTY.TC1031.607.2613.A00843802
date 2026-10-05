//Isis Krystal Agramón Leal
//A00843802

#include <iostream>
#include <stdexcept>
#include "NodeQ.h"

using namespace std;

#ifndef Queue_h
#define Queue_h

template<typename T>
class Queue {
    private:
        NodeQ<T>* head;
        NodeQ<T>* tail;
        int size;

    public:
        Queue() : head(nullptr), tail(nullptr), size(0) {}
        T pop();
        void push(T data);
        T front();
        int getSize();
        void print();
};

template <typename T>
T Queue<T>::pop() {
    //validamos que la fila no este vacía
    if (head != nullptr) {
        //guardamos el dato del primer elemento
        T data = head->data;

        //validamos que si solo hay un elemento
        if (head == tail) {
            //creamos un apuntador auxiliar para head
            NodeQ<T>* aux = head;
            //borramos aux
            delete aux;
            //inicializamos head y tail
            head = nullptr;
            tail = nullptr;
        } else {
            //creamos un apuntador auxiliar a head
            NodeQ<T>* aux = head;
            //actualizamos head
            head = head->next;
            //borramos el primer elemento
            delete aux;
        }
        size--;

        //regresamos el dato eliminado
        return data;
    }

    //si la fila esta vacía
    throw out_of_range("No hay elementos en la fila");
}
        
template <typename T>
void Queue<T>::push(T data) {
    //validamos si la fila esta vacía
    if (head != nullptr) {
        //la fila no esta vacía
        //actualizamos el next de tail con un nodo nuevo
        tail->next = new NodeQ<T>(data);
        //actualizamos tail con tail->next
        tail = tail->next;
    } else {
        //apunto head a un nuevo nodo
        head = new NodeQ<T>(data);
        //apunto tail a head
        tail = head;
    }

    size++;
}


template <typename T>
T Queue<T>::front() {
    //validamos si la fila esta vacia
    if (head != nullptr) {
        //la fila no está vacía
        return head->data;
    }

    //si la fila esta vacía
    throw out_of_range("No hay elementos en la fila");
}

template <typename T>
int Queue<T>::getSize() {
    return size;
}

template<typename T>
void Queue<T>::print() {
    NodeQ<T>* aux = head;

    while (aux != nullptr) {
        cout << aux->data;
        aux = aux->next;

        if (aux != nullptr) {
            cout << "-";
        }
    }

    cout << aux->data;;
}

#endif