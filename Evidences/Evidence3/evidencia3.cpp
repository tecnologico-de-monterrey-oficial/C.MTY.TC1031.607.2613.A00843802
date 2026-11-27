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

//Comparar los registros por fecha y hora
bool compararFecha(const Log &a, const Log &b){
    string fechaA = a.key.substr(12, 14);
    string fechaB = b.key.substr(12, 14);

    return fechaA > fechaB;
}

//Comparar los registros por mensaje
bool compararMensaje(const Log &a, const Log &b){
    return a.message > b.message;
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

//Verificar el orden de dos registros
bool verificarOrden(const Log &anterior, const Log &actual,
                    int tipo){

    if(tipo == 1){
        return anterior >= actual;
    }

    if(tipo == 2){
        return !compararFecha(actual, anterior);
    }

    if(tipo == 3){
        return !compararMensaje(actual, anterior);
    }

    return false;
}

int main(){
    ifstream archivo("log607-3.json");

    if(archivo.is_open() == false){
        cout << "Error no se pudo abrir el archivo" << endl;
        return 1;
    } else{
        string linea;
        int contador = 0;

        //Crear los Heaps
        Heap<Log> registros;
        Heap<Log> registrosFecha(compararFecha);
        Heap<Log> registrosMensaje(compararMensaje);

        //Crear el BST de direcciones IP
        BST<unsigned long long> direccionesIP;

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

            if(registro.key.length() < 26){
                continue;
            }

            //Insertar el registro en los Heaps
            registros.push(registro);
            registrosFecha.push(registro);
            registrosMensaje.push(registro);

            //Convertir e insertar la IP en el BST
            unsigned long long ipNumerica = convertirIP(ip);
            direccionesIP.insert(ipNumerica);

            contador++;
        }

        cout << "Cantidad de registros: " << contador << endl;

        //Crear los archivos de salida
        ofstream salida("registrosOrdenados.txt");
        ofstream salidaFecha("registrosPorFecha.txt");
        ofstream salidaMensaje("registrosPorMensaje.txt");

        if(!salida.is_open() || !salidaFecha.is_open() ||
           !salidaMensaje.is_open()){
            cout << "Error al crear los archivos de salida" << endl;
            return 1;
        }

        //Variables para verificar el ordenamiento
        bool ordenIP = true;
        bool ordenFecha = true;
        bool ordenMensaje = true;

        Log anteriorIP;
        Log anteriorFecha;
        Log anteriorMensaje;

        //Ordenar los registros por IP
        for(int i = 0; i < contador; i++){
            Log registro = registros.pop();

            if(i > 0){
                if(!verificarOrden(anteriorIP, registro, 1)){
                    ordenIP = false;
                }
            }

            anteriorIP = registro;

            salida << registro.ip << " "
                   << registro.year << " "
                   << registro.month << " "
                   << registro.day << " "
                   << registro.time << " "
                   << registro.message << endl;
        }

        //Ordenar los registros por fecha y hora
        for(int i = 0; i < contador; i++){
            Log registro = registrosFecha.pop();

            if(i > 0){
                if(!verificarOrden(anteriorFecha, registro, 2)){
                    ordenFecha = false;
                }
            }

            anteriorFecha = registro;

            salidaFecha << registro.year << " "
                        << registro.month << " "
                        << registro.day << " "
                        << registro.time << " "
                        << registro.ip << " "
                        << registro.message << endl;
        }

        //Ordenar los registros por mensaje
        for(int i = 0; i < contador; i++){
            Log registro = registrosMensaje.pop();

            if(i > 0){
                if(!verificarOrden(anteriorMensaje, registro, 3)){
                    ordenMensaje = false;
                }
            }

            anteriorMensaje = registro;

            salidaMensaje << registro.message << " "
                          << registro.ip << " "
                          << registro.year << " "
                          << registro.month << " "
                          << registro.day << " "
                          << registro.time << endl;
        }

        salida.close();
        salidaFecha.close();
        salidaMensaje.close();

        //Mostrar los resultados de la verificacion
        if(ordenIP){
            cout << "Registros ordenados por IP correctamente" << endl;
        } else{
            cout << "Error en el ordenamiento por IP" << endl;
        }

        if(ordenFecha){
            cout << "Registros ordenados por fecha correctamente" << endl;
        } else{
            cout << "Error en el ordenamiento por fecha" << endl;
        }

        if(ordenMensaje){
            cout << "Registros ordenados por mensaje correctamente" << endl;
        } else{
            cout << "Error en el ordenamiento por mensaje" << endl;
        }

        //Consultar direcciones IP
        string ipConsulta;

        while(true){
            cout << endl;
            cout << "Ingresa una direccion IP o 0 para salir: ";

            if(!(cin >> ipConsulta)){
                break;
            }

            if(ipConsulta == "0"){
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
            cout << "Cantidad de apariciones: " << cantidad << endl;
        }

        cout << "Fin del programa" << endl;
    }

    archivo.close();

    return 0;
}