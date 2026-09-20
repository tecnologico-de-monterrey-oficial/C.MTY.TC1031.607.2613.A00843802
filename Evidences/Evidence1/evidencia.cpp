//Isis Krystal Agramón Leal
//A00843802

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Log.h"
#include "Sorts.h"
#include <chrono>

using namespace std;

vector<Log> readFile(string fileName){
    vector<Log> logs;
    ifstream file;
    file.open(fileName);
    if (!file.is_open()){
        cout << "Error al abrir el archivo." << endl;
        return logs;
    }
    string line;
     while (getline(file, line)){
        stringstream ss(line);
        string month;
        int day;
        int year;
        string time;
        string ip;
        string message;
        ss >> month >> day >> year >> time >> ip;
        getline(ss >> ws, message);
        Log log1(year, month, day, time, ip, message);
        logs.push_back(log1);
    }
    return logs;
}

int buscarInicio(vector<Log> &logs, Log data) {
    int left = 0;
    int right = logs.size() - 1;
    int result = logs.size();
    while (left <= right) {
        int mid = (left + right) / 2;
        if (logs[mid] >= data) {
            result = mid;
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return result;
}

int buscarFinal(vector<Log> &logs, Log data) {
    int left = 0;
    int right = logs.size() - 1;
    int result = logs.size();

    while (left <= right) {
        int mid = (left + right) / 2;
        if (logs[mid] > data) {
        result = mid;
        right = mid - 1;
    }
    else {
        left = mid + 1;
    }
    }
    return result;
}

int main(){

    char continuar;

do {
    int opcionArchivo;
    cout << "Selecciona el archivo:" << endl;
    cout << "Escribe 1 para seleccionar log607-1.txt" << endl;
    cout << "Escribe 2 para seleccionar log607-2.txt" << endl;
    cout << "Opcion: ";
    cin >> opcionArchivo;

    string fileName;

    switch (opcionArchivo){
    case 1:
        fileName = "data/log607-1.txt";
        break;

    case 2:
        fileName = "data/log607-2.txt";
        break;

    default:
        cout << "Opcion invalida." << endl;
        return 1;
}

    vector<Log> logs = readFile(fileName);
    cout << "Archivo seleccionado: " << fileName << endl;

    cout << "Total de logs: " << logs.size() << endl;

    int opcionAlgoritmo;
    cout << "Selecciona el algoritmo de ordenamiento:" << endl;
    cout << "Escribe 1 para Swap Sort" << endl;
    cout << "Escribe 2 para Bubble Sort" << endl;
    cout << "Escribe 3 para Selection Sort" << endl;
    cout << "Escribe 4 para Insertion Sort" << endl;
    cout << "Escribe 5 para Quick Sort" << endl;
    cout << "Escribe 6 para Merge Sort" << endl;
    cout << "Escribe 7 para Shell Sort" << endl;
    cout << "Opcion: ";
    cin >> opcionAlgoritmo;

    string prediccion;
    string razon;

    cout << "Crees que este algoritmo sera rapido o lento? ";
    cin >> prediccion;
    cout << "Por que? ";
    getline(cin >> ws, razon);

    string nombreAlgoritmo;

    auto inicio = chrono::high_resolution_clock::now();

    switch (opcionAlgoritmo){
    case 1:
        nombreAlgoritmo = "Swap Sort";
        swapSort(logs);
        break;

    case 2:
        nombreAlgoritmo = "Bubble Sort";
        bubbleSort(logs);
        break;

    case 3:
        nombreAlgoritmo = "Selection Sort";
        selectionSort(logs);
        break;

    case 4:
        nombreAlgoritmo = "Insertion Sort";
        insertionSort(logs);
        break;

    case 5:
        nombreAlgoritmo = "Quick Sort";
        quickSort(logs, 0, logs.size() - 1);
        break;

    case 6:
        nombreAlgoritmo = "Merge Sort";
        mergeSort(logs, 0, logs.size() - 1);
        break;

    case 7:
        nombreAlgoritmo = "Shell Sort";
        shellSort(logs);
        break;

    default:
        cout << "Opcion invalida." << endl;
        return 1;
}

auto fin = chrono::high_resolution_clock::now();
chrono::duration<double, milli> duracion = fin - inicio;
cout << "Algoritmo: " << nombreAlgoritmo << endl;
cout << "Tiempo de ejecucion: " << duracion.count() << " ms" << endl;

string coincidencia;
cout << "Despues de ver el tiempo, tu prediccion coincidio? Escribe si o no: ";
cin >> coincidencia;

cout << "La prediccion coincidio: " << coincidencia << endl;

string mejorCaso;
string peorCaso; 

switch (opcionAlgoritmo){
    case 1:
    mejorCaso = "O(n^2)";
    peorCaso = "O(n^2)";
    break;

    case 2:
        mejorCaso = "O(n)";
        peorCaso = "O(n^2)";
        break;

    case 3:
        mejorCaso = "O(n^2)";
        peorCaso = "O(n^2)";
        break;

    case 4:
        mejorCaso = "O(n)";
        peorCaso = "O(n^2)";
        break;

    case 5:
        mejorCaso = "O(n log n)";
        peorCaso = "O(n^2)";
        break;

    case 6:
        mejorCaso = "O(n log n)";
        peorCaso = "O(n log n)";
        break;

    case 7:
        mejorCaso = "O(n log n)";
        peorCaso = "O(n^2)";
        break;
}

cout << "Mejor caso: " << mejorCaso << endl;
cout << "Peor caso: " << peorCaso << endl;

ofstream resultados;
resultados.open("resultados.txt", ios::app);

resultados << "Algoritmo: " << nombreAlgoritmo << endl;
resultados << "Archivo: " << fileName << endl;
resultados << "Cantidad de registros: " << logs.size() << endl;
resultados << "Tiempo de ejecucion: " << duracion.count() << " ms" << endl;
resultados << "Mejor caso: " << mejorCaso << endl;
resultados << "Peor caso: " << peorCaso << endl;
resultados << "La prediccion coincidio: " << coincidencia << endl;
resultados << endl;
resultados.close();

    bool ordenado = true;

    for (int i = 1; i < logs.size(); i++){
        if (logs[i] < logs[i - 1]){
            ordenado = false;
            break;
        }
    }

    cout << "Lista ordenada: " << ordenado << endl;

    cout << "Primer log ordenado: " << logs[0].key << endl;
    cout << "Ultimo log ordenado: " << logs[logs.size() - 1].key << endl;

    ofstream output;
    output.open("output608.txt");
    for (int i = 0; i < logs.size(); i++){
    output << logs[i].month << " " << logs[i].day << " " << logs[i].year << " " << logs[i].time << " " << logs[i].ip << " " << logs[i].message << endl;

    }

    string monthInicio;
    int dayInicio;
    int yearInicio;
    string timeInicio;
    cout << "Ingresa la fecha y hora inicial." << endl;
    cout << "Usa el mes abreviado en ingles (Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec)." << endl;
    cout << "Formato: Sep 8 2024 04:30:00" << endl;
    cout << "Fecha inicial: ";
    cin >> monthInicio >> dayInicio >> yearInicio >> timeInicio;

    string monthFin;
    int dayFin;
    int yearFin;
    string timeFin;
    cout << "Ingresa la fecha y hora final." << endl;
    cout << "Fecha final: ";
    cin >> monthFin >> dayFin >> yearFin >> timeFin;

    Log logInicio(yearInicio, monthInicio, dayInicio, timeInicio, "", "");
    Log logFinal(yearFin, monthFin, dayFin, timeFin, "", "");
   
 if (logInicio.key == "" || logFinal.key == ""){
    cout << "Error: formato de fecha invalido." << endl;
    return 1;
}

if (logInicio > logFinal){
    cout << "Error: la fecha inicial no puede ser posterior a la fecha final." << endl;
    return 1;
}

if (dayInicio < 1 || dayInicio > 31 || dayFin < 1 || dayFin > 31){
    cout << "Error: dia invalido." << endl;
    return 1;
}

if (timeInicio.size() != 8 || timeFin.size() != 8){
    cout << "Error: formato de hora invalido." << endl;
    return 1;
}

if (timeInicio[2] != ':' || timeInicio[5] != ':' ||
    timeFin[2] != ':' || timeFin[5] != ':'){
    cout << "Error: formato de hora invalido." << endl;
    return 1;
}

int horaInicio = stoi(timeInicio.substr(0, 2));
int horaFin = stoi(timeFin.substr(0, 2));
int minutoInicio = stoi(timeInicio.substr(3, 2));
int minutoFin = stoi(timeFin.substr(3, 2));

int segundoInicio = stoi(timeInicio.substr(6, 2));
int segundoFin = stoi(timeFin.substr(6, 2));

if (horaInicio < 0 || horaInicio > 23 || horaFin < 0 || horaFin > 23 ||
    minutoInicio < 0 || minutoInicio > 59 || minutoFin < 0 || minutoFin > 59 ||
    segundoInicio < 0 || segundoInicio > 59 || segundoFin < 0 || segundoFin > 59){
    cout << "Error: hora invalida." << endl;
    return 1;
}


    cout << "Key inicial: " << logInicio.key << endl;
    cout << "Key final: " << logFinal.key << endl;

    int posicionInicio = buscarInicio(logs, logInicio);

    cout << "Posicion inicial encontrada: " << posicionInicio << endl;

    int posicionFinal = buscarFinal(logs, logFinal);

    cout << "Posicion final encontrada: " << posicionFinal << endl;
    ofstream rangeFile;
    rangeFile.open("range607.txt");
        if (posicionInicio >= posicionFinal){
        cout << "No se encontraron logs en ese rango." << endl;  
    }else {
            for (int i = posicionInicio; i < posicionFinal; i++){
                rangeFile << logs[i].month << " " << logs[i].day << " "
                        << logs[i].year << " " << logs[i].time << " "
                        << logs[i].ip << " " << logs[i].message << endl;
            }
   }

cout << "Deseas realizar otra ejecucion? Escribe s o n: ";
cin >> continuar;

} while (continuar == 's' || continuar == 'S');

return 0;
}