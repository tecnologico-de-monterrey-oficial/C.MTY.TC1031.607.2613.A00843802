//Isis Krystal Agramón Leal
//A00843802

#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "DoublyLinkedList.h"

using namespace std;

int main() {
    DoublyLinkedList<int> lista;
    DoublyLinkedList<int> lista2;
    int opcion, tipo, cantidad, dato, nuevo, index;

    cout << "Creación de la lista" << endl;
    cout << "1.Capturar datos" << endl;
    cout << "2.Generar datos aleatorios" << endl;
    cout << "Opcion: ";
    cin >> tipo;

    cout << "Cantidad de elementos: ";
    cin >> cantidad;

    if (tipo == 1) {
        for (int i = 0; i < cantidad; i++) {
            cout << "Dato " << i + 1 << ": ";
            cin >> dato;
            lista.addLast(dato);
        }
    } else if (tipo == 2) {
        for (int i = 0; i < cantidad; i++) {
            dato = rand() % 100 + 1;
            lista.addLast(dato);
        }
    } else {
        cout << "Opcion invalida" << endl;
    }

    do {
        cout << "\n-----------Menú-------------" << endl;
        cout << "1. Agregar al inicio" << endl;
        cout << "2. Agregar al final" << endl;
        cout << "3. Insertar despues de un indice" << endl;
        cout << "4. Borrar por dato" << endl;
        cout << "5. Borrar por posicion" << endl;
        cout << "6. Obtener dato por posicion" << endl;
        cout << "7. Actualizar por dato" << endl;
        cout << "8. Actualizar por posicion" << endl;
        cout << "9. Buscar dato" << endl;
        cout << "10. Obtener dato con []" << endl;
        cout << "11. Actualizar dato con []" << endl;
        cout << "12. Copiar lista con =" << endl;
        cout << "13. Limpiar lista" << endl;
        cout << "14. Ordenar lista" << endl;
        cout << "15. Duplicar elementos" << endl;
        cout << "16. Eliminar duplicados" << endl;
        cout << "17. Mostrar lista" << endl;
        cout << "18. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        try {
            if (opcion == 1) {
                cout << "Dato: ";
                cin >> dato;
                lista.addFirst(dato);
            }
            else if (opcion == 2) {
                cout << "Dato: ";
                cin >> dato;
                lista.addLast(dato);
            }
            else if (opcion == 3) {
                cout << "Indice: ";
                cin >> index;
                cout << "Dato: ";
                cin >> dato;
                lista.insert(index, dato);
            }
            else if (opcion == 4) {
                cout << "Dato a borrar: ";
                cin >> dato;
                if (lista.deleteData(dato)) {
                    cout << "Dato eliminado" << endl;
                } else {
                    cout << "Dato no encontrado" << endl;
                }
            }
            else if (opcion == 5) {
                cout << "Indice a borrar: ";
                cin >> index;
                if (lista.deleteAt(index)) {
                    cout << "Dato eliminado" << endl;
                } else {
                    cout << "Indice invalido" << endl;
                }
            }
            else if (opcion == 6) {
                cout << "Indice: ";
                cin >> index;
                cout << "Dato: " << lista.getData(index) << endl;
            }
            else if (opcion == 7) {
                cout << "Dato a actualizar: ";
                cin >> dato;
                cout << "Nuevo dato: ";
                cin >> nuevo;
                lista.updateData(dato, nuevo);
                cout << "Dato actualizado" << endl;
            }
            else if (opcion == 8) {
                cout << "Indice: ";
                cin >> index;
                cout << "Nuevo dato: ";
                cin >> nuevo;
                lista.updateAt(index, nuevo);
                cout << "Dato actualizado" << endl;
            }
            else if (opcion == 9) {
                cout << "Dato a buscar: ";
                cin >> dato;
                index = lista.findData(dato);
                if (index == -1) {
                    cout << "Dato no encontrado" << endl;
                } else {
                    cout << "Se encuentra en el indice: " << index << endl;
                }
            }
            else if (opcion == 10) {
                cout << "Indice: ";
                cin >> index;
                cout << "Dato: " << lista[index] << endl;
            }
            else if (opcion == 11) {
                cout << "Indice: ";
                cin >> index;
                cout << "Nuevo dato: ";
                cin >> nuevo;
                lista[index] = nuevo;
                cout << "Dato actualizado" << endl;
            }
            else if (opcion == 12) {
                lista2 = lista;
                cout << "Lista copiada: ";
                lista2.print();
            }
            else if (opcion == 13) {
                lista.clear();
                cout << "Lista vaciada" << endl;
            }
            else if (opcion == 14) {
                lista.sort();
                cout << "Lista ordenada" << endl;
            }
            else if (opcion == 15) {
                lista.duplicate();
                cout << "Elementos duplicados" << endl;
            }
            else if (opcion == 16) {
                lista.removeDuplicates();
                cout << "Duplicados eliminados" << endl;
            }
            else if (opcion == 17) {
                cout << "Lista: ";
                lista.print();
            }
            else if (opcion == 18) {
                cout << "Programa terminado" << endl;
            }
            else {
                cout << "Opcion invalida" << endl;
            }

            if (opcion >= 1 && opcion <= 16) {
                cout << "Lista actual: ";
                lista.print();
            }
        }
        catch (const out_of_range& e) {
            cout << "Error: " << e.what() << endl;
        }

    } while (opcion != 18);

    return 0;
}
