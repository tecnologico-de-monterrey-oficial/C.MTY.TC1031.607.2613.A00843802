//Isis Krystal Agramón Leal
//A00843802

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <chrono>
#include "Queue.h"
#include "DoublyLinkedList.h"
#include "Stack.h"
#include "Log.h"

using namespace std;

void buscarPorDia(DoublyLinkedList<Log>& logs, int anio, string mes, int dia) {
    //variable para contar los registros encontrados
    int cantidad = 0;
    //creamos la fecha que queremos buscar
    Log buscado(anio, mes, dia, "00:00:00", "", "");
    //recorremos los registros ordenados
    for (int i = 0; i < logs.getSize(); i++) {
        Log registro = logs.getData(i);

        //si pasamos de la fecha, dejamos de buscar
        if (registro.key.substr(0, 8) > buscado.key.substr(0, 8)) {
            break;
        }
        //comparamos la fecha
        if (registro.year == anio && registro.month == mes && registro.day == dia) {
            cout << registro.month << " " << registro.day << " "
                 << registro.year << " " << registro.time << " "
                 << registro.ip << " " << registro.message << endl;
            cantidad++;
        }
    }
    if (cantidad == 0) {
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
        string fecha = registro.month + " " + to_string(registro.day) + " " + to_string(registro.year);
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

void guardarArchivo(DoublyLinkedList<Log>& logs) {
    //creamos el archivo de salida
    ofstream salida("output608.out");
    if (!salida.is_open()) {
        cout << "Error al crear el archivo de salida." << endl;
        return;
    }
    //guardamos los registros ordenados
    for (int i = 0; i < logs.getSize(); i++) {
        Log registro = logs.getData(i);
        salida << registro.month << " " << registro.day << " " << registro.year << " " << registro.time << " " << registro.ip << " " << registro.message << endl;
    }
    salida.close();
    cout << "Archivo output608.out generado correctamente." << endl;
}


int main() {
    //creamos nuestras estructuras
    Queue<Log> queue;
    DoublyLinkedList<Log> logs;

    string nombreArchivo;
    int opcionArchivo;
    //preguntamos que archivo desea cargar
    cout << "Selecciona el archivo que deseas cargar:" << endl;
    cout << "1. log607-1.txt" << endl;
    cout << "2. log607-2.txt" << endl;
    cout << "Opcion: ";
    cin >> opcionArchivo;

    if (opcionArchivo == 1) {
        nombreArchivo = "log607-1.txt";
    } else if (opcionArchivo == 2) {
        nombreArchivo = "log607-2.txt";
    } else {
        cout << "Opcion no valida." << endl;
        return 1;
    }

    //abrimos el archivo seleccionado
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo: " << nombreArchivo << endl;
        return 1;
    }

    string linea;
    int omitidas = 0;
    //leemos cada linea
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string mes, hora, ip, message;
        int dia, anio;

        //separamos los datos
        if (!(ss >> mes >> dia >> anio >> hora >> ip)) {
            omitidas++;
            continue;
        }
        //leemos el mensaje completo
        getline(ss, message);
        if (!message.empty() && message[0] == ' ') {
            message.erase(0, 1);
        }
        //creamos un registro
        Log registro(anio, mes, dia, hora, ip, message);
        queue.enqueue(registro);
    }

    archivo.close();
    //pasamos los registros a la lista
    while (!queue.isEmpty()) {
        Log registro = queue.dequeue();
        logs.addLast(registro);
    }

    cout << "\nArchivo cargado: " << nombreArchivo << endl;
    cout << "Registros cargados: " << logs.getSize() << endl;
    cout << "Lineas omitidas: " << omitidas << endl;
    int opcion = 0;
    bool ordenado = false;

    //mostramos el menu hasta que el usuario decida salir
    do {
        cout << "\n---------- Menu ----------" << endl;
        cout << "1. Ordenar por fecha y hora" << endl;
        cout << "2. Buscar logs por dia" << endl;
        cout << "3. Mostrar logs en orden descendente" << endl;
        cout << "4. Estadisticas del archivo" << endl;
        cout << "5. Salir" << endl;
        cout << "Selecciona una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            if (ordenado) {
                cout << "Los registros ya estan ordenados." << endl;
            } else {
                //preguntamos la prediccion
                int prediccion;
                cout << "Predice el crecimiento de comparaciones:" << endl;
                cout << "1. n log n" << endl;
                cout << "2. n^2" << endl;
                cout << "Opcion: ";
                cin >> prediccion;
                //medimos el tiempo del ordenamiento
                auto inicio = chrono::high_resolution_clock::now();
                logs.mergeSort();
                auto fin = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> tiempo = fin - inicio;
                ordenado = true;
                //guardamos los registros ordenados
                guardarArchivo(logs);

                //mostramos los resultados
                cout << "\nResultados del ordenamiento:" << endl;
                cout << "Algoritmo: Merge Sort" << endl;
                cout << "Archivo: " << nombreArchivo << endl;
                cout << "Total de registros: " << logs.getSize() << endl;
                cout << "Tiempo: " << tiempo.count() << " ms" << endl;
                cout << "Comparaciones: " << logs.getComparaciones() << endl;
                cout << "Profundidad maxima: " << logs.getProfundidadMaxima() << endl;

                if (prediccion == 1) {
                    cout << "Tu prediccion coincide con el crecimiento esperado de Merge Sort." << endl;
                } else if (prediccion == 2) {
                    cout << "Tu prediccion no coincide. Merge Sort tiene crecimiento O(n log n)." << endl;
                } else {
                    cout << "Prediccion no valida." << endl;
                }
                            }
        } else if (opcion == 2) {
            if (!ordenado) {
                cout << "Primero debes ordenar los registros con la opcion 1." << endl;
            } else {
                int anio, dia;
                string mes;
                cout << "Ingresa el anio: ";
                cin >> anio;
                cout << "Ingresa el mes (Jan, Feb, Mar...): ";
                cin >> mes;
                cout << "Ingresa el dia: ";
                cin >> dia;
                buscarPorDia(logs, anio, mes, dia);
            }
        } else if (opcion == 3) {
            if (!ordenado) {
                cout << "Primero debes ordenar los registros con la opcion 1." << endl;
            } else {
                cout << "\nRegistros en orden inverso:" << endl;
                mostrarInverso(logs);
            }
        } else if (opcion == 4) {
            mostrarEstadisticas(logs);
        } else if (opcion == 5) {
            cout << "El programa finalizo" << endl;
        } else {
            cout << "Opcion no valida." << endl;
        }
    } while (opcion != 5);
    return 0;
}
