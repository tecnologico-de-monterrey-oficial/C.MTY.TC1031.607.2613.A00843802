//Isis Krystal Agramón Leal
//A00843802

#include <iostream>
#include <string>
#include "Stack.h"

using namespace std;

struct PaginaWeb {
    string titulo;
    string url;
};

int main() {
    Stack<PaginaWeb> historial;
    int opcion;

    do {
        cout << "\nMENU" << endl;
        cout << "1.Visitar una nueva pagina" << endl;
        cout << "2.Retroceder a la pagina anterior" << endl;
        cout << "3.Ver la pagina actual" << endl;
        cout << "4.Mostrar cuantas paginas hay en el historial" << endl;
        cout << "5.Salir" << endl;
        cout << "Opción: ";
        cin >> opcion;

    if (opcion == 1) {
        PaginaWeb pagina;
        cout << "Titulo de la pagina: ";
        cin >> pagina.titulo;
        cout << "URL de la pagina: ";
        cin >> pagina.url;
        historial.push(pagina);
        cout << "Pagina agregada al historial" << endl;
    }
    else if (opcion == 2) {
        try {
            PaginaWeb pagina = historial.pop();

            cout << "Pagina cerrada: " << pagina.titulo << endl;
            cout << "URL: " << pagina.url << endl;
        }
        catch (out_of_range&) {
            cout << "No hay paginas en el historial" << endl;
        }
    }

    else if (opcion == 3) {
        try {
            PaginaWeb pagina = historial.top();

            cout << "Pagina actual: " << pagina.titulo << endl;
            cout << "URL: " << pagina.url << endl;
        }
        catch (out_of_range&) {
            cout << "No hay paginas en el historial" << endl;
        }
    }

    else if (opcion == 4) {
        cout << "Paginas en el historial: " << historial.getSize() << endl;
    }
    else if (opcion == 5) {
        cout << "Programa terminado" << endl;
    }
    else {
        cout << "Opcion no valida" << endl;
    }

    } while (opcion != 5);

    return 0;
}