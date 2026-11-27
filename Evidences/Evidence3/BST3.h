
//Isis Krystal Agramón Leal
//A00843802

#ifndef BST_h
#define BST_h

#include "NodeT3.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <queue>
#include <vector> //NUEVO
#include <utility> //NUEVO

using namespace std;

template <typename T>
class BST {
private:
    NodeT<T>* root;
    void printTree(NodeT<T>* node, string prefix, bool isRight, bool isRoot);
    void inOrder(NodeT<T>* node);
    void clear(NodeT<T>* node);

    //NUEVO
    int size(NodeT<T>* node);
    int height(NodeT<T>* node);
    void inOrder(NodeT<T>* node, vector<pair<T, int>>& list);

public:
    BST() : root(nullptr) {}
    ~BST();
    void insert(T data);
    void print();
    bool find(T data);
    int getCount(T data);

    //NUEVO
    int size();
    int height();
    pair<int, int> search(T data);
    vector<pair<T, int>> inOrder();
};

template<typename T>
BST<T>::~BST(){
    clear(root);
}

template<typename T>
void BST<T>::clear(NodeT<T>* node){
    if(node != nullptr){
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

template<typename T>
void BST<T>::insert(T data){
    //validamos si el árbol está vacío
    if (root == nullptr){
        //el árbol está vacío
        //apuntamos root al nuevo nodo
        root = new NodeT<T>(data);
    } else {
        //el árbol no está vacío
        //creamos un apuntador auxiliar igual a root
        NodeT<T>* aux = root;

        //creamos un apuntador father igual a root
        NodeT<T>* father = root;

        //itero en el árbol hasta encontrar donde voy a insertar el nodo
        while(aux != nullptr){
            //valido si aux->data es igual a data
            if (aux->data == data){
                //son iguales
                aux->count++;
                return;
            } else {
                //hacemos father igual a aux
                father = aux;

                //recorremos aux
                if(data < aux->data){
                    aux = aux->left;
                } else {
                    aux = aux->right;
                }
            }
        }

        //inserto el nodo en el lado correspondiente
        if(data < father->data){
            //el nodo va al lado izquierdo de father
            father->left = new NodeT<T>(data);
        } else {
            //el nodo va al lado derecho de father
            father->right = new NodeT<T>(data);
        }
    }
}

template<typename T>
bool BST<T>::find(T data){
    //validamos si el árbol está vacío
    if (root == nullptr){
        //el árbol está vacío
        return false;
    } else {
        //el árbol no está vacío
        //creamos un apuntador auxiliar igual a root
        NodeT<T>* aux = root;

        //itero en el árbol hasta encontrar el nodo a buscar o que no lo encuentre
        while(aux != nullptr){
            //valido si aux->data es igual a data
            if (aux->data == data){
                //son iguales, regreso true
                return true;
            } else {
                //recorremos aux
                if(data < aux->data){
                    aux = aux->left;
                } else {
                    aux = aux->right;
                }
            }
        }

        //no se encontró el dato a buscar
        return false;
    }
}

template <typename T>
void BST<T>::printTree(NodeT<T>* node, string prefix, bool isRight, bool isRoot) {
    if (node == nullptr) return;

    printTree(node->right, prefix + (isRoot ? "" : (isRight ? "      " : "|     ")), true, false);

    cout << prefix << (isRoot ? "" : (isRight ? ".---- " : "`---- ")) << node->data << endl;

    printTree(node->left, prefix + (isRoot ? "" : (isRight ? "|     " : "      ")), false, false);
}

template <typename T>
void BST<T>::print() {
    if (root == nullptr) {
        cout << "(arbol vacio)" << endl;
        return;
    }

    printTree(root, "", false, true);
}

template<typename T>
void BST<T>::inOrder(NodeT<T>* node){
    if(node != nullptr){
        //hacemos inOrder con left
        inOrder(node->left);

        //imprimir data
        cout << node->data << " ";

        //hacemos inOrder con right
        inOrder(node->right);
    }
}

template<typename T>
int BST<T>::getCount(T data){
    NodeT<T>* aux = root;

    while(aux != nullptr){
        if(aux->data == data){
            return aux->count;
        }

        if(data < aux->data){
            aux = aux->left;
        } else {
            aux = aux->right;
        }
    }

    return 0;
}

//NUEVO
//cuenta la cantidad de nodos distintos
template<typename T>
int BST<T>::size(NodeT<T>* node){
    if(node == nullptr){
        return 0;
    }

    return 1 + size(node->left) + size(node->right);
}

//NUEVO
//regresa la cantidad de nodos
template<typename T>
int BST<T>::size(){
    return size(root);
}

//NUEVO
//calcula la altura del árbol
template<typename T>
int BST<T>::height(NodeT<T>* node){
    if(node == nullptr){
        return -1;
    }

    //obtenemos la altura de ambos lados
    int left = height(node->left);
    int right = height(node->right);

    //regresamos la altura mayor
    if(left > right){
        return left + 1;
    } else {
        return right + 1;
    }
}

//NUEVO
//regresa la altura del árbol
template<typename T>
int BST<T>::height(){
    return height(root);
}

//NUEVO
//busca un dato y cuenta las comparaciones
template<typename T>
pair<int, int> BST<T>::search(T data){
    NodeT<T>* aux = root;
    int comparisons = 0;

    while(aux != nullptr){
        //comparamos si los datos son iguales
        comparisons++;

        if(aux->data == data){
            return make_pair(aux->count, comparisons);
        }

        //comparamos si el dato es menor
        comparisons++;

        if(data < aux->data){
            aux = aux->left;
        } else {
            aux = aux->right;
        }
    }

    //no se encontró el dato
    return make_pair(0, comparisons);
}

//NUEVO
//recorre el árbol y guarda los datos con sus contadores
template<typename T>
void BST<T>::inOrder(NodeT<T>* node, vector<pair<T, int>>& list){
    if(node != nullptr){
        //recorremos el lado izquierdo
        inOrder(node->left, list);

        //guardamos el dato y su contador
        list.push_back(make_pair(node->data, node->count));

        //recorremos el lado derecho
        inOrder(node->right, list);
    }
}

//NUEVO
//regresa los datos ordenados con sus contadores
template<typename T>
vector<pair<T, int>> BST<T>::inOrder(){
    vector<pair<T, int>> list;

    inOrder(root, list);

    return list;
}

#endif // BST_H