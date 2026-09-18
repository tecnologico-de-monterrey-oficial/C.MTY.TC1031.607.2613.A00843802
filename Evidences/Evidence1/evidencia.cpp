//Isis Krystal Agramón Leal
//A00843802

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Log.h"

using namespace std;

int main(){
    ifstream file;
    file.open("data/log607-1.txt");

    if (!file.is_open()){
        cout << "Error al abrir el archivo." << endl;
        return 1;
    }
    
    vector<Log> logs;
    string line;
    while(getline(file, line)){
      stringstream ss(line);  

      string month;
      int day;
      string time;
      string ip;
      int year;
      string message;
      ss >> month >> day >> year >> time >> ip;
      getline(ss >> ws, message);
      Log log1(year, month, day, time, ip, message);
      logs.push_back(log1);
      
    }
    
cout << "Total de logs: " << logs.size() << endl;
cout << "Primer log: " << logs[0].key << endl;



    return 0;
}