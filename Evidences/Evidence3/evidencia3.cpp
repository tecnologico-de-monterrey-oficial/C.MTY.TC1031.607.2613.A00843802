//Isis Krystal Agramón Leal
//A00843802

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <limits>
#include <chrono>
#include <functional>
#include <exception>
#include <cmath>
#include <utility>
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

//Verificar el orden de dos registros
bool verificarOrden(const Log &anterior,
                    const Log &actual, int tipo){

    //Orden descendente
    if(tipo == 1){
        return !(anterior < actual);
    }

    //Orden ascendente
    if(tipo == 2){
        return !(anterior > actual);
    }

    return false;
}

//Realizar el ordenamiento de los registros
void ordenarRegistros(const vector<Log>& registrosValidos,
                      int tipo){

    if(registrosValidos.empty()){
        cout << "No hay registros para ordenar" << endl;
        return;
    }

    //Determinar el tipo de ordenamiento
    string nombreArchivo;

    function<bool(const Log&, const Log&)> comparador;

    if(tipo == 1){
        comparador = greater<Log>();
        nombreArchivo = "output608-1.out";

        cout << "Ordenamiento descendente" << endl;
    } else{
        comparador = less<Log>();
        nombreArchivo = "output608-2.out";

        cout << "Ordenamiento ascendente" << endl;
    }

    //Solicitar una prediccion al usuario
    int prediccion;

    cout << endl;
    cout << "Si duplicamos la cantidad de registros, que pasara con las comparaciones?" << endl;
    cout << "1. Aproximadamente las mismas" << endl;
    cout << "2. Aproximadamente el doble" << endl;
    cout << "3. Un poco mas del doble" << endl;
    cout << "4. Cuatro veces mas" << endl;
    cout << "Ingresa tu prediccion: ";

    while(!(cin >> prediccion) || prediccion < 1 || prediccion > 4){
        if(cin.eof()){
            return;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Prediccion no valida" << endl;
        cout << "Ingresa tu prediccion: ";
    }

    //Crear el Heap
    Heap<Log> registros(comparador);

    //Iniciar la medicion del tiempo
    auto inicio = chrono::steady_clock::now();

    //Insertar los registros validos
    for(int i = 0; i < registrosValidos.size(); i++){
        registros.push(registrosValidos[i]);
    }

    //Obtener la altura antes de las extracciones
    int altura = registros.height();

    //Obtener las comparaciones de las inserciones
    long long comparacionesInsercion =
        registros.getComparisons();

    auto finInsercion = chrono::steady_clock::now();

    double tiempoInsercion =
        chrono::duration<double, milli>(
            finInsercion - inicio).count();

    //Guardar los registros ordenados
    vector<Log> registrosOrdenados;
    registrosOrdenados.reserve(registrosValidos.size());

    //Extraer los registros del Heap
    while(!registros.empty()){
        registrosOrdenados.push_back(registros.pop());
    }

    //Finalizar la medicion del tiempo
    auto fin = chrono::steady_clock::now();

    double tiempo =
        chrono::duration<double, milli>(
            fin - inicio).count();

    //Obtener la cantidad total de comparaciones
    long long comparaciones = registros.getComparisons();

    //Verificar el ordenamiento
    bool ordenCorrecto = true;

    for(int i = 1; i < registrosOrdenados.size(); i++){
        if(!verificarOrden(registrosOrdenados[i - 1],
                           registrosOrdenados[i], tipo)){
            ordenCorrecto = false;
        }
    }

    //Crear el archivo de salida
    ofstream salida(nombreArchivo);

    if(!salida.is_open()){
        cout << "Error al crear el archivo de salida" << endl;
        return;
    }

    //Escribir los registros ordenados
    for(int i = 0; i < registrosOrdenados.size(); i++){
        Log registro = registrosOrdenados[i];

        salida << registro.month << " "
               << registro.day << " "
               << registro.year << " "
               << registro.time << " "
               << registro.ip << " "
               << registro.message << endl;
    }

    salida.close();

    //Mostrar los resultados del ordenamiento
    cout << endl;
    cout << "Cantidad de registros: "
         << registrosValidos.size() << endl;

    cout << "Altura del Heap: "
         << altura << endl;

    cout << "Comparaciones antes de las extracciones: "
         << comparacionesInsercion << endl;

    cout << "Tiempo antes de las extracciones: "
         << tiempoInsercion << " ms" << endl;

    cout << "Comparaciones durante las extracciones: "
         << comparaciones - comparacionesInsercion << endl;

    cout << "Cantidad total de comparaciones: "
         << comparaciones << endl;

    cout << "Tiempo total de ejecucion: "
         << tiempo << " ms" << endl;

    if(ordenCorrecto){
        cout << "Registros ordenados correctamente" << endl;
    } else{
        cout << "Error en el ordenamiento" << endl;
    }

    cout << "Archivo generado: "
         << nombreArchivo << endl;

    //Crear otro Heap para duplicar los registros
    Heap<Log> registrosDuplicados(comparador);

    //Iniciar la medicion del tiempo
    auto inicioDuplicados = chrono::steady_clock::now();

    //Insertar dos veces los registros validos
    for(int j = 0; j < 2; j++){
        for(int i = 0; i < registrosValidos.size(); i++){
            registrosDuplicados.push(registrosValidos[i]);
        }
    }

    //Obtener la altura antes de las extracciones
    int alturaDuplicados = registrosDuplicados.height();

    long long comparacionesInsercionDuplicados =
        registrosDuplicados.getComparisons();

    auto finInsercionDuplicados =
        chrono::steady_clock::now();

    double tiempoInsercionDuplicados =
        chrono::duration<double, milli>(
            finInsercionDuplicados -
            inicioDuplicados).count();

    //Extraer los registros duplicados
    while(!registrosDuplicados.empty()){
        registrosDuplicados.pop();
    }

    //Finalizar la medicion del tiempo
    auto finDuplicados = chrono::steady_clock::now();

    double tiempoDuplicados =
        chrono::duration<double, milli>(
            finDuplicados - inicioDuplicados).count();

    //Obtener las comparaciones de los registros duplicados
    long long comparacionesDuplicados =
        registrosDuplicados.getComparisons();

    //Mostrar los resultados del experimento
    cout << endl;
    cout << "----- REGISTROS DUPLICADOS -----" << endl;

    cout << "Cantidad de registros: "
         << registrosValidos.size() * 2 << endl;

    cout << "Altura del Heap: "
         << alturaDuplicados << endl;

    cout << "Comparaciones antes de las extracciones: "
         << comparacionesInsercionDuplicados << endl;

    cout << "Tiempo antes de las extracciones: "
         << tiempoInsercionDuplicados << " ms" << endl;

    cout << "Cantidad total de comparaciones: "
         << comparacionesDuplicados << endl;

    cout << "Tiempo total de ejecucion: "
         << tiempoDuplicados << " ms" << endl;

    //Comparar los resultados originales y duplicados
    if(comparaciones > 0){
        double aumento = static_cast<double>(comparacionesDuplicados)
                         / comparaciones;
        cout << "Las comparaciones se multiplicaron por: " << aumento << endl;
        //Criterio aproximado elegido para clasificar el resultado
        int resultado;
        if(aumento < 1.5){
            resultado = 1;
        } else if(aumento <= 2.05){
            resultado = 2;
        } else if(aumento < 3.5){
            resultado = 3;
        } else{
            resultado = 4;
        }
        cout << "Prediccion: " << prediccion << endl;
        cout << "Categoria experimental: " << resultado << endl;
        cout << (prediccion == resultado ? "La prediccion fue correcta" :
                 "La prediccion no fue correcta") << endl;
    } else{
        cout << "No se puede calcular la proporcion: cero comparaciones originales" << endl;
    }
}

//Convertir una IP numerica a su formato original
string convertirIPTexto(unsigned long long ip){
    return to_string((ip >> 24) & 255) + "." +
           to_string((ip >> 16) & 255) + "." +
           to_string((ip >> 8) & 255) + "." +
           to_string(ip & 255);
}

//Comparar las IP por cantidad de apariciones
bool compararApariciones(const pair<unsigned long long, int>& a,
                         const pair<unsigned long long, int>& b){
    if(a.second == b.second){
        return a.first < b.first;
    }

    return a.second > b.second;
}

//Mostrar las 10 direcciones IP con mas apariciones
void mostrarTop10(BST<unsigned long long>& direccionesIP){
    vector<pair<unsigned long long, int>> lista = direccionesIP.inOrder();

    if(lista.empty()){
        cout << "No hay direcciones IP" << endl;
        return;
    }

    //Crear el MaxHeap de apariciones
    Heap<pair<unsigned long long, int>> registros(compararApariciones);

    for(int i = 0; i < lista.size(); i++){
        registros.push(lista[i]);
    }

    cout << endl;
    cout << "---------- TOP 10 DE IP ----------" << endl;

    int lugar = 0;
    int apariciones = 0;

    //Extraer las 10 IP con mayor cantidad de apariciones
    while(!registros.empty() && lugar < 10){
        pair<unsigned long long, int> registro = registros.pop();
        lugar++;
        apariciones = registro.second;

        cout << lugar << ". " << convertirIPTexto(registro.first)
             << " - " << registro.second << " apariciones" << endl;
    }

    //Contar las IP adicionales empatadas con el decimo lugar
    int empatadas = 0;

    if(lugar == 10){
        while(!registros.empty() && registros.top().second == apariciones){
            registros.pop();
            empatadas++;
        }

        if(empatadas > 0){
            cout << "Hay " << empatadas
                 << " IP adicionales empatadas con el decimo lugar" << endl;
        } else{
            cout << "No hay mas IP empatadas con el decimo lugar" << endl;
        }
    } else{
        cout << "Hay menos de 10 direcciones IP distintas" << endl;
    }
}

//Consultar una direccion IP y mostrar las metricas del BST
void consultarIP(BST<unsigned long long>& direccionesIP, string ip){
    unsigned long long ipNumerica = convertirIP(ip);
    pair<int, int> resultado = direccionesIP.search(ipNumerica);

    int cantidad = resultado.first;
    int comparaciones = resultado.second;
    int altura = direccionesIP.height();
    int nodos = direccionesIP.size();

    cout << "IP: " << ip << endl;
    cout << "Existe: " << (cantidad > 0 ? "Si" : "No") << endl;
    cout << "Cantidad de apariciones: " << cantidad << endl;
    cout << "Comparaciones realizadas: " << comparaciones << endl;
    cout << "Cantidad de IP distintas: " << nodos << endl;
    cout << "Altura real del BST: " << altura << endl;

    //Calcular la altura teorica solicitada
    if(nodos > 0){
        int alturaTeorica = static_cast<int>(ceil(log2(nodos)));

        cout << "Altura teorica del BST: " << alturaTeorica << endl;

        if(altura > alturaTeorica){
            cout << "La altura real supera la teorica por "
                 << altura - alturaTeorica << endl;
        } else if(altura == alturaTeorica){
            cout << "La altura real es igual a la teorica" << endl;
        } else{
            cout << "La altura real es menor que la teorica por "
                 << alturaTeorica - altura << endl;
        }
    } else{
        cout << "Altura teorica no definida: BST vacio" << endl;
    }
}

//Mostrar las opciones del programa
void mostrarMenu(){
    cout << endl;
    cout << "---------- MENU ----------" << endl;
    cout << "1. Ordenar registros de forma descendente" << endl;
    cout << "2. Ordenar registros de forma ascendente" << endl;
    cout << "3. Top 10 de direcciones IP" << endl;
    cout << "4. Consultar direccion IP" << endl;
    cout << "5. Salir" << endl;
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
        int invalidos = 0;
        int numeroLinea = 0;

        //Guardar los registros validos
        vector<Log> registrosValidos;

        //Crear el BST de direcciones IP
        BST<unsigned long long> direccionesIP;

        //Leer cada linea del archivo
        while(getline(archivo, linea)){
            numeroLinea++;

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

            //Validar el registro
            string error = validarRegistro(month, day,
                                           year, time,
                                           ip, message);

            if(!error.empty()){
                cout << "Linea " << numeroLinea << ": " << error << endl;
                invalidos++;
                continue;
            }

            //Crear un objeto Log
            Log registro(stoi(year), month, stoi(day),
                         time, ip, message);

            if(registro.key.length() < 26){
                cout << "Linea " << numeroLinea << ": Clave no valida" << endl;
                invalidos++;
                continue;
            }

            //Guardar el registro valido
            registrosValidos.push_back(registro);

            //Convertir e insertar la IP en el BST
            unsigned long long ipNumerica = convertirIP(ip);
            direccionesIP.insert(ipNumerica);

            contador++;
        }

        archivo.close();

        //Mostrar la cantidad de registros
        cout << "Total de registros leidos: " << contador + invalidos << endl;
        cout << "Cantidad de registros validos: "
             << contador << endl;

        cout << "Cantidad de registros invalidos: "
             << invalidos << endl;

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

            if(opcion == 5){
                break;
            }

            if(opcion == 1){

                //Ordenar los registros de forma descendente
                ordenarRegistros(registrosValidos, 1);

            } else if(opcion == 2){

                //Ordenar los registros de forma ascendente
                ordenarRegistros(registrosValidos, 2);

            } else if(opcion == 3){

                mostrarTop10(direccionesIP);

            } else if(opcion == 4){

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

                //Buscar la IP y mostrar las metricas
                consultarIP(direccionesIP, ipConsulta);

            } else{
                cout << "Opcion no valida" << endl;
            }
        }

        cout << "Fin del programa" << endl;
    }

    return 0;
}