
 // Isis Krystal Agramón Leal
// A00843802

#ifndef Log_h
#define Log_h

#include <string>
#include <sstream>
using namespace std;

struct Log {
    int year;
    string month;
    int day;
    string time;
    string ip;
    string message;
    string key;

    Log();
    Log(int _year, string _month, int _day, string _time, string _ip, string _message);
    string createKey();
    bool operator>(const Log &other) const;
    bool operator<(const Log &other) const;
    bool operator==(const Log &other) const;
    bool operator!=(const Log &other) const;
    bool operator>=(const Log &other) const;
    bool operator<=(const Log &other) const;
};

bool Log::operator>(const Log &log1) const {
    return key > log1.key;
}

bool Log::operator<(const Log &log1) const {
    return key < log1.key;
}

bool Log::operator==(const Log &log1) const {
    return key == log1.key;
}

bool Log::operator!=(const Log &log1) const {
    return key != log1.key;
}

bool Log::operator>=(const Log &log1) const {
    return key >= log1.key;
}

bool Log::operator<=(const Log &log1) const {
    return key <= log1.key;
}

string Log::createKey() {
    string monthNumber;
    string dayNumber;
    string timeNumber;
    string ipNumber = "";

    if (month == "Jan"){
        monthNumber = "01";
    }
    else if (month == "Feb"){
        monthNumber = "02";
    }
    else if (month == "Mar"){
        monthNumber = "03";
    }
    else if (month == "Apr"){
        monthNumber = "04";
    }
    else if (month == "May"){
        monthNumber = "05";
    }
    else if (month == "Jun"){
        monthNumber = "06";
    }
    else if (month == "Jul"){
        monthNumber = "07";
    }
    else if (month == "Aug"){
        monthNumber = "08";
    }
    else if (month == "Sep"){
        monthNumber = "09";
    }
    else if (month == "Oct"){
        monthNumber = "10";
    }
    else if (month == "Nov"){
        monthNumber = "11";
    }
    else if (month == "Dec"){
        monthNumber = "12";
    }
    else{
        return "";
    }

    if (day < 10){
        dayNumber = "0" + to_string(day);
    }
    else{
        dayNumber = to_string(day);
    }

    timeNumber = time.substr(0,2) + time.substr(3,2) + time.substr(6,2);

    // separamos los numeros de la IP
    stringstream ss(ip);
    string number;

    for (int i = 0; i < 4; i++){
        getline(ss, number, '.');

        // convertimos el numero a tres digitos
        int octet = stoi(number);
        number = to_string(octet);

        while (number.length() < 3){
            number = "0" + number;
        }

        ipNumber = ipNumber + number;
    }

    // creamos la llave con IP, fecha, hora y mensaje
    key = ipNumber + to_string(year);
    key = key + monthNumber + dayNumber + timeNumber + message;

    return key;
}

Log::Log(){
    year = 0;
    month = "";
    day = 0;
    time = "";
    ip = "";
    message = "";
    key = "";
}

Log::Log(int _year, string _month, int _day, string _time, string _ip, string _message){
    year = _year;
    month = _month;
    day = _day;
    time = _time;
    ip = _ip;
    message = _message;
    key = createKey();
}

#endif
