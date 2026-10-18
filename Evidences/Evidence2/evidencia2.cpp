//Isis Krystal Agramón Leal
//A00843802

//Isis Krystal Agramón Leal
//A00843802

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Queue.h"
#include "DoublyLinkedList.h"
#include "Stack.h"
#include "Log.h"

using namespace std;

int main() {
    //creamos nuestras estructuras
    Queue<Log> queue;
    DoublyLinkedList<Log> logs;
    //archivos que vamos a leer
    string archivos[2] = {
    "log607-1.txt",
    "log607-2.txt"
    };
    //recorremos los dos archivos
    for (int i = 0; i < 2; i++) {
        ifstream archivo(archivos[i]);
        //validamos que el archivo se abra
        if (!archivo.is_open()) {
            cout << "Error al abrir el archivo: " << archivos[i] << endl;
            return 1;
        }
        string linea;

        //leemos cada linea
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string mes, hora, ip, message;
            int dia, anio;

            //separamos los datos
            if (!(ss >> mes >> dia >> anio >> hora >> ip)) {
                continue;
            }
            //leemos el mensaje completo
            getline(ss, message);
            //quitamos el espacio inicial del mensaje
            if (!message.empty() && message[0] == ' ') {
                message.erase(0, 1);
            }
            //creamos un registro
            Log registro(anio, mes, dia, hora, ip, message);
            //agregamos el registro a la cola
            queue.enqueue(registro);
        }

        archivo.close();
    }

    //mostramos cuantos registros se leyeron
    cout << "Registros leidos: " << queue.getSize() << endl;
    //pasamos los registros a la lista doblemente enlazada
    while (queue.getSize() != 0) {
        Log registro = queue.dequeue();
        logs.addLast(registro);
    }

    //mostramos el total de registros
    cout << "Registros en la lista: " << logs.getSize() << endl;

    return 0;
}