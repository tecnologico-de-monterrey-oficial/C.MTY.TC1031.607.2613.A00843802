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


int main(){

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

switch (opcionAlgoritmo){
    case 1:
        cout << "Mejor caso: O(n^2)" << endl;
        cout << "Peor caso: O(n^2)" << endl;
        break;

    case 2:
        cout << "Mejor caso: O(n)" << endl;
        cout << "Peor caso: O(n^2)" << endl;
        break;
    case 3:
        cout << "Mejor caso: O(n^2)" << endl;
        cout << "Peor caso: O(n^2)" << endl;
    break;

    case 4:
        cout << "Mejor caso: O(n)" << endl;
        cout << "Peor caso: O(n^2)" << endl;
    break;

    case 5:
        cout << "Mejor caso: O(n log n)" << endl;
        cout << "Peor caso: O(n^2)" << endl;
    break;

    case 6:
        cout << "Mejor caso: O(n log n)" << endl;
        cout << "Peor caso: O(n log n)" << endl;
    break;

    case 7:
        cout << "Mejor caso: O(n log n)" << endl;
        cout << "Peor caso: O(n^2)" << endl;
    break;

    
}

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
    return 0;
}