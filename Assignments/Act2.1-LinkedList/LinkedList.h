//Isis Krystal Agramón Leal
//A00843802

#ifndef LinkedList_h
#define LinkedList_h

#include "Node.h"

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    int size;
public:
    LinkedList() : head(nullptr), size(0) {}
    void addFirst(T data);
    void addLast(T data);
    void insert(int index, T data);
    bool deleteData(T data);
    bool deleteAt(int index);
    T getData(int index);
    void updateData(T data, T newData);
    void updateAt(int index, T newData);
    int findData(T data);
    T& operator[](int index);
    LinkedList<T>& operator=(const LinkedList<T>& list);
    void print();
};

template <typename T>
void LinkedList<T>::addFirst(T data) {
    // crear un nodo nuevo
    Node<T>* node = new Node<T>(data);
    // actualizo el next del nodo nuevo para que apunte a head
    node->next = head;
    // actualizo head
    head = node;
    size++;
}

template <typename T>
void LinkedList<T>::addLast(T data) {
    // validamos si la lista vacía
    if (head != nullptr) {
        // la lista no esta vacía
        // creamos un apuntador auxiliar que apunte a head
        Node<T>* aux = head;
        // recorremos la lista mientras aux->next sea diferente de nullptr
        while (aux->next != nullptr) {
            // recorremos aux a aux->next
            aux = aux->next;
        }
        // agregamos el nodo nuevo después de aux
        aux->next = new Node<T>(data);
    } else {
        // la lista esta vacía
        head = new Node<T>(data);    
    }
    // incrementamos size
    size++;
}

template <typename T>
void LinkedList<T>::insert(int index, T data) {
    // validamos que la posición exista
    if (index >= 0 && index < size) {
        // creamos un índice auxiliar
        int auxIndex = 0;
        // creamos nodo auxiliar
        Node<T>* aux = head;
        // recorremos la lista hasta encontrar la posición donde vamos a hacer el insert
        while (auxIndex < index) {
            // recorremos aux
            aux = aux->next;
            // incrementamos el indice auxiliar
            auxIndex++;
        }
        // insertamos el nuevo nodo
        aux->next = new Node<T>(data, aux->next);
        // incrementamos size
        size++;
    } else {
        // error
        throw out_of_range("la posición no existe en la lista");
    }

}
/*
template <typename T>
void LinkedList<T>::deleteData(T data) {
    // validamos que la lista no este vacía
    if (head != nullptr) {
        // la lista no esta vacía
        // valido si el primer elemento es el que quiero borrar
        if (head->data == data) {
            // quiero borrar el primer elemento
            // creamos un elemento aux igual a head
            Node<T>* aux = head;
            // recorremos head a head->next
            head = head->next;
            // borramos el primer elemento
            delete aux;
            // decrementamos size
            size--;
        } else {
            // creamos un elemento auxPrev igual a head
            Node<T>* auxPrev = head;
            // creamos un elemento aux igual a head->next
            Node<T>* aux = head->next;
            // recorremos la lista
            while (aux != nullptr) {
                // validamos si el valor de aux es el que quiero borrar
                if (aux->data == data) {
                    // 
                    auxPrev->next = aux->next;
                    // borro aux
                    delete aux;
                    // decrmenatmos size
                    size--;
                    // return
                }
                // recorremos los apuntadores
                auxPrev = aux;
                aux = aux->next;
            }
            // no lo encontre
            throw out_of_range("no se encontró el dato a borrar")
        }
    } else {
        throw out_of_range("La lista esta vacía")
    }
}
*/

template <typename T>
bool LinkedList<T>::deleteData(T data) {
    //validamos que la lista no este vacia
    if (head == nullptr) {
        return false;
    }

    //si el dato esta en el primer nodo
    if (head->data == data) {
        Node<T>* aux = head;
        head = head->next;
        delete aux;
        size--;
        return true;
    }

    //buscamos el dato en el resto de la lista
    Node<T>* auxPrev = head;
    Node<T>* aux = head->next;

    while (aux != nullptr) {
        if (aux->data == data) {
            auxPrev->next = aux->next;
            delete aux;
            size--;
            return true;
        }

        auxPrev = aux;
        aux = aux->next;
    }

    //no se encontró el dato
    return false;
}

template <typename T>
bool LinkedList<T>::deleteAt(int index) {
    //validamos que la posición exista
    if (index < 0 || index >= size) {
        return false;
    }

    //si queremos borrar el primer elemento
    if (index == 0) {
        Node<T>* aux = head;
        head = head->next;
        delete aux;
        size--;
        return true;
    }

    //nos movemos al nodo anterior al que queremos borrar
    Node<T>* aux = head;

    for (int i = 0; i < index - 1; i++) {
        aux = aux->next;
    }

    //guardamos el nodo que vamos a borrar
    Node<T>* nodeDelete = aux->next;

    //conectamos con el siguiente nodo
    aux->next = nodeDelete->next;

    //borramos el nodo
    delete nodeDelete;
    size--;

    return true;
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
void LinkedList<T>::updateData(T data, T newData) {
    Node<T>* aux = head;
    //buscamos el dato
    while (aux != nullptr) {
        if (aux->data == data) {
            aux->data = newData;
            return;
        }
        aux = aux->next;
    }
    //si terminamos la lista y no lo encontramos
    throw out_of_range("No se encontró el dato a actualizar");
}

template <typename T>
void LinkedList<T>::updateAt(int index, T newData) {
    //validamos que la posición exista
    if (index < 0 || index >= size) {
        throw out_of_range("La posición no existe en la lista");
    }
    Node<T>* aux = head;
    //recorremos hasta llegar a la posición
    for (int i = 0; i < index; i++) {
        aux = aux->next;
    }
    //actualizamos el dato
    aux->data = newData;
}

template <typename T>
int LinkedList<T>::findData(T data) {
    Node<T>* aux = head;
    int index = 0;

    while (aux != nullptr) {
        if (aux->data == data) {
            return index;
        }

        aux = aux->next;
        index++;
    }

    return -1;
}

template <typename T>
T& LinkedList<T>::operator[](int index) {
    //validamos que la posicion exista
    if (index < 0 || index >= size) {
        throw out_of_range("La posición no existe en la lista");
    }

    Node<T>* aux = head;
    //recorremos hasta llegar a la posición
    for (int i = 0; i < index; i++) {
        aux = aux->next;
    }

    return aux->data;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& list) {
    //evitamos copiar la lista sobre si misma
    if (this == &list) {
        return *this;
    }

    //borramos los nodos que ya tenia la lista actual
    while (head != nullptr) {
        Node<T>* aux = head;
        head = head->next;
        delete aux;
    }
    size = 0;
    //recorremos la lista que queremos copiar
    Node<T>* aux = list.head;
    while (aux != nullptr) {
        addLast(aux->data);
        aux = aux->next;
    }

    return *this;
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