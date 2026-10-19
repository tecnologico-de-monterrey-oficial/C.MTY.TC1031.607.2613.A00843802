//Isis Krystal Agramón Leal
//A00843802

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <chrono>
#include <limits>
#include <cctype>
#include "Queue.h"
#include "DoublyLinkedList.h"
#include "Stack.h"
#include "Log.h"

using namespace std;
bool fechaValida(int anio, string mes, int dia) {
    string meses[12] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };
    int diasMes[12] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };
    if (anio < 1) {
        return false;
    }
    int posicion = -1;
    for (int i = 0; i < 12; i++) {
        if (mes == meses[i]) {
            posicion = i;
            break;
        }
    }
    if (posicion == -1) {
        return false;
    }
    //verificamos si el anio es bisiesto
    if (posicion == 1) {
        if ((anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0) {
            diasMes[1] = 29;
        }
    }
    if (dia < 1 || dia > diasMes[posicion]) {
        return false;
    }
    return true;
}

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

void mostrarInverso(DoublyLinkedList<Log>& logs, int anio, string mes, int dia) {
    //creamos un stack para guardar los registros del dia
    Stack<Log> stack;
    //creamos la fecha que queremos buscar
    Log buscado(anio, mes, dia, "00:00:00", "", "");
    //recorremos los registros ordenados
    for (int i = 0; i < logs.getSize(); i++) {
        Log registro = logs.getData(i);
        //si pasamos de la fecha, dejamos de buscar
        if (registro.key.substr(0, 8) > buscado.key.substr(0, 8)) {
            break;
        }
        //guardamos solamente los registros del dia
        if (registro.year == anio && registro.month == mes && registro.day == dia) {
            stack.push(registro);
        }
}

    //validamos si encontramos registros
    if (stack.isEmpty()) {
        cout << "No se encontraron registros en esa fecha." << endl;
        return;
    }

    cout << "\nRegistros en orden descendente:" << endl;

    //mostramos los registros desde el mas reciente
    while (!stack.isEmpty()) {
        Log registro = stack.pop();

        cout << registro.month << " " << registro.day << " "
             << registro.year << " " << registro.time << " "
             << registro.ip << " " << registro.message << endl;
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



//leemos numeros completos sin dejar errores en cin
bool leerNumero(const string& mensaje, int& numero) {
    string entrada;
    cout << mensaje;
    if (!getline(cin, entrada)) return false;
    stringstream ss(entrada);
    char extra;
    return (ss >> numero) && !(ss >> extra);
}

bool leerFecha(int& anio, string& mes, int& dia) {
    if (!leerNumero("Ingresa el anio: ", anio)) return false;
    cout << "Ingresa el mes (Jan, Feb, Mar...): ";
    if (!getline(cin, mes)) return false;
    if (!leerNumero("Ingresa el dia: ", dia)) return false;
    return fechaValida(anio, mes, dia);
}

bool horaValida(const string& hora) {
    if (hora.size() != 8 || hora[2] != ':' || hora[5] != ':') return false;
    for (int i = 0; i < 8; i++) {
        if (i != 2 && i != 5 && !isdigit(static_cast<unsigned char>(hora[i]))) return false;
    }
    int h = stoi(hora.substr(0, 2));
    int m = stoi(hora.substr(3, 2));
    int s = stoi(hora.substr(6, 2));
    return h < 24 && m < 60 && s < 60;
}

bool validarLinea(const string& linea, int& anio, string& mes, int& dia,
                  string& hora, string& ip, string& mensaje, string& motivo) {
    stringstream ss(linea);
    if (!(ss >> mes >> dia >> anio >> hora >> ip)) {
        motivo = "faltan datos o la fecha tiene un formato incorrecto";
        return false;
    }
    getline(ss, mensaje);
    size_t inicio = mensaje.find_first_not_of(" \t\r");
    if (inicio == string::npos) mensaje.clear();
    else mensaje.erase(0, inicio);

    if (!fechaValida(anio, mes, dia)) {
        motivo = "fecha no valida";
        return false;
    }
    if (!horaValida(hora)) {
        motivo = "hora no valida";
        return false;
    }
    if (ip.empty() || mensaje.empty()) {
        motivo = "falta la IP o el mensaje";
        return false;
    }
    return true;
}

int main() {
    //creamos nuestras estructuras
    Queue<string> queue;
    DoublyLinkedList<Log> logs;

    int opcionArchivo;
    if (!leerNumero("Selecciona el archivo que deseas cargar:\n1. log607-1.txt\n2. log607-2.txt\nOpcion: ", opcionArchivo)) {
        cout << "Opcion no valida." << endl;
        return 1;
    }

    string nombreArchivo;
    if (opcionArchivo == 1) nombreArchivo = "log607-1.txt";
    else if (opcionArchivo == 2) nombreArchivo = "log607-2.txt";
    else {
        cout << "Opcion no valida." << endl;
        return 1;
    }

    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo: " << nombreArchivo << endl;
        return 1;
    }

    //primero guardamos todas las lineas en Queue
    string linea;
    while (getline(archivo, linea)) queue.enqueue(linea);
    archivo.close();

    //despues sacamos cada linea, la validamos y la agregamos a la lista
    int omitidas = 0;
    int numeroLinea = 0;
    while (!queue.isEmpty()) {
        linea = queue.dequeue();
        numeroLinea++;
        string mes, hora, ip, mensaje, motivo;
        int dia, anio;
        if (!validarLinea(linea, anio, mes, dia, hora, ip, mensaje, motivo)) {
            omitidas++;
            cout << "Linea " << numeroLinea << " omitida: " << motivo << endl;
            continue;
        }
        Log registro(anio, mes, dia, hora, ip, mensaje);
        logs.addLast(registro);
    }

    cout << "\nArchivo cargado: " << nombreArchivo << endl;
    cout << "Registros cargados: " << logs.getSize() << endl;
    cout << "Lineas omitidas: " << omitidas << endl;

    int opcion = 0;
    bool ordenado = false;
    int ultimoAnio = 0, ultimoDia = 0;
    string ultimoMes = "";
    bool hayBusqueda = false;

    do {
        cout << "\n---------- Menu ----------" << endl;
        cout << "1. Ordenar por fecha y hora" << endl;
        cout << "2. Buscar logs por dia" << endl;
        cout << "3. Mostrar logs en orden descendente" << endl;
        cout << "4. Estadisticas del archivo" << endl;
        cout << "5. Salir" << endl;

        if (!leerNumero("Selecciona una opcion: ", opcion)) {
            if (cin.eof()) break;
            cout << "Opcion no valida. Escribe un numero del 1 al 5." << endl;
            continue;
        }

        if (opcion == 1) {
            if (ordenado) {
                cout << "Los registros ya estan ordenados." << endl;
            } else {
                int prediccion;
                if (!leerNumero("Predice el crecimiento de comparaciones:\n1. n log n\n2. n^2\nOpcion: ", prediccion)
                    || (prediccion != 1 && prediccion != 2)) {
                    cout << "Prediccion no valida. Intenta nuevamente." << endl;
                    continue;
                }
                auto inicio = chrono::high_resolution_clock::now();
                logs.mergeSort();
                auto fin = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> tiempo = fin - inicio;
                ordenado = true;
                guardarArchivo(logs);

                cout << "\nResultados del ordenamiento:" << endl;
                cout << "Algoritmo: Merge Sort" << endl;
                cout << "Archivo: " << nombreArchivo << endl;
                cout << "Total de registros: " << logs.getSize() << endl;
                cout << "Tiempo: " << tiempo.count() << " ms" << endl;
                cout << "Comparaciones: " << logs.getComparaciones() << endl;
                cout << "Profundidad maxima: " << logs.getProfundidadMaxima() << endl;
                if (prediccion == 1)
                    cout << "Tu prediccion coincide con el crecimiento esperado de Merge Sort." << endl;
                else
                    cout << "Tu prediccion no coincide. Merge Sort tiene crecimiento O(n log n)." << endl;
            }
        } else if (opcion == 2) {
            if (!ordenado) {
                cout << "Primero debes ordenar los registros con la opcion 1." << endl;
            } else {
                int anio, dia;
                string mes;
                if (!leerFecha(anio, mes, dia)) {
                    cout << "Fecha no valida. Intenta nuevamente." << endl;
                } else {
                    buscarPorDia(logs, anio, mes, dia);
                    ultimoAnio = anio;
                    ultimoMes = mes;
                    ultimoDia = dia;
                    hayBusqueda = true;
                }
            }
        } else if (opcion == 3) {
            if (!ordenado) {
                cout << "Primero debes ordenar los registros con la opcion 1." << endl;
            } else {
                if (!hayBusqueda) {
                    if (!leerFecha(ultimoAnio, ultimoMes, ultimoDia)) {
                        cout << "Fecha no valida. Intenta nuevamente." << endl;
                        continue;
                    }
                    hayBusqueda = true;
                }
                mostrarInverso(logs, ultimoAnio, ultimoMes, ultimoDia);
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