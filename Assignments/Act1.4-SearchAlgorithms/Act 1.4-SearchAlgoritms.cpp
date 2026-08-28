// Isis Krystal Agramón Leal
// A00843802

#include<iostream>
using namespace std;

//Busqueda secuencial
int seqSearch(vector<int> &list , int data){
    for (int i=0; i<list.size();i++){
        if (list[i] = data) {
            return i;
        }
    }
    throw out_of_range("no se encontró el valor");
}

//Busqueda binaria 
template <typename T>
int binarysearch(vector <int> &list, int data) {
    //obtenemos left
    int left =0;
    //obtenemos right
    int right = list.size()-1;
    //buscamos el elemento mientras left <= right
    while (left<=right){
        //obtenemos la mitad
        int mid = (left +right) /2;
        //comprarmos el valor buscado con el valor de la mitad
        if(data==list[mid]){
            //regresmos el valor de mid que es el índice del valor de la mitad
            return mid;
        }else{
            //preguntamos si el valor buscado es menor que el balor de mid
            if(data< list[mid]){
                //si es menor
                right = mid +1;
            } else{
                //es mayor
                left = mid +1
            }
            
        }
        
        

    }
}

int main() {
    vector<int> list{3, 5, 6, 8, 11, 12, 13, 16, 27, 35};
    cout << "El valor se encuentra en: " << index << endl;
} catch (const)

}