//Isis Krystal Agramón Leal
//A008483802

#include <iostream>
#include <fstream>
#include <string>
#include "Log3.h"
#include "Heap3.h"
#include "BST3.h"

using namespace std;

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

                contador++;
            }
        }

        cout << "Cantidad de registros: " << contador << endl;
    }

    archivo.close();

    return 0;
}