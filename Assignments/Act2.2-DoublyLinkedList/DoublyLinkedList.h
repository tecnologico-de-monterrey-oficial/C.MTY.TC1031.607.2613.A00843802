//Isis Krystal Agramón Leal
//A00843802

#ifndef DoublyLinkedList_h
#define DoublyLinkedList_h

#include <iostream>
#include <stdexcept>
#include "NodeD.h"

using namespace std;

template <typename T>
class DoublyLinkedList {
private:
    NodeD<T>* head;
    NodeD<T>* tail;
    int size = 0;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    DoublyLinkedList(const DoublyLinkedList<T>& other);
    ~DoublyLinkedList();

    void addFirst(T data);
    void addLast(T data);
    void insert(int index, T data);
    bool deleteAt(int index);
    int findData(T data);
    bool deleteData(T data);
    T getData(int index);
    void updateData(T data, T newData);
    void updateAt(int index, T data);
    T& operator[](int index);
    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& other);
    void clear();
    void sort();
    void duplicate();
    void removeDuplicates();
    void print();
    int getSize();
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other)
    : head(nullptr), tail(nullptr), size(0) {
    //creamos un apuntador auxiliar
    NodeD<T>* aux = other.head;
    //recorremos la otra lista
    while (aux != nullptr) {
        addLast(aux->data);
        aux = aux->next;
    }
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

template <typename T>
void DoublyLinkedList<T>::addFirst(T data) {
    //validamos si la lista está vacía
    if (head == nullptr) {
        //apuntamos head a un nuevo nodo
        head = new NodeD<T>(data);
        //apuntamos tail a head
        tail = head;
        //incrementamos size
        size++;
    } else {
        //creamos un nuevo nodo
        NodeD<T>* aux = new NodeD<T>(data);
        //apuntamos el next de aux a head
        aux->next = head;
        //apuntamos el prev de head a aux
        head->prev = aux;
        //apuntamos head a aux
        head = aux;
        //incrementamos size
        size++;
    }
}

template <typename T>
void DoublyLinkedList<T>::addLast(T data) {
    //validamos si la lista está vacía
    if (head == nullptr) {
        //apuntamos head a un nuevo nodo
        head = new NodeD<T>(data);
        //apuntamos tail a head
        tail = head;
        //incrementamos size
        size++;
    } else {
        //creamos un nuevo nodo
        NodeD<T>* aux = new NodeD<T>(data);
        //apuntamos el prev de aux a tail
        aux->prev = tail;
        //apuntamos el next de tail a aux
        tail->next = aux;
        //apuntamos tail a aux
        tail = aux;
        //incrementamos size
        size++;
    }
}

template <typename T>
void DoublyLinkedList<T>::insert(int index, T data) {
    //validamos que el índice sea válido
    if (index >= 0 && index < size) {
        //validamos si queremos insertar después del último
        if (index == size - 1) {
            addLast(data);
        } else {
            //creamos un índice auxiliar
            int auxIndex = 0;
            //creamos un apuntador auxiliar igual a head
            NodeD<T>* aux = head;
            //recorremos hasta encontrar el índice
            while (auxIndex < index) {
                aux = aux->next;
                auxIndex++;
            }
            //creamos un nuevo nodo
            NodeD<T>* auxNew = new NodeD<T>(data);
            //apuntamos el prev del nuevo a aux
            auxNew->prev = aux;
            //apuntamos el next del nuevo al siguiente
            auxNew->next = aux->next;
            //actualizamos el prev del siguiente nodo
            aux->next->prev = auxNew;
            //apuntamos el next de aux al nuevo
            aux->next = auxNew;
            //incrementamos size
            size++;
        }
    } else {
        throw out_of_range("Indice invalido");
    }
}

template <typename T>
bool DoublyLinkedList<T>::deleteAt(int index) {
    //validamos que el índice sea válido
    if (index < 0 || index >= size) {
        return false;
    }
    //validamos si solo hay un elemento
    if (head == tail) {
        NodeD<T>* aux = head;
        head = nullptr;
        tail = nullptr;
        delete aux;
        size--;
        return true;
    }
    //validamos si queremos borrar el primero
    if (index == 0) {
        NodeD<T>* aux = head;
        head = head->next;
        head->prev = nullptr;
        delete aux;
        size--;
        return true;
    }
    //validamos si queremos borrar el último
    if (index == size - 1) {
        NodeD<T>* aux = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete aux;
        size--;
        return true;
    }
    //borramos un elemento de en medio
    NodeD<T>* aux;
    if (index <= (size - 1) / 2) {
        //recorremos por la izquierda
        int auxIndex = 0;
        aux = head;
        while (auxIndex < index) {
            aux = aux->next;
            auxIndex++;
        }
    } else {
        //recorremos por la derecha
        int auxIndex = size - 1;
        aux = tail;
        while (auxIndex > index) {
            aux = aux->prev;
            auxIndex--;
        }
    }
    //actualizamos los apuntadores
    aux->prev->next = aux->next;
    aux->next->prev = aux->prev;
    //liberamos aux
    delete aux;
    //decrementamos size
    size--;
    return true;
}

template <typename T>
int DoublyLinkedList<T>::findData(T data) {
    //creamos un apuntador auxiliar
    NodeD<T>* aux = head;
    //inicializamos un índice auxiliar
    int auxIndex = 0;
    //recorremos la lista
    while (aux != nullptr) {
        if (aux->data == data) {
            return auxIndex;
        }
        aux = aux->next;
        auxIndex++;
    }
    //el dato no se encuentra
    return -1;
}

template <typename T>
bool DoublyLinkedList<T>::deleteData(T data) {
    //buscamos el dato
    int index = findData(data);
    //validamos si lo encontramos
    if (index == -1) {
        return false;
    }
    //borramos el elemento encontrado
    return deleteAt(index);
}

template <typename T>
T DoublyLinkedList<T>::getData(int index) {
    //validamos el índice
    if (index < 0 || index >= size) {
        throw out_of_range("Indice invalido");
    }
    //creamos un apuntador auxiliar
    NodeD<T>* aux;
    if (index <= (size - 1) / 2) {
        //recorremos desde head
        aux = head;
        for (int i = 0; i < index; i++) {
            aux = aux->next;
        }
    } else {
        //recorremos desde tail
        aux = tail;
        for (int i = size - 1; i > index; i--) {
            aux = aux->prev;
        }
    }
    return aux->data;
}

template <typename T>
void DoublyLinkedList<T>::updateData(T data, T newData) {
    //buscamos el dato
    int index = findData(data);
    //validamos si lo encontramos
    if (index == -1) {
        throw out_of_range("Dato no encontrado");
    }
    //actualizamos el elemento
    updateAt(index, newData);
}

template <typename T>
void DoublyLinkedList<T>::updateAt(int index, T data) {
    //validamos el índice
    if (index < 0 || index >= size) {
        throw out_of_range("Indice invalido");
    }
    //actualizamos el dato utilizando el operador []
    (*this)[index] = data;
}

template <typename T>
T& DoublyLinkedList<T>::operator[](int index) {
    //validamos el índice
    if (index < 0 || index >= size) {
        throw out_of_range("Indice invalido");
    }
    //creamos un apuntador auxiliar
    NodeD<T>* aux;
    if (index <= (size - 1) / 2) {
        //recorremos desde head
        aux = head;
        for (int i = 0; i < index; i++) {
            aux = aux->next;
        }
    } else {
        //recorremos desde tail
        aux = tail;
        for (int i = size - 1; i > index; i--) {
            aux = aux->prev;
        }
    }
    //regresamos una referencia al dato
    return aux->data;
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other) {
    //validamos que no sea la misma lista
    if (this != &other) {
        //creamos una copia de la otra lista
        DoublyLinkedList<T> copia(other);
        //limpiamos la lista actual
        clear();
        //recorremos la copia
        NodeD<T>* aux = copia.head;
        while (aux != nullptr) {
            //agregamos cada elemento
            addLast(aux->data);
            aux = aux->next;
        }
    }
    return *this;
}

template <typename T>
void DoublyLinkedList<T>::clear() {
    //creamos un apuntador auxiliar
    NodeD<T>* aux = head;
    //recorremos toda la lista
    while (aux != nullptr) {
        //guardamos el siguiente nodo
        NodeD<T>* siguiente = aux->next;
        //liberamos el nodo actual
        delete aux;
        //avanzamos al siguiente
        aux = siguiente;
    }
    //dejamos la lista vacía
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template <typename T>
void DoublyLinkedList<T>::sort() {
    //utilizamos bubble sort
    if (size < 2) {
        return;
    }
    //recorremos la lista comparando elementos
    for (int i = 0; i < size - 1; i++) {
        NodeD<T>* aux = head;
        for (int j = 0; j < size - i - 1; j++) {
            //intercambiamos los datos si están desordenados
            if (aux->data > aux->next->data) {
                T temp = aux->data;
                aux->data = aux->next->data;
                aux->next->data = temp;
            }
            aux = aux->next;
        }
    }
}

template <typename T>
void DoublyLinkedList<T>::duplicate() {
    //creamos un apuntador auxiliar
    NodeD<T>* aux = head;
    //recorremos la lista original
    while (aux != nullptr) {
        //creamos un nodo con el mismo dato
        NodeD<T>* nuevo = new NodeD<T>(aux->data);
        //apuntamos el nuevo nodo después de aux
        nuevo->next = aux->next;
        nuevo->prev = aux;
        //actualizamos el siguiente nodo
        if (aux->next != nullptr) {
            aux->next->prev = nuevo;
        } else {
            tail = nuevo;
        }
        //conectamos aux con el nuevo nodo
        aux->next = nuevo;
        //incrementamos size
        size++;
        //avanzamos al siguiente elemento original
        aux = nuevo->next;
    }
}

template <typename T>
void DoublyLinkedList<T>::removeDuplicates() {
    //primero ordenamos la lista
    sort();
    //creamos un apuntador auxiliar
    NodeD<T>* aux = head;
    //recorremos la lista
    while (aux != nullptr && aux->next != nullptr) {
        //validamos si los datos son iguales
        if (aux->data == aux->next->data) {
            //guardamos el nodo duplicado
            NodeD<T>* repetido = aux->next;
            //actualizamos el next de aux
            aux->next = repetido->next;
            //actualizamos el prev del siguiente nodo
            if (repetido->next != nullptr) {
                repetido->next->prev = aux;
            } else {
                tail = aux;
            }
            //liberamos el nodo repetido
            delete repetido;
            //decrementamos size
            size--;
        } else {
            //avanzamos al siguiente nodo
            aux = aux->next;
        }
    }
}

template <typename T>
void DoublyLinkedList<T>::print() {
    //creamos un apuntador auxiliar
    NodeD<T>* aux = head;
    //recorremos la lista
    while (aux != nullptr) {
        cout << aux->data;
        if (aux->next != nullptr) {
            cout << " <-> ";
        }
        aux = aux->next;
    }
    cout << endl;
}

template <typename T>
int DoublyLinkedList<T>::getSize() {
    return size;
}

#endif
