//Isis Krystal Agramón Leal
//A00843802

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Log.h"
#include "Sorts.h"

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
    cout << "Primer log: " << logs[0].key << endl;

    selectionSort(logs);

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

    return 0;
}