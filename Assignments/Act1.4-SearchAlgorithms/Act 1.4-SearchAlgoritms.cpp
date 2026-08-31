// Isis Krystal Agramón Leal
// A00843802

#include <iostream>
#include <chrono>
using namespace std;

//Búsqueda secuencial
int seqSearch(vector<int> &list, int data) {
    for (int i=0; i<list.size(); i++) {
        if (list[i] == data) {
            return i;
        }
    }
    throw out_of_range("no se encontró el valor");
}

//Búsqueda binaria (La lista ya esta ordenada)
template <typename T>
int binarySearch(vector<T> &list, T data) {
    // obtenemos left
    int left = 0;
    // obtenemos right
    int right = list.size() - 1;
    // buscamos el elemento mientras left <= right
    while (left <= right) {
        // obtenemos la mitad
        int mid = (left + right) / 2;
        // comparamos el valor buscado con el valor de la mitad
        if (data == list[mid]) {
            // regresamos el valor de mid que es el índice del valor encontrado
            return mid;
        } else {
            // preguntamos si el valor buscado es menor que el valor de mid
            if (data < list[mid]) {
                // si es menor
                right = mid - 1;
            } else {
                // es mayor
                left = mid + 1;
            }
        }
    }

    // no lo encontramos
    throw out_of_range("No se encontró el valor");
}

int main() {

    vector<int> list;

    // Creamos 10,000 números aleatorios entre 1 y 1,000,000
    for (int i = 0; i < 10000; i++) {
        list.push_back(rand() % 1000000 + 1);
    }

    // Ordenamos el vector
    sort(list.begin(), list.end());
    

    int data;

    cout << "Ingresa un numero entre 1 y 1000000" << endl;
    cout << "Ingresa 0 para terminar" << endl;
    cin >> data;

    while (data != 0) {

        // Búsqueda secuencial
        auto inicioSeq = chrono::high_resolution_clock::now();

        try {
            int index = seqSearch(list, data);
            cout << "Busqueda secuencial: el valor se encuentra en: "
                 << index << endl;
        } catch (const out_of_range &e) {
            cout << "Busqueda secuencial: " << e.what() << endl;
        }

        auto finSeq = chrono::high_resolution_clock::now();

        auto tiempoSeq =
            chrono::duration_cast<chrono::nanoseconds>(finSeq - inicioSeq);

        // Búsqueda binaria
        auto inicioBin = chrono::high_resolution_clock::now();

        try {
            int index = binarySearch(list, data);
            cout << "Busqueda binaria: el valor se encuentra en: "
                 << index << endl;
        } catch (const out_of_range &e) {
            cout << "Busqueda binaria: " << e.what() << endl;
        }

        auto finBin = chrono::high_resolution_clock::now();

        auto tiempoBin =
            chrono::duration_cast<chrono::nanoseconds>(finBin - inicioBin);

        cout << "Tiempo busqueda secuencial: "
             << tiempoSeq.count() << " nanosegundos" << endl;

        cout << "Tiempo busqueda binaria: "
             << tiempoBin.count() << " nanosegundos" << endl;

        cout << endl;
        cout << "Ingresa otro numero o 0 para terminar: ";
        cin >> data;
    }

    return 0;
}