//Isis Krystal Agrmaón Leal
//A00843802

#ifndef BST_h
#define BST_h

#include "NodeT3.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <queue>
using namespace std;

template <typename T>
class BST {
private:
    NodeT<T>* root;
    void printTree(NodeT<T>* node, string prefix, bool isRight, bool isRoot);
    void inOrder(NodeT<T>* node);
    void clear(NodeT<T>* node);

public:
    BST() : root(nullptr) {}
    ~BST();
    void insert(T data);
    void print();
    bool find(T data);
    int getCount(T data);
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
            }else {
                //hacemos father igual a aux
                father = aux;
                //recorremos aux
                //if (data < aux->data ? aux = aux->left : aux = aux->right)
                if(data < aux->data){
                    aux = aux->left;
                }else {
                    aux = aux->right;
                }
            }
        }
        //inserto el nodo en el lado correspondiente
        if(data < father->data){
            //el nodo va al lado izquierdo de father
            father->left = new NodeT<T>(data);
        }else {
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
            }else {
                //recorremos aux
                //if (data < aux->data ? aux = aux->left : aux = aux->right)
                if(data < aux->data){
                    aux = aux->left;
                }else {
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
        if(aux->data== data){
            return aux->count;
        }
        if(data < aux->data){
            aux = aux->left;
        } else{
            aux = aux->right;
        }
    }
    return 0;
}

#endif // BST_H
