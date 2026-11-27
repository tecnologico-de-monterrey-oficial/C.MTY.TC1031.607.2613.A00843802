//Isis Krystal Agramón Leal
//A00843802

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector> //NUEVO
#include <limits> //NUEVO
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

//Validar una direccion IP
bool validarIP(string ip){
    stringstream ss(ip);
    string parte;
    int contador = 0;

    if(ip.empty() || ip.back() == '.'){
        return false;
    }

    while(getline(ss, parte, '.')){
        if(parte.empty() || parte.length() > 3){
            return false;
        }

        for(char caracter : parte){
            if(caracter < '0' || caracter > '9'){
                return false;
            }
        }

        int numero = stoi(parte);

        if(numero < 0 || numero > 255){
            return false;
        }

        contador++;
    }

    return contador == 4;
}

//NUEVO
//Validar la fecha del registro
bool validarFecha(string month, int day, int year){
    string meses[12] = {
        "Jan", "Feb", "Mar", "Apr",
        "May", "Jun", "Jul", "Aug",
        "Sep", "Oct", "Nov", "Dec"
    };

    int dias[12] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    if(year <= 0){
        return false;
    }

    //Validar si el año es bisiesto
    if(year % 400 == 0 ||
       (year % 4 == 0 && year % 100 != 0)){
        dias[1] = 29;
    }

    //Buscar el mes y validar el dia
    for(int i = 0; i < 12; i++){
        if(month == meses[i]){
            return day >= 1 && day <= dias[i];
        }
    }

    return false;
}

//NUEVO
//Validar la hora del registro
bool validarHora(string time){
    if(time.length() != 8){
        return false;
    }

    if(time[2] != ':' || time[5] != ':'){
        return false;
    }

    //Validar que los caracteres sean numeros
    for(int i = 0; i < time.length(); i++){
        if(i != 2 && i != 5){
            if(time[i] < '0' || time[i] > '9'){
                return false;
            }
        }
    }

    int hora = stoi(time.substr(0, 2));
    int minuto = stoi(time.substr(3, 2));
    int segundo = stoi(time.substr(6, 2));

    return hora >= 0 && hora <= 23 &&
           minuto >= 0 && minuto <= 59 &&
           segundo >= 0 && segundo <= 59;
}

//NUEVO
//Validar todos los campos del registro
string validarRegistro(string month, string day,
                       string year, string time,
                       string ip, string message){

    //Validar que los campos no esten vacios
    if(month.empty() || day.empty() ||
       year.empty() || time.empty() ||
       ip.empty() || message.empty()){
        return "Campos incompletos";
    }

    //Validar que el dia sea numerico
    for(char caracter : day){
        if(caracter < '0' || caracter > '9'){
            return "Dia no valido";
        }
    }

    //Validar que el año sea numerico
    for(char caracter : year){
        if(caracter < '0' || caracter > '9'){
            return "Anio no valido";
        }
    }

    //Validar la fecha
    try{
        if(!validarFecha(month, stoi(day), stoi(year))){
            return "Fecha no valida";
        }
    } catch(const exception&){
        return "Fecha no valida";
    }

    //Validar la hora
    if(!validarHora(time)){
        return "Hora no valida";
    }

    //Validar la direccion IP
    if(!validarIP(ip)){
        return "Direccion IP no valida";
    }

    return "";
}

//NUEVO
//Mostrar las opciones del programa
void mostrarMenu(){
    cout << endl;
    cout << "---------- MENU ----------" << endl;
    cout << "1. Mostrar cantidad de registros" << endl;
    cout << "2. Consultar direccion IP" << endl;
    cout << "0. Salir" << endl;
    cout << "Selecciona una opcion: ";
}

int main(){
    ifstream archivo("log607-3.json");

    if(archivo.is_open() == false){
        cout << "Error no se pudo abrir el archivo" << endl;
        return 1;
    } else{
        string linea;
        int contador = 0;
        int invalidos = 0; //NUEVO

        //Guardar los registros validos
        vector<Log> registrosValidos; //NUEVO

        //Crear el BST de direcciones IP
        BST<unsigned long long> direccionesIP;

        //Leer cada linea del archivo
        while(getline(archivo, linea)){

            //Ignorar las lineas que no contienen registros
            if(linea.find('{') == string::npos){
                continue;
            }

            //Extraer los campos del registro
            string ip = extraerCampo(linea, "ip");
            string month = extraerCampo(linea, "month");
            string day = extraerCampo(linea, "day");
            string year = extraerCampo(linea, "year");
            string time = extraerCampo(linea, "time");
            string message = extraerCampo(linea, "message");

            //NUEVO
            //Validar el registro
            string error = validarRegistro(month, day,
                                           year, time,
                                           ip, message);

            if(!error.empty()){
                invalidos++;
                continue;
            }

            //Crear un objeto Log
            Log registro(stoi(year), month, stoi(day),
                         time, ip, message);

            if(registro.key.length() < 26){
                invalidos++;
                continue;
            }

            //NUEVO
            //Guardar el registro valido
            registrosValidos.push_back(registro);

            //Convertir e insertar la IP en el BST
            unsigned long long ipNumerica = convertirIP(ip);
            direccionesIP.insert(ipNumerica);

            contador++;
        }

        archivo.close();

        //Mostrar la cantidad de registros
        cout << "Cantidad de registros validos: "
             << contador << endl;

        cout << "Cantidad de registros invalidos: "
             << invalidos << endl;

        //NUEVO
        //Mostrar el menu
        int opcion;

        while(true){
            mostrarMenu();

            //Validar la opcion ingresada
            if(!(cin >> opcion)){
                if(cin.eof()){
                    break;
                }

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Opcion no valida" << endl;
                continue;
            }

            if(opcion == 0){
                break;
            }

            if(opcion == 1){
                cout << "Registros validos: "
                     << registrosValidos.size() << endl;

                cout << "Registros invalidos: "
                     << invalidos << endl;

            } else if(opcion == 2){

                //Consultar direcciones IP
                string ipConsulta;

                cout << "Ingresa una direccion IP: ";

                if(!(cin >> ipConsulta)){
                    break;
                }

                //Validar la IP ingresada
                if(!validarIP(ipConsulta)){
                    cout << "Direccion IP no valida" << endl;
                    continue;
                }

                //Buscar la cantidad de apariciones
                unsigned long long ipNumerica = convertirIP(ipConsulta);

                int cantidad = direccionesIP.getCount(ipNumerica);

                cout << "IP: " << ipConsulta << endl;
                cout << "Cantidad de apariciones: "
                     << cantidad << endl;

            } else{
                cout << "Opcion no valida" << endl;
            }
        }

        cout << "Fin del programa" << endl;
    }

    return 0;
}
