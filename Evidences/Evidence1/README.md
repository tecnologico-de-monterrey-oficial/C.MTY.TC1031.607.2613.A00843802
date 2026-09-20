//Evidencia 1 - Conceptos básicos y algoritmos fundamentales

//Descripción

//Este programa permite leer registros de logs desde un archivo, ordenarlos cronológicamente utilizando diferentes algoritmos de ordenamiento y realizar búsquedas por rangos de fecha y hora. También permite comparar el tiempo de ejecución de los algoritmos utilizando archivos con diferente orden inicial.

//Algoritmos implementados

//Swap Sort
//Bubble Sort
//Selection Sort
//Insertion Sort
//Quick Sort
//Merge Sort
//Shell Sort

//Archivos utilizados

//El programa trabaja con los siguientes archivos de entrada:

//`data/log607-1.txt`: registros desordenados.
//`data/log607-2.txt`: registros casi ordenados.

//Durante la ejecución se generan los siguientes archivos:

//`output608.txt`: contiene los registros ordenados de la ejecución más reciente.
//`range607.txt`: contiene los registros encontrados dentro del rango de fechas seleccionado.
//`resultados.txt`: guarda los resultados de las ejecuciones, incluyendo algoritmo, archivo, cantidad de registros, tiempo y complejidad.

//Compilación y ejecución

//Para compilar el programa:

```powershell
g++ evidencia.cpp -o evidencia 
```

//Búsqueda por rango

//Después de ordenar los registros, el programa permite ingresar una fecha y hora inicial y una fecha y hora final. La búsqueda utiliza una estrategia basada en búsqueda binaria para encontrar los límites del rango.

//Si existen varios registros con la misma fecha y hora en los límites, se incluyen todos los registros correspondientes para evitar perder datos.

//Video de demostración

Link del video: https://www.youtube.com/watch?v=pP2mO_4JlKA