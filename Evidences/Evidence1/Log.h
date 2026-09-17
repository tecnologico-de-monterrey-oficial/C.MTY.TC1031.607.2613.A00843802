// Isis Krystal Agramón Leal
// A00843802

#ifndef Log_h
#define Log_h

struct Log{
    int year;
    string month;
    int day;
    string time;
    string ip;
    string message;
    string key;
    
    Log();
    Log(int year, string month, int day, string time, string ip, string message, string key);
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

bool Log::operator==(const Log&log1) const {
    return key == log1.key;
}

bool Log::operator!=(const Log&log1) const {
    return key != log1.key;
}

bool Log::operator>=(const Log&log1) const{
    return key >= log1.key;
}

bool Log::operator<=(const Log&log1) const {
    return key <= log1.key;
}

string Log::createKey() {
    string monthNumber;
    string dayNumber;
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
}



