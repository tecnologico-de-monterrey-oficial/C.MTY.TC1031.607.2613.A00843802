//Isis Krystal Agramón Leal
//A008483802

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

int main(){
    ifstream archivo("log607-3.json");

    if(archivo.is_open() == false){
        cout << "Error no se pudo abrir el archivo" << endl;
        return 1;
    } else{
        string linea;
        int contador = 0;

        //Leer cada linea del archivo
        while(getline(archivo, linea)){

            //Buscar el campo ip
            size_t posicion = linea.find("\"ip\"");

            if(posicion != string::npos){

                //Encontrar las comillas de la IP
                size_t inicio = linea.find('"', posicion + 4);

                if(inicio == string::npos){
                    continue;
                }

                inicio++;
                size_t fin = linea.find('"', inicio);

                if(fin == string::npos){
                    continue;
                }

                //Extraer la direccion IP
                string ip = linea.substr(inicio, fin - inicio);

                //Convertir la IP
                unsigned long long ipNumerica = convertirIP(ip);

                contador++;
            }
        }

        cout << "Cantidad de registros: " << contador << endl;
    }

    archivo.close();

    return 0;
}