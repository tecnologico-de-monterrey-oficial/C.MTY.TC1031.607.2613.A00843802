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