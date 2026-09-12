//Isis Krystal Agramón Leal
//A00843802

#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
using namespace std;

template <typename T>
void swap(vector<T> &list, int i, int j) {
    if (i != j) {
        //creamos una variable temporal
        T aux = list[i];
        //cambiamos i por j
        list[i] = list[j];
        //cambiamos j por aux
        list[j] = aux;
    }
}

template <typename T>
void swapSort(vector<T> &list, long long &comparaciones, long long &intercambios) {

    comparaciones = 0;
    intercambios = 0;

    for (int i = 0; i < list.size() - 1; i++) {
        for (int j = i + 1; j < list.size(); j++) {

            comparaciones++;

            if (list[j] < list[i]) {
                swap(list, i, j);
                intercambios++;
            }
        }
    }
}

template <typename T>
void bubbleSort(vector<T> &list, long long &comparaciones, long long &intercambios) {
    //definimos un booleano como verdadero
    bool change = true;

    comparaciones = 0;
    intercambios = 0;

    //iteramos desde n hasta 1
    for (int i = list.size() - 1; i > 0 && change; i--) {
        //cambiamos el valor de change a falso
        change = false;

        //iteramos desde 0 hasta que sea menor que i
        for (int j = 0; j < i; j++) {
            //comparamos j con j+1
            comparaciones++;

            if (list[j] > list[j + 1]) {
                //si hay cambio, lo marcamos
                change = true;

                //intercambiamos los valores
                swap(list, j, j + 1);

                intercambios++;
            }
        }
    }
}

//Selection Sort
template <typename T>
void selectionSort(vector<T> &list, long long &comparaciones, long long &intercambios) {

    comparaciones = 0;
    intercambios = 0;

    //iteramos toda la lista desde el principio hasta uno antes del final
    for (int i = 0; i < list.size() - 1; i++) {
        //hacemos el indice de la posicion i como el mas chico
        int min = i;

        //iteramos desde el siguiente indice hasta el final
        for (int j = i + 1; j < list.size(); j++) {
            //comparamos el valor de j contra min
            comparaciones++;

            if (list[j] < list[min]) {
                //actualizamos el valor de min
                min = j;
            }
        }

        //intercambiamos el valor de min por el valor de i
        if (min != i) {
            swap(list, min, i);
            intercambios++;
        }
    }
}

//Insertion Sort
template <typename T>
void insertionSort(vector<T> &list, long long &comparaciones, long long &intercambios) {

    comparaciones = 0;
    intercambios = 0;

    //iteramos la lista desde la segunda posicion hasta el final
    for (int i = 1; i < list.size(); i++) {
        //declaramos un contador para ver donde vamos
        int j = i;

        while (j > 0) {

            comparaciones++;

            if (list[j] < list[j - 1]) {
                //intercambiamos j con j-1
                swap(list, j, j - 1);

                intercambios++;

                //decrementamos j
                j--;
            }
            else {
                break;
            }
        }
    }
}

template <typename T>
int getPivot(vector<T> &list, int left, int right) {
    //creamos una variable auxiliar con el valor de left - 1
    int aux = left - 1;

    //creamos una variable pivot con el valor de right
    int pivot = right;

    //iteramos desde left hasta pivot - 1
    for (int i = left; i < pivot; i++) {
        //comparamos el valor del pivote con el valor de i
        if (list[pivot] > list[i]) {
            //incrementamos aux
            aux++;

            //intercambiamos aux con i
            swap(list, aux, i);
        }
    }

    //movemos el pivote a su posicion correcta
    aux++;
    swap(list, aux, pivot);

    //regresamos la posicion del pivote
    return aux;
}

template <typename T>
void quickSort(vector<T> &list, int left, int right) {
    //condicion de control
    if (left < right) {
        int pivot = getPivot(list, left, right);

        //ordenamos el lado izquierdo del pivote
        quickSort(list, left, pivot - 1);

        //ordenamos el lado derecho del pivote
        quickSort(list, pivot + 1, right);
    }
}

//Prototipo de merge
template <typename T>
void merge(vector<T> &list, int left, int mid, int right);

template <typename T>
void mergeSort(vector<T> &list, int left, int right) {
    //la condicion de control es que left < right
    if (left < right) {
        //calculamos mid
        int mid = (left + right) / 2;

        //ordenamos de left a mid
        mergeSort(list, left, mid);

        //ordenamos de mid+1 a right
        mergeSort(list, mid + 1, right);

        //combinamos las dos partes de la lista
        merge(list, left, mid, right);
    }
}

template <typename T>
void merge(vector<T> &list, int left, int mid, int right) {
    //creamos una lista para los valores del lado izquierdo
    vector<T> leftList;

    //guardamos de left hasta mid
    for (int i = left; i <= mid; i++) {
        leftList.push_back(list[i]);
    }

    //creamos una lista para los valores del lado derecho
    vector<T> rightList;

    //guardamos de mid+1 hasta right
    for (int j = mid + 1; j <= right; j++) {
        rightList.push_back(list[j]);
    }

    //indice que actualiza la lista original
    int index = left;

    //indice de la lista izquierda
    int i = 0;

    //indice de la lista derecha
    int j = 0;

    //combinamos mientras ambas listas tengan elementos
    while (i < leftList.size() && j < rightList.size()) {
        if (leftList[i] < rightList[j]) {
            list[index] = leftList[i];
            i++;
        }
        else {
            list[index] = rightList[j];
            j++;
        }

        index++;
    }

    //vaciamos lo que quede en la lista izquierda
    while (i < leftList.size()) {
        list[index] = leftList[i];
        i++;
        index++;
    }

    //vaciamos lo que quede en la lista derecha
    while (j < rightList.size()) {
        list[index] = rightList[j];
        j++;
        index++;
    }
}

//Shell Sort
template <typename T>
void shellSort(vector<T> &list) {
    //empezamos con un salto igual a la mitad del tamaño de la lista
    for (int gap = list.size() / 2; gap > 0; gap /= 2) {

        //recorremos desde gap hasta el final
        for (int i = gap; i < list.size(); i++) {

            //guardamos el valor actual
            T temp = list[i];

            int j = i;

            //movemos los elementos mayores hacia adelante
            while (j >= gap && list[j - gap] > temp) {
                list[j] = list[j - gap];
                j -= gap;
            }

            //colocamos temp en su posicion correcta
            list[j] = temp;
        }
    }
}

template <typename T>
void print(vector<T> &list) {
    for (int i = 0; i < list.size(); i++) {
        cout << list[i] << " ";
    }

    cout << endl;
}


//Lista de enteros aleatorios
vector<int> createIntList(int size) {

    vector<int> list;

    for (int i = 0; i < size; i++) {
        list.push_back(rand() % 100000);
    }

    return list;
}


//Lista de doubles aleatorios
vector<double> createDoubleList(int size) {

    vector<double> list;

    for (int i = 0; i < size; i++) {
        list.push_back((rand() % 1000000) / 100.0);
    }

    return list;
}


//String aleatorio
string randomString() {

    string word = "";

    for (int i = 0; i < 5; i++) {
        word += 'A' + rand() % 26;
    }

    return word;
}


//Lista de strings aleatorios
vector<string> createStringList(int size) {

    vector<string> list;

    for (int i = 0; i < size; i++) {
        list.push_back(randomString());
    }

    return list;
}


string algorithmName(int algorithm) {

    if (algorithm == 1) return "Swap Sort";
    if (algorithm == 2) return "Bubble Sort";
    if (algorithm == 3) return "Selection Sort";
    if (algorithm == 4) return "Insertion Sort";
    if (algorithm == 5) return "Merge Sort";
    if (algorithm == 6) return "Quick Sort";
    if (algorithm == 7) return "Shell Sort";

    return "";
}


//Ejecutar algoritmo y obtener tiempo
template <typename T>
long long executeAlgorithm(vector<T> &list, int algorithm,
                           long long &comparaciones,
                           long long &intercambios) {

    comparaciones = 0;
    intercambios = 0;

    auto inicio = chrono::high_resolution_clock::now();

    if (algorithm == 1) {
        swapSort(list, comparaciones, intercambios);
    }
    else if (algorithm == 2) {
        bubbleSort(list, comparaciones, intercambios);
    }
    else if (algorithm == 3) {
        selectionSort(list, comparaciones, intercambios);
    }
    else if (algorithm == 4) {
        insertionSort(list, comparaciones, intercambios);
    }
    else if (algorithm == 5) {
        mergeSort(list, 0, list.size() - 1);
    }
    else if (algorithm == 6) {
        quickSort(list, 0, list.size() - 1);
    }
    else if (algorithm == 7) {
        shellSort(list);
    }

    auto fin = chrono::high_resolution_clock::now();

    long long tiempo =
        chrono::duration_cast<chrono::nanoseconds>(fin - inicio).count();

    return tiempo;
}


//Ordenar la lista seleccionada
template <typename T>
void runSort(vector<T> originalList, int algorithm) {

    vector<T> list = originalList;

    long long comparaciones = 0;
    long long intercambios = 0;

    long long tiempo =
        executeAlgorithm(list, algorithm, comparaciones, intercambios);

    cout << endl;
    cout << "Lista ordenada con " << algorithmName(algorithm) << ":" << endl;

    print(list);

    cout << "Tiempo: " << tiempo << " nanosegundos" << endl;

    if (algorithm >= 1 && algorithm <= 4) {
        cout << "Comparaciones: " << comparaciones << endl;
        cout << "Intercambios: " << intercambios << endl;
    }
}


//Medir tiempo para el analisis
template <typename T>
long long measureTime(vector<T> list, int algorithm) {

    long long comparaciones = 0;
    long long intercambios = 0;

    return executeAlgorithm(list, algorithm, comparaciones, intercambios);
}


//Analizar un tipo de dato
template <typename T>
void analyzeType(string type,
                 vector<T> list1000,
                 vector<T> list10000,
                 vector<T> list100000,
                 ofstream &file) {

    for (int algorithm = 1; algorithm <= 7; algorithm++) {

        cout << endl;
        cout << "Analizando " << algorithmName(algorithm)
             << " con " << type << "..." << endl;

        long long tiempo1000 =
            measureTime(list1000, algorithm);

        long long tiempo10000 =
            measureTime(list10000, algorithm);

        long long tiempo100000 =
            measureTime(list100000, algorithm);

        cout << algorithmName(algorithm) << ", "
             << type << ", "
             << tiempo1000 << ", "
             << tiempo10000 << ", "
             << tiempo100000 << endl;

        file << algorithmName(algorithm) << ","
             << type << ","
             << tiempo1000 << ","
             << tiempo10000 << ","
             << tiempo100000 << endl;
    }
}


//Generar archivo CSV
void comparativeAnalysis() {

    vector<int> int1000 = createIntList(1000);
    vector<int> int10000 = createIntList(10000);
    vector<int> int100000 = createIntList(100000);

    vector<double> double1000 = createDoubleList(1000);
    vector<double> double10000 = createDoubleList(10000);
    vector<double> double100000 = createDoubleList(100000);

    vector<string> string1000 = createStringList(1000);
    vector<string> string10000 = createStringList(10000);
    vector<string> string100000 = createStringList(100000);

    ofstream file("resultados.csv");

    file << "algoritmo,tipoDato,tiempo1000,tiempo10000,tiempo100000" << endl;

    analyzeType("int", int1000, int10000, int100000, file);

    analyzeType("double", double1000, double10000, double100000, file);

    analyzeType("string", string1000, string10000, string100000, file);

    file.close();

    cout << endl;
    cout << "Resultados guardados en resultados.csv" << endl;
}


int main() {

    srand(time(0));

    vector<int> list = {15, 7, 3, 9, 12, 5, 2};
    vector<int> listOriginal = list;

    cout << "Lista original:" << endl;
    print(list);

    //Swap Sort
    list = listOriginal;
    long long comparaciones = 0;
    long long intercambios = 0;
    swapSort(list, comparaciones, intercambios);
    cout << "Lista ordenada con Swap Sort:" << endl;
    print(list);

    cout << "Comparaciones: " << comparaciones << endl;
    cout << "Intercambios: " << intercambios << endl;

    //Bubble Sort
    list = listOriginal;

    comparaciones = 0;
    intercambios = 0;

    bubbleSort(list, comparaciones, intercambios);
    cout << "Lista ordenada con Bubble Sort:" << endl;
    print(list);
    cout << "Comparaciones: " << comparaciones << endl;
    cout << "Intercambios: " << intercambios << endl;

    //Selection Sort
    list = listOriginal;

    comparaciones = 0;
    intercambios = 0;

    selectionSort(list, comparaciones, intercambios);
    cout << "Lista ordenada con Selection Sort:" << endl;
    print(list);
    cout << "Comparaciones: " << comparaciones << endl;
    cout << "Intercambios: " << intercambios << endl;

    //Insertion Sort
    list = listOriginal;

    comparaciones = 0;
    intercambios = 0;

    insertionSort(list, comparaciones, intercambios);
    cout << "Lista ordenada con Insertion Sort:" << endl;
    print(list);
    cout << "Comparaciones: " << comparaciones << endl;
    cout << "Intercambios: " << intercambios << endl;

    //Quick Sort
    list = listOriginal;
    quickSort(list, 0, list.size() - 1);
    cout << "Lista ordenada con Quick Sort:" << endl;
    print(list);

    //Merge Sort
    list = listOriginal;
    mergeSort(list, 0, list.size() - 1);
    cout << "Lista ordenada con Merge Sort:" << endl;
    print(list);

    //Shell Sort
    list = listOriginal;
    shellSort(list);
    cout << "Lista ordenada con Shell Sort:" << endl;
    print(list);


    //AGREGADO: listas que se crean desde el menu
    vector<int> intList;
    vector<double> doubleList;
    vector<string> stringList;

    int type = 0;
    int option = -1;


    //Menu
    while (option != 0) {

        cout << endl;
        cout << "-----------------------------" << endl;
        cout << "       SORT ALGORITHMS       " << endl;
        cout << "-----------------------------" << endl;

        cout << "1. Crear lista" << endl;
        cout << "2. Ordenar lista" << endl;
        cout << "3. Analisis comparativo" << endl;
        cout << "0. Salir" << endl;

        cout << "Selecciona una opcion: ";
        cin >> option;


        if (option == 1) {

            cout << endl;
            cout << "Tipo de dato:" << endl;
            cout << "1. int" << endl;
            cout << "2. double" << endl;
            cout << "3. string" << endl;

            cout << "Selecciona: ";
            cin >> type;

            cout << endl;
            cout << "Cantidad de datos:" << endl;
            cout << "1. 1000" << endl;
            cout << "2. 10000" << endl;
            cout << "3. 100000" << endl;

            int sizeOption;
            int size;

            cout << "Selecciona: ";
            cin >> sizeOption;

            if (sizeOption == 1) {
                size = 1000;
            }
            else if (sizeOption == 2) {
                size = 10000;
            }
            else if (sizeOption == 3) {
                size = 100000;
            }
            else {
                cout << "Opcion invalida" << endl;
                continue;
            }


            if (type == 1) {

                intList = createIntList(size);

                cout << "Lista de int creada correctamente." << endl;
            }

            else if (type == 2) {

                doubleList = createDoubleList(size);

                cout << "Lista de double creada correctamente." << endl;
            }

            else if (type == 3) {

                stringList = createStringList(size);

                cout << "Lista de string creada correctamente." << endl;
            }

            else {

                cout << "Tipo invalido" << endl;
                type = 0;
            }
        }


        else if (option == 2) {

            if (type == 0) {

                cout << "Primero debes crear una lista." << endl;
                continue;
            }

            cout << endl;
            cout << "1. Swap Sort" << endl;
            cout << "2. Bubble Sort" << endl;
            cout << "3. Selection Sort" << endl;
            cout << "4. Insertion Sort" << endl;
            cout << "5. Merge Sort" << endl;
            cout << "6. Quick Sort" << endl;
            cout << "7. Shell Sort" << endl;

            int algorithm;

            cout << "Selecciona un algoritmo: ";
            cin >> algorithm;


            if (algorithm < 1 || algorithm > 7) {

                cout << "Algoritmo invalido." << endl;
                continue;
            }


            if (type == 1) {

                runSort(intList, algorithm);
            }

            else if (type == 2) {

                runSort(doubleList, algorithm);
            }

            else if (type == 3) {

                runSort(stringList, algorithm);
            }
        }


        else if (option == 3) {

            comparativeAnalysis();
        }


        else if (option == 0) {

            cout << "Programa terminado." << endl;
        }


        else {

            cout << "Opcion invalida." << endl;
        }
    }

    return 0;
}