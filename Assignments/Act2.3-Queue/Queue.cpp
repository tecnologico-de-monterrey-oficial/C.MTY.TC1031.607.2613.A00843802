//Isis Krystal Agramón Leal
//A00843802

#include <iostream>
#include <string>
#include "Queue.h"

using namespace std;

struct Cliente {
    string nombre;
    int boletos;
};

int main() {

    Queue<Cliente> fila;
    int opcion;

    do {
        cout << "\nMENU" << endl;
        cout << "1.Llegada de un nuevo cliente" << endl;
        cout << "2.Atender al siguiente cliente" << endl;
        cout << "3.Ver al siguiente cliente" << endl;
        cout << "4.Mostrar cuantas personas hay en la fila" << endl;
        cout << "5.Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            Cliente cliente;
            cout << "Nombre del cliente: ";
            cin >> cliente.nombre;
            cout << "Cantidad de boletos: ";
            cin >> cliente.boletos;
            fila.push(cliente);
            cout << "Cliente agregado a la fila" << endl;
        }
        else if (opcion == 2) {
            try {
                Cliente cliente = fila.pop();
                cout << "Cliente atendido: " << cliente.nombre << endl;
                cout << "Boletos solicitados: " << cliente.boletos << endl;
            }
            catch (out_of_range&) {
                cout << "No hay elementos en la fila" << endl;
            }
        }
        else if (opcion == 3) {
            try {
                Cliente cliente = fila.front();
                cout << "Siguiente cliente: " << cliente.nombre << endl;
                cout << "Boletos solicitados: " << cliente.boletos << endl;
            }
            catch (out_of_range&) {
                cout << "No hay elementos en la fila" << endl;
            }
        }
        else if (opcion == 4) {
            cout << "Personas en la fila: " << fila.getSize() << endl;
        }
        else if (opcion == 5) {
            cout << "Programa terminado" << endl;
        }
            else {
            cout << "Opcion no valida" << endl;
        }

    } while (opcion != 5);

    return 0;
}