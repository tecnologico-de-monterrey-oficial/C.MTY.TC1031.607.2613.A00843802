//Isis Krystal Agramón Leal
//A00843802


#include <iostream>
#include <stdexcept>
#include "BST.h"
using namespace std;

int main(){
    BST<int> tree;
    int opcion, dato, metodo;

    do{
        cout << "\n----- Menu BST -----" << endl;
        cout << "1.Insertar un dato" << endl;
        cout << "2.Mostrar recorridos" << endl;
        cout << "3.Buscar un dato" << endl;
        cout << "4.Mostrar altura del arbol" << endl;
        cout << "5.Mostrar ancestros" << endl;
        cout << "6.Consultar nivel de un nodo" << endl;
        cout << "7.Eliminar un dato" << endl;
        cout << "8.Imprimir arbol" << endl;
        cout << "9.Salir" << endl;
        cout << "Selecciona una opcion: ";
        cin >> opcion;

        switch(opcion){
            case 1:
                cout << "Ingresa el dato: ";
                cin >> dato;
                tree.insert(dato);
                cout << "Dato insertado" << endl;
                break;

            case 2:
                cout << "\n--- Recorridos ---" << endl;
                cout << "1.PreOrder" << endl;
                cout << "2.InOrder" << endl;
                cout << "3.PostOrder" << endl;
                cout << "4.Level by level" << endl;
                cout << "Selecciona un recorrido: ";
                cin >> metodo;
                tree.visit(metodo);
                break;

            case 3:
                cout << "Ingresa el dato a buscar: ";
                cin >> dato;
                if(tree.find(dato)){
                    cout << "El dato existe" << endl;
                }else{
                    cout << "El dato no existe" << endl;
                }
                break;

            case 4:
                cout << "Altura del arbol: " << tree.height() << endl;
                break;

            case 5:
                cout << "Ingresa el dato: ";
                cin >> dato;
                cout << "Ancestros: ";
                tree.ancestors(dato);
                break;

            case 6:
                cout << "Ingresa el dato: ";
                cin >> dato;
                if(tree.whatLevelAmI(dato) == -1){
                    cout << "El dato no existe" << endl;
                }else{
                    cout << "Nivel: " << tree.whatLevelAmI(dato) << endl;
                }
                break;

            case 7:
                cout << "Ingresa el dato a eliminar: ";
                cin >> dato;
                try{
                    tree.remove(dato);
                    cout << "Dato eliminado" << endl;
                }catch(out_of_range &e){
                    cout << e.what() << endl;
                }
                break;

            case 8:
                cout << "\n--- Arbol BST ---" << endl;
                tree.print();
                break;

            case 9:
                cout << "Saliendo del programa..." << endl;
                break;

            default:
                cout << "Opcion no valida" << endl;
        }

    }while(opcion != 9);

    return 0;
}
