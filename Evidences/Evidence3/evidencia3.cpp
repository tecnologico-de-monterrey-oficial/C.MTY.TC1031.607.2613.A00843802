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

        while(getline(archivo, linea)){
            contador++;
        }

        cout << "Cantidad de lineas: " << contador << endl;
    }

    archivo.close();

    return 0;
}