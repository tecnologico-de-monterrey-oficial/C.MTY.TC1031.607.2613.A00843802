//Isis Krystal Agramón Leal
//A00843802

#include "NodeS.h"
#include <stdexcept>

#ifndef Stack_h
#define Stack_h

template<typename T>
class Stack {
private:
    NodeS<T>* head;
    int size;
public:
    Stack() : head(nullptr), size(0) {}
    T pop();
    void push(T data);
    T top();
    int getSize();
};

template <typename T>
void Stack<T>::push(T data) {
    //creamos un apuntador auxiliar a un nuevo nodo
    NodeS<T>* aux = new NodeS<T>(data, head);
    //actualizamos head
    head = aux;
    size++;
}

template <typename T>
T Stack<T>::pop() {
    //validamos que la pila no esté vacía
    if (head != nullptr) {
        //guardamos el dato del primer elemento
        T data = head->data;
        //creamos un apuntador auxiliar a head
        NodeS<T>* aux = head;
        //actualizamos head
        head = head->next;
        //borramos el nodo anterior
        delete aux;
        size--;
        //regresamos el dato eliminado
        return data;
    }
    //si la pila está vacía
    throw std::out_of_range("No hay elementos en la pila");
}

template <typename T>
T Stack<T>::top() {
    //validamos si la pila está vacía
    if (head != nullptr) {
        //regresamos el último elemento agregado
        return head->data;
    }
    //si la pila está vacía
    throw std::out_of_range("No hay elementos en la pila");
}

template <typename T>
int Stack<T>::getSize() {
    return size;
}
#endif