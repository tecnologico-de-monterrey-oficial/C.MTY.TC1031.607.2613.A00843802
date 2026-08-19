// Isis Krystal Agramón Leal
//A00843802

#include <iostream>
using namespace std;

int factorial (int n) {
    if (n <= 1) {
        return 1;
    }
    else {
        return n * factorial(n - 1);
    }
}

int sumIterative(int n) {
    int suma = 0;
    for (int i = 1; i <= n; i++) {
        suma += i;
    }
    return suma;
}

int sumRecursive(int n) {
    if (n == 1) {
        return 1;
    }
    
    return n + sumRecursive(n - 1);
}

int sumFormula(int n){
    return n * (n + 1) / 2;
}

int fibonacciIterative(int n){
    int a=1;
    int b=1;
    int c;
    for(int i=3; i<=n; i++){
        c=a+b;
        a=b;
        b=c;
    }
    return b;
}

int fibonacciRecursive(int n){
    if(n<=2){
        return 1;
    }
    return fibonacciRecursive(n-1)+fibonacciRecursive(n-2);
}

int bacteriasIterative(int n){
    double born = 3.78;
    double died = 2.34;
    int sum = 1;
    for(int i=1; i<=n; i++){
        int bacBorn = sum * born;
        int bacDied = sum * died;
        sum += bacBorn - bacDied;
    }
    return sum;
}


int bacteriasRecursive(int n){
    if(n==0){
        return 1;
    }
    int bacteria = bacteriasRecursive(n-1);
    int born = bacteria * 3.78;
    int died = bacteria * 2.34;
    return bacteria + born - died;
}


float investmentIterative(float n, int meses){
    float inversion = n;
    for(int i = 0; i < meses; i++){
        inversion += inversion * 0.1875;
    }
    return inversion;
}

float investmentRecursive(float cantidad, int meses){
    if(meses == 0){
        return cantidad;
    }

    return investmentRecursive(cantidad + cantidad * 0.1875, meses - 1);
}

int powIterative(int n, int exp){
    int result = 1;
    for(int i = 0; i < exp; i++){
        result *= n;
    }
    return result;
}

int powRecursive(int n, int exp){
    if(exp == 0){
        return 1;
    }
    else{
        return n * powRecursive(n, exp - 1);
    }
}


int main(){


    cout << "El factorial de 5 es: " << factorial(5) << endl;
    //suma Iterativa
    cout << "La suma iterativa de 5 es: " << sumIterative(5) << endl;
    //suma Recursiva
    cout << "La suma recursiva de 5 es: " << sumRecursive(5) << endl;
    //suma Formula
    cout << "La suma con formula de 5 es: " << sumFormula(5) << endl;
    //fibonacci Iterativo
    cout << "El fibonacci iterativo de 8 es: " << fibonacciIterative(8) << endl;
    //fibonacci Recursivo
    cout << "El fibonacci recursivo de 8 es: " << fibonacciRecursive(8) << endl;
    //bacterias Iterativo
    cout << "El numero de bacterias iterativo de 5 es: " << bacteriasIterative(5) << endl;      
    //bacterias Recursivo
    cout << "El numero de bacterias recursivo de 5 es: " << bacteriasRecursive(5) << endl;
    //inversion Iterativa
    cout << "El valor de la inversion iterativa es: "  << investmentIterative(1000, 5) << endl;
    //inversion Recursiva
    cout << "El valor de la inversion recursiva es: " << investmentRecursive(1000, 5) << endl;
    //potencia Iterativa
    cout << "El valor de la potencia iterativa de 2 a la 5 es: " << powIterative(2, 5) << endl;     
    //potencia Recursiva
    cout << "El valor de la potencia recursiva de 2 a la 5 es: " << powRecursive(2, 5) << endl;
    return 0;

}