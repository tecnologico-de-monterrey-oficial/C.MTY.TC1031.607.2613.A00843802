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
    NodeD<T>* mergeSort(NodeD<T>* inicio);
    NodeD<T>* merge(NodeD<T>* izquierda, NodeD<T>* derecha);

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    DoublyLinkedList(const DoublyLinkedList<T>& other);
    ~DoublyLinkedList();
    void addFirst(T data);
    void addLast(T data);
    void insertAfter(NodeD<T>* node, T data);
    bool deleteAt(int index);
    int findData(T data);
    bool deleteData(T data);
    T getData(int index);
    void updateData(T data, T newData);
    void updateAt(int index, T data);
    T& operator[](int index);
    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& other);
    void clear();
    void print();
    int getSize();
    void printReverse();
    bool deleteNode(NodeD<T>* node);
    void mergeSort();
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
void DoublyLinkedList<T>::insertAfter(NodeD<T>* node, T data) {
    //validamos que el nodo exista
    if (node == nullptr) {
        throw out_of_range("Nodo invalido");
    }
    //creamos un nuevo nodo
    NodeD<T>* auxNew = new NodeD<T>(data);
    //conectamos el nuevo nodo
    auxNew->prev = node;
    auxNew->next = node->next;
    //actualizamos el prev del siguiente nodo
    if (node->next != nullptr) {
        node->next->prev = auxNew;
    } else {
        //actualizamos tail si insertamos al final
        tail = auxNew;
    }
    //conectamos el nodo anterior con el nuevo
    node->next = auxNew;
    //incrementamos size
    size++;
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
void DoublyLinkedList<T>::printReverse() {
    //creamos un apuntador auxiliar
    NodeD<T>* aux = tail;
    //recorremos la lista
    while (aux != nullptr) {
        cout << aux->data;
        if (aux->prev != nullptr) {
            cout << " <-> ";
        }
        aux = aux->prev;
    }
    cout << endl;
}

template <typename T>
int DoublyLinkedList<T>::getSize() {
    return size;
}

template <typename T>
bool DoublyLinkedList<T>::deleteNode(NodeD<T>* node) {
    //validamos que el nodo exista
    if (node == nullptr) {
        return false;
    }

    //validamos si solo hay un elemento
    if (head == tail) {
        head = nullptr;
        tail = nullptr;
        delete node;
        size--;
        return true;
    }

    //validamos si queremos borrar el primero
    if (node == head) {
        head = head->next;
        head->prev = nullptr;
        delete node;
        size--;
        return true;
    }

    //validamos si queremos borrar el último
    if (node == tail) {
        tail = tail->prev;
        tail->next = nullptr;
        delete node;
        size--;
        return true;
    }

    //borramos un elemento de en medio
    node->prev->next = node->next;
    node->next->prev = node->prev;
    //liberamos el nodo
    delete node;
    //decrementamos size
    size--;
    return true;
}

template <typename T>
void DoublyLinkedList<T>::mergeSort() {
    //validamos si la lista tiene elementos suficientes
    if (head == nullptr || head->next == nullptr) {
        return;
    }

    //ordenamos la lista
    head = mergeSort(head);

    //actualizamos tail
    tail = head;
    while (tail->next != nullptr) {
        tail = tail->next;
    }
}

template <typename T>
NodeD<T>* DoublyLinkedList<T>::mergeSort(NodeD<T>* inicio) {
    //validamos si llegamos al caso base
    if (inicio == nullptr || inicio->next == nullptr) {
        return inicio;
    }

    //buscamos la mitad de la lista
    NodeD<T>* lento = inicio;
    NodeD<T>* rapido = inicio->next;

    while (rapido != nullptr && rapido->next != nullptr) {
        lento = lento->next;
        rapido = rapido->next->next;
    }

    //dividimos la lista en dos partes
    NodeD<T>* derecha = lento->next;
    lento->next = nullptr;
    derecha->prev = nullptr;

    //ordenamos ambas mitades
    NodeD<T>* izquierda = mergeSort(inicio);
    derecha = mergeSort(derecha);

    //unimos las mitades ordenadas
    return merge(izquierda, derecha);
}

template <typename T>
NodeD<T>* DoublyLinkedList<T>::merge(NodeD<T>* izquierda, NodeD<T>* derecha) {
    //validamos si alguna mitad está vacía
    if (izquierda == nullptr) {
        return derecha;
    }
    if (derecha == nullptr) {
        return izquierda;
    }

    NodeD<T>* resultado = nullptr;

    //comparamos los datos de ambas mitades
    if (derecha->data < izquierda->data) {
        resultado = derecha;
        resultado->next = merge(izquierda, derecha->next);
    } else {
        resultado = izquierda;
        resultado->next = merge(izquierda->next, derecha);
    }

    //actualizamos los apuntadores prev
    if (resultado->next != nullptr) {
        resultado->next->prev = resultado;
    }
    resultado->prev = nullptr;
    return resultado;
}



#endif
