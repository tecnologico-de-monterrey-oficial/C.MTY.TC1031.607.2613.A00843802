//Isis Krystal Agramón Leal
//A00843802

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "Queue.h"
#include "DoublyLinkedList.h"
#include "Stack.h"
#include "Log.h"

using namespace std;

void buscarPorDia(DoublyLinkedList<Log>& logs, int anio, string mes, int dia) {
    //variable para saber si encontramos registros
    bool encontrado = false;
    int cantidad = 0;

    //recorremos los registros
    for (int i = 0; i < logs.getSize(); i++) {
        Log registro = logs.getData(i);
        //comparamos la fecha
        if (registro.year == anio && registro.month == mes && registro.day == dia) {
            //mostramos el registro encontrado
            cout << registro.month << " " << registro.day << " " << registro.year << " " << registro.time << " " << registro.ip << " " << registro.message << endl;
            encontrado = true;
            cantidad++;
        }
    }
    //mostramos los resultados
    if (!encontrado) {
        cout << "No se encontraron registros en esa fecha." << endl;
    } else {
        cout << "Total de registros encontrados: " << cantidad << endl;
    }
}

void mostrarInverso(DoublyLinkedList<Log>& logs) {
    //creamos un stack para guardar los registros
    Stack<Log> stack;
    //agregamos los registros al stack
    for (int i = 0; i < logs.getSize(); i++) {
        stack.push(logs.getData(i));
    }
    //mostramos los registros en orden inverso
    while (!stack.isEmpty()) {
        Log registro = stack.pop();
        cout << registro.month << " " << registro.day << " " << registro.year << " " << registro.time << " " << registro.ip << " " << registro.message << endl;
    }
}

void mostrarEstadisticas(DoublyLinkedList<Log>& logs) {
    //creamos mapas para contar los registros
    map<string, int> dias;
    map<string, int> eventos;
    map<string, int> ips;

    //recorremos todos los registros
    for (int i = 0; i < logs.getSize(); i++) {
        Log registro = logs.getData(i);

        //guardamos la fecha completa
        string fecha = registro.month + " " +
                       to_string(registro.day) + " " +
                       to_string(registro.year);

        //contamos las apariciones
        dias[fecha]++;
        eventos[registro.message]++;
        ips[registro.ip]++;
    }

    //buscamos las cantidades mayores
    int mayorDia = 0;
    int mayorEvento = 0;
    int mayorIP = 0;

    for (auto dato : dias) {
        if (dato.second > mayorDia) {
            mayorDia = dato.second;
        }
    }

    for (auto dato : eventos) {
        if (dato.second > mayorEvento) {
            mayorEvento = dato.second;
        }
    }

    for (auto dato : ips) {
        if (dato.second > mayorIP) {
            mayorIP = dato.second;
        }
    }

    //mostramos las estadisticas
    cout << "\nEstadisticas del archivo:" << endl;
    cout << "Total de registros: " << logs.getSize() << endl;

    //mostramos el dia con mas incidentes
    cout << "\nDia con mas incidentes:" << endl;

    if (mayorDia == 0) {
        cout << "No hay registros." << endl;
    } else {
        for (auto dato : dias) {
            if (dato.second == mayorDia) {
                cout << dato.first << ": "
                     << dato.second << " incidentes" << endl;
            }
        }
    }

    //mostramos el evento mas frecuente
    cout << "\nTipo de evento mas frecuente:" << endl;

    if (mayorEvento == 0) {
        cout << "No hay registros." << endl;
    } else {
        for (auto dato : eventos) {
            if (dato.second == mayorEvento) {
                cout << dato.first << ": "
                     << dato.second << " apariciones" << endl;
            }
        }
    }

    //mostramos la ip mas frecuente
    cout << "\nDireccion IP mas frecuente:" << endl;

    if (mayorIP == 0) {
        cout << "No hay registros." << endl;
    } else {
        for (auto dato : ips) {
            if (dato.second == mayorIP) {
                cout << dato.first << ": "
                     << dato.second << " apariciones" << endl;
            }
        }
    }
}

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

    logs.mergeSort();

    cout << "Registros ordenados: " << logs.getSize() << endl;
    cout << "Primer registro: " << logs.getData(0).key << endl;
    cout << "Ultimo registro: " << logs.getData(logs.getSize() - 1).key << endl;

    int anio, dia;
    string mes;
    cout << "\nBusqueda por dia" << endl;
    cout << "Ingresa el anio: ";
    cin >> anio;
    cout << "Ingresa el mes (Jan, Feb, Mar...): ";
    cin >> mes;
    cout << "Ingresa el dia: ";
    cin >> dia;
    //buscamos los registros de esa fecha
    buscarPorDia(logs, anio, mes, dia);
    //mostramos los registros en orden inverso
    //cout << "\nRegistros en orden inverso:" << endl;
    //mostrarInverso(logs);

    //mostramos las estadisticas
    mostrarEstadisticas(logs);

return 0;
}