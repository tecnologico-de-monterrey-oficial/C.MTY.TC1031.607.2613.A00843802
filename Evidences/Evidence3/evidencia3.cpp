//Isis Krystal Agramón Leal
//A00843802

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Log3.h"
#include "Heap3.h"
#include "BST3.h"

using namespace std;

//Convertir una IP a un valor numerico
unsigned long long convertirIP(string ip){
    stringstream ss(ip);
    string parte;
    unsigned long long resultado = 0;

    while(getline(ss, parte, '.')){
        resultado = resultado * 256 + stoi(parte);
    }

    return resultado;
}

//Extraer un campo del JSON
string extraerCampo(string linea, string campo){
    size_t posicion = linea.find("\"" + campo + "\"");

    if(posicion == string::npos){
        return "";
    }

    posicion = linea.find(':', posicion);

    if(posicion == string::npos){
        return "";
    }

    size_t inicio = linea.find_first_not_of(" \t", posicion + 1);

    if(inicio == string::npos){
        return "";
    }

    size_t fin;

    //Si el campo es texto
    if(linea[inicio] == '"'){
        inicio++;
        fin = linea.find('"', inicio);
    } else{
        //Si el campo es numerico
        fin = linea.find_first_of(",}", inicio);
    }

    if(fin == string::npos){
        return "";
    }

    return linea.substr(inicio, fin - inicio);
}

int main(){
    ifstream archivo("log607-3.json");

    if(archivo.is_open() == false){
        cout << "Error no se pudo abrir el archivo" << endl;
        return 1;
    } else{
        string linea;
        int contador = 0;

        //Crear un Heap de registros
        Heap<Log> registros;

        //Leer cada linea del archivo
        while(getline(archivo, linea)){

            //Extraer los campos del registro
            string ip = extraerCampo(linea, "ip");

            if(ip.empty()){
                continue;
            }

            string month = extraerCampo(linea, "month");
            string day = extraerCampo(linea, "day");
            string year = extraerCampo(linea, "year");
            string time = extraerCampo(linea, "time");
            string message = extraerCampo(linea, "message");

            if(month.empty() || day.empty() ||
               year.empty() || time.empty()){
                continue;
            }

            //Crear un objeto Log
            Log registro(stoi(year), month, stoi(day),
                         time, ip, message);

            //Insertar el registro en el Heap
            registros.push(registro);

            contador++;
        }

        cout << "Cantidad de registros: " << contador << endl;

        //Comprobar que el Heap contiene registros
        if(contador > 0){
            Log primero = registros.pop();

            cout << "IP: " << primero.ip << endl;
            cout << "Fecha: " << primero.day << "/"
                 << primero.month << "/"
                 << primero.year << endl;
            cout << "Hora: " << primero.time << endl;
            cout << "Mensaje: " << primero.message << endl;
        }
    }

    archivo.close();

    return 0;
}