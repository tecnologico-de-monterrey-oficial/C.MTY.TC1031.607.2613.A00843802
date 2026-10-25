//Isis Krystal Agrmaón Leal
//A00843802

#ifndef BST_h
#define BST_h

#include "NodeT.h"
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
    void preOrder(NodeT<T>* node);
    void inOrder(NodeT<T>* node);
    void postOrder(NodeT<T>* node);
    int height(NodeT<T>* node);
    void clear(NodeT<T>* node);

public:
    BST() : root(nullptr) {}
    ~BST();
    void insert(T data);
    void print();
    bool find(T data);
    void remove(T data);
    void visit(int method);
    int height();
    void ancestors(T data);
    int whatLevelAmI(T data);
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
void BST<T>::remove(T data){
    //validamos si el arbol esta vacio
    if(root != nullptr){
        //validamos si el nodo a borrar es root
        if(root->data == data){
            //validamos si no tiene hijos
            if(root->left == nullptr && root->right == nullptr){
                //root no tiene hijos
                //creamos un nodo aux igual a root
                NodeT<T>* aux = root;
                //asignamos nulos a root
                root = nullptr;
                //removemos aux
                delete aux;
                //nos salimos de la funcion
                return;
            }
            //validamos si tiene un hijo
            if(root->left == nullptr || root->right == nullptr){
                //root solo tiene un hijo
                //creamos un apuntador auxiliar igual a root
                NodeT<T>* aux = root;
                //movemos root a hijo
                root = (root->left == nullptr) ? root->right : root->left;
                //removemos aux
                delete aux;
                //nos salimos de la funcion
                return;
            }
            //root tiene dos hijos
            //creamos un apuntador igual a root
            NodeT<T>* aux = root;
            //validamos que el apuntador right de aux->left sea nulo
            if(aux->left->right == nullptr){
                //aux->left es el más grande del lado izquierdo
                //creamos un apuntador que apunte a aux->left
                NodeT<T>* auxRemove = aux->left;
                //actualizamos el valor de aux por el valor de auxRemove
                aux->data = auxRemove->data;
                //actualizamos el valor de aux->left a auxRemove->left
                aux->left = auxRemove->left;
                //removemos auxRemove
                delete auxRemove;
                //salimos de la funcion
                return;
            } else{
                //el mas grande del lado izquierdo no es aux->left
                //creamos un apuntador que va a ser el padre que voy a remover
                NodeT<T>* fatherRemove = aux->left;
                //creamos un apuntador hacia el hijo derecho de fatherRemove
                NodeT<T>* auxRemove = fatherRemove->right;
                //iteramos hasta encontrar el mas grande
                while(auxRemove->right != nullptr){
                    //recorremos los apuntadores hacia la derecha
                    fatherRemove = auxRemove;
                    auxRemove = auxRemove->right;
                }
                //ya encontramos al mas grande del lado izquierdo
                aux->data = auxRemove->data;
                //actualizamos el lado derecho de fatherRemove
                fatherRemove->right = auxRemove->left;
                //removemos auxRemove
                delete auxRemove;
                //nos salimos de la funcion
                return;
            }
        } else {
            //no quiero borrar raíz
            //creamos un apuntador father igual a root
            NodeT<T>* father = root;
            //creamos un apuntador auxiliar para buscar el nodo
            NodeT<T>* aux = (data < root->data) ? root->left : root->right;
            //itero en el árbol hasta encontrar el nodo a borrar
            while(aux != nullptr){
                //valido si aux->data es igual a data
                if(aux->data == data){
                    //validamos si no tiene hijos
                    if(aux->left == nullptr && aux->right == nullptr){
                        //aux no tiene hijos
                        //actualizamos el apuntador de father
                        if(father->left == aux){
                            father->left = nullptr;
                        }else{
                            father->right = nullptr;
                        }
                        //removemos aux
                        delete aux;
                        //nos salimos de la funcion
                        return;
                    }
                    //validamos si tiene un hijo
                    if(aux->left == nullptr || aux->right == nullptr){
                        //aux solo tiene un hijo
                        if(father->left == aux){
                            //el hijo esta a la izquierda del padre
                            father->left = (aux->left != nullptr) ? aux->left : aux->right;
                        }else{
                            //el hijo esta a la derecha del padre
                            father->right = (aux->left != nullptr) ? aux->left : aux->right;
                        }
                        //removemos aux
                        delete aux;
                        //nos salimos de la funcion
                        return;
                    }
                    //aux tiene dos hijos
                    //validamos que el apuntador right de aux->left sea nulo
                    if(aux->left->right == nullptr){
                        //aux->left es el más grande del lado izquierdo
                        NodeT<T>* auxRemove = aux->left;
                        //actualizamos el valor de aux
                        aux->data = auxRemove->data;
                        //actualizamos el lado izquierdo
                        aux->left = auxRemove->left;
                        //removemos auxRemove
                        delete auxRemove;
                        //nos salimos de la funcion
                        return;
                    }else{
                        //el mas grande del lado izquierdo no es aux->left
                        NodeT<T>* fatherRemove = aux->left;
                        NodeT<T>* auxRemove = fatherRemove->right;
                        //iteramos hasta encontrar el mas grande
                        while(auxRemove->right != nullptr){
                            //recorremos los apuntadores hacia la derecha
                            fatherRemove = auxRemove;
                            auxRemove = auxRemove->right;
                        }
                        //ya encontramos al mas grande del lado izquierdo
                        aux->data = auxRemove->data;
                        //actualizamos el lado derecho de fatherRemove
                        fatherRemove->right = auxRemove->left;
                        //removemos auxRemove
                        delete auxRemove;
                        //nos salimos de la funcion
                        return;
                    }
                }else{
                    //recorremos aux y father
                    father = aux;
                    if(data < aux->data){
                        aux = aux->left;
                    }else{
                        aux = aux->right;
                    }
                }
            }
            //no se encontró el dato a buscar, arrojamos una excepcion
            throw out_of_range("El nodo a borrar no existe");
        }
    }else{
        //el árbol está vacío
        throw out_of_range("El arbol esta vacio");
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
void BST<T>::preOrder(NodeT<T>* node){
    if(node != nullptr){
        //imprimir data
        cout << node->data << " ";
        //hacemos preOrder con left
        preOrder(node->left);
        //hacemos preOrder con right
        preOrder(node->right);
    }
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
void BST<T>::postOrder(NodeT<T>* node){
    if(node != nullptr){
        //hacemos postOrder con left
        postOrder(node->left);
        //hacemos postOrder con right
        postOrder(node->right);
        //imprimir data
        cout << node->data << " ";
    }
}

template<typename T>
void BST<T>::visit(int method){
    //validamos el metodo que se quiere utilizar
    if(method == 1){
        //recorrido preOrder
        preOrder(root);
    }else if(method == 2){
        //recorrido inOrder
        inOrder(root);
    }else if(method == 3){
        //recorrido postOrder
        postOrder(root);
    }else if(method == 4){
        //recorrido por niveles
        if(root != nullptr){
            queue<NodeT<T>*> nodes;
            nodes.push(root);
            while(!nodes.empty()){
                NodeT<T>* aux = nodes.front();
                nodes.pop();
                //imprimimos data
                cout << aux->data << " ";
                //agregamos los hijos a la cola
                if(aux->left != nullptr){
                    nodes.push(aux->left);
                }
                if(aux->right != nullptr){
                    nodes.push(aux->right);
                }
            }
        }
    }else{
        cout << "Metodo no valido";
    }
    cout << endl;
}

template<typename T>
int BST<T>::height(NodeT<T>* node){
    //validamos si el nodo esta vacio
    if(node == nullptr){
        return 0;
    }
    //calculamos la altura del lado izquierdo
    int leftHeight = height(node->left);
    //calculamos la altura del lado derecho
    int rightHeight = height(node->right);
    //regresamos la altura mayor
    if(leftHeight > rightHeight){
        return leftHeight + 1;
    }else{
        return rightHeight + 1;
    }
}

template<typename T>
int BST<T>::height(){
    //regresamos la altura del arbol
    return height(root);
}

template<typename T>
void BST<T>::ancestors(T data){
    //validamos si el dato existe
    if(!find(data)){
        cout << "El dato no existe" << endl;
        return;
    }
    //creamos un apuntador auxiliar igual a root
    NodeT<T>* aux = root;
    //iteramos hasta encontrar el dato
    while(aux != nullptr && aux->data != data){
        //imprimimos el ancestro
        cout << aux->data << " ";
        //recorremos aux
        if(data < aux->data){
            aux = aux->left;
        }else{
            aux = aux->right;
        }
    }
    cout << endl;
}

template<typename T>
int BST<T>::whatLevelAmI(T data){
    //creamos un apuntador auxiliar igual a root
    NodeT<T>* aux = root;
    //iniciamos el nivel en cero
    int level = 0;
    //iteramos hasta encontrar el dato
    while(aux != nullptr){
        //validamos si encontramos el dato
        if(aux->data == data){
            return level;
        }
        //recorremos aux
        if(data < aux->data){
            aux = aux->left;
        }else{
            aux = aux->right;
        }
        //aumentamos el nivel
        level++;
    }
    //no se encontro el dato
    return -1;
}

#endif // BST_H
