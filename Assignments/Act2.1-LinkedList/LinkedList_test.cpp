//Isis Krystal Agramón Leal  
//A00843802 
 
#include <iostream> 
using namespace std; 
 
#include "LinkedList.h" 
 
template <typename T> 
void menu() { 
 
        LinkedList<T> list; 
 
        T dato; 
        int cantidad; 
        int opcion; 
 
        //crear la lista 
        cout << "Cómo quieres crear la lista?" << endl; 
        cout << "1.Capturar los datos" << endl; 
        cout << "2.Datos aleatorios" << endl; 
        cout << "Opción: "; 
        cin >> opcion; 
 
        cout << "Cuántos números quieres agregar? "; 
        cin >> cantidad; 
 
        if (opcion == 1) { 
            for (int i = 0; i < cantidad; i++) { 
                cout << "Escribe un numero: "; 
                cin >> dato; 
                list.addLast(dato); 
            } 
        } 
        else if (opcion == 2) { 
            for (int i = 0; i < cantidad; i++) { 
                dato = rand(); 
                list.addLast(dato); 
            } 
        } 
        cout << "\nLista: "; 
        list.print(); 
 
        do { 
 
            cout << "\n-------- Menú ---------" << endl; 
            cout << "1.Agregar al principio" << endl; 
            cout << "2.Agregar al final" << endl; 
            cout << "3.Insertar despues de un índice" << endl; 
            cout << "4.Borrar un dato" << endl; 
            cout << "5.Borrar por posición" << endl; 
            cout << "6.Obtener dato por posición" << endl; 
            cout << "7.Actualizar un dato" << endl; 
            cout << "8.Actualizar por posición" << endl; 
            cout << "9.Buscar un dato" << endl; 
            cout << "10.Obtener usando []" << endl; 
            cout << "11.Actualizar usando []" << endl; 
            cout << "12.Duplicar lista usando =" << endl; 
            cout << "13.Mostrar lista" << endl; 
            cout << "14.Salir" << endl; 
 
            cout << "Opción: "; 
            cin >> opcion; 
 
            //agregar al principio 
            if (opcion == 1) { 
                cout << "Escribe el número que quieres agregar: "; 
                cin >> dato; 
                list.addFirst(dato); 
                cout << "Lista: "; 
                list.print(); 
            } 
            //agregar al final 
            else if (opcion == 2) { 
                cout << "Escribe el número que quieres agregar: "; 
                cin >> dato; 
                list.addLast(dato); 
                cout << "Lista: "; 
                list.print(); 
            } 
            //insertar despues de un índice 
            else if (opcion == 3) { 
                int index; 
                cout << "En que índice quieres insertar despues? "; 
                cin >> index; 
                cout << "Escribe el número que quieres agregar: "; 
                cin >> dato; 
                try { 
                    list.insert(index, dato); 
                    cout << "Lista: "; 
                    list.print(); 
                } 
                catch (out_of_range& e) { 
                    cout << e.what() << endl; 
                } 
            } 
            //borrar un dato 
            else if (opcion == 4) { 
                cout << "Escribe el número que quieres borrar: "; 
                cin >> dato; 
                if (list.deleteData(dato)) { 
                    cout << "Dato eliminado" << endl; 
                } 
                else { 
                    cout << "El dato no se encontró" << endl; 
                } 
                cout << "Lista: "; 
                list.print(); 
            } 
            //borrar por posicion 
            else if (opcion == 5) { 
                int index; 
                cout << "Escribe el índice que quieres borrar: "; 
                cin >> index; 
                if (list.deleteAt(index)) { 
                    cout << "Dato eliminado" << endl; 
                } 
                else { 
                    cout << "La posición no existe" << endl; 
                } 
                cout << "Lista: "; 
                list.print(); 
            } 
            //obtener dato por posicion 
            else if (opcion == 6) { 
                int index; 
                cout << "Escribe el índice: "; 
                cin >> index; 
                try { 
                    cout << "Dato: " << list.getData(index) << endl; 
                } 
                catch (out_of_range& e) { 
                    cout << e.what() << endl; 
                } 
            } 
            //actualizar un dato 
            else if (opcion == 7) { 
                T nuevoDato; 
                cout << "Escribe el dato que quieres cambiar: "; 
                cin >> dato; 
                cout << "Escribe el nuevo dato: "; 
                cin >> nuevoDato; 
                try { 
                    list.updateData(dato, nuevoDato); 
 
                    cout << "Lista: "; 
                    list.print(); 
                } 
                catch (out_of_range& e) { 
                    cout << e.what() << endl; 
                } 
            } 
 
            //actualizar por posición 
            else if (opcion == 8) { 
                int index; 
                T nuevoDato; 
                cout << "Escribe el índice que quieres cambiar: "; 
                cin >> index; 
                cout << "Escribe el nuevo dato: "; 
                cin >> nuevoDato; 
                try { 
                    list.updateAt(index, nuevoDato); 
 
                    cout << "Lista: "; 
                    list.print(); 
                } 
                catch (out_of_range& e) { 
                    cout << e.what() << endl; 
                } 
            } 
            //buscar un dato 
            else if (opcion == 9) { 
                cout << "Escribe el dato que quieres buscar: "; 
                cin >> dato; 
                int index = list.findData(dato); 
                if (index == -1) { 
                    cout << "El dato no se encontró" << endl; 
                } 
                else { 
                    cout << "El dato esta en el índice: " << index << endl; 
                } 
            } 
            //obtener usando [] 
            else if (opcion == 10) { 
                int index; 
                cout << "Escribe el índice: "; 
                cin >> index; 
                try { 
                    cout << "Dato: " << list[index] << endl; 
                } 
                catch (out_of_range& e) { 
                    cout << e.what() << endl; 
                } 
            } 
            //actualizar usando [] 
            else if (opcion == 11) { 
                int index; 
                T nuevoDato; 
                cout << "Escribe el índice que quieres cambiar: "; 
                cin >> index; 
                cout << "Escribe el nuevo dato: "; 
                cin >> nuevoDato; 
                try { 
                    list[index] = nuevoDato; 
 
                    cout << "Lista: "; 
                    list.print(); 
                } 
                catch (out_of_range& e) { 
                    cout << e.what() << endl; 
                } 
            } 
            //duplicar lista usando = 
            else if (opcion == 12) { 
                LinkedList<T> list2; 
                list2 = list; 
                cout << "Lista original: "; 
                list.print(); 
                cout << "Lista duplicada: "; 
                list2.print(); 
            } 
            //mostrar lista 
            else if (opcion == 13) { 
 
                cout << "Lista: "; 
                list.print(); 
            } 
            //salir 
            else if (opcion == 14) { 
 
                cout << "Programa terminado" << endl; 
            } 
            else { 
                cout << "Opción inválida" << endl; 
            } 
 
        } while (opcion != 14); 
}


int main() {
    int tipo;
    cout << "Qué tipo de lista quieres crear?" << endl;
    cout << "1.Enteros" << endl;
    cout << "2.Caracteres" << endl;
    cout << "Opción: ";
    cin >> tipo;

    if (tipo == 1) {
        menu<int>();
    }
    else if (tipo == 2) {
        menu<char>();
    }
    else {
        cout << "Opcion invalida" << endl;
    }

    return 0;
}