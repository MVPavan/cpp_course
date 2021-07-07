#include <iostream>
#include <cstring>
#include "Mystring.h"

// No-args constructor
Mystring::Mystring()
        : str{nullptr} {
    str = new char[1];
    *str = '\0';
}

// Overloaded constructor
Mystring::Mystring(const char *s)
        : str {nullptr} {
    if (s==nullptr) {
        str = new char[1];
        *str = '\0';
    } else {
        str = new char[strlen(s)+1];
        strcpy(str, s);
    }
}

// Copy constructor
Mystring::Mystring(const Mystring &source)
        : str{nullptr} {
    str = new char[strlen(source.str)+ 1];
    strcpy(str, source.str);
    //       std::cout << "Copy constructor used" << std::endl;

}

// Move constructor
Mystring::Mystring( Mystring &&source)
        :str(source.str) {
    source.str = nullptr;
//        std::cout << "Move constructor used" << std::endl;
}

// Destructor
Mystring::~Mystring() {
    delete [] str;
}

// Copy assignment
Mystring &Mystring::operator=(const Mystring &rhs) {
//    std::cout << "Using copy assignment" << std::endl;

    if (this == &rhs)
        return *this;
    delete [] str;
    str = new char[strlen(rhs.str) + 1];
    strcpy(str, rhs.str);
    return *this;
}

// Move assignment
Mystring &Mystring::operator=( Mystring &&rhs) {
    //   std::cout << "Using move assignment" << std::endl;
    if (this == &rhs)
        return *this;
    delete [] str;
    str = rhs.str;
    rhs.str = nullptr;
    return *this;
}


// Display method
void Mystring::display() const {
    std::cout << str << " : " << get_length() << std::endl;
}

// getters
int Mystring::get_length() const { return strlen(str); }
const char *Mystring::get_str() const { return str; }

// overloaded insertion operator
std::ostream &operator<<(std::ostream &os, const Mystring &rhs) {
    os << rhs.str;
    return os;
}

// overloaded extraction operator
std::istream &operator>>(std::istream &in, Mystring &rhs) {
    char *buff = new char[1000];
    in >> buff;
    rhs = Mystring{buff};
    delete [] buff;
    return in;
}



bool operator==(const Mystring &lhs, const Mystring &rhs){
    return (std::strcmp(lhs.str,rhs.str)==0);
}

bool operator!=(const Mystring &lhs, const Mystring &rhs){
    return (std::strcmp(lhs.str,rhs.str)!=0);
}
bool operator<(const Mystring &lhs, const Mystring &rhs){
    return (std::strcmp(lhs.str,rhs.str)<0);
}
bool operator>(const Mystring &lhs, const Mystring &rhs){
    return (std::strcmp(lhs.str,rhs.str)>0);
}

Mystring &operator-(Mystring &lhs){
    for (std::size_t i{0}; i < strlen(lhs.str); i++)
        lhs.str[i] = std::tolower(lhs.str[i]);
    return lhs;
}

Mystring &operator+( Mystring &lhs, const Mystring &rhs) {
    Mystring temp {lhs};
    delete [] lhs.str;
    lhs.str = new char[std::strlen(temp.str) + std::strlen(rhs.str)+1];
    std::strcpy(lhs.str,temp.str);
    std::strcat(lhs.str,rhs.str);
    return lhs;
}


Mystring &operator+=(Mystring &lhs, const Mystring &rhs) {
    return lhs + rhs;
}

Mystring &operator*(Mystring &lhs, int rhs){
    Mystring temp{lhs};
    for(int i{0}; i<rhs-1;i++) {
        lhs += temp;
    }
    return lhs;
}

Mystring &operator*=(Mystring &lhs, int rhs){
    return lhs*rhs;
}

Mystring &operator++( Mystring &lhs){
    for (size_t i{0}; i < std::strlen(lhs.str); i++)
        lhs.str[i] = std::toupper(lhs.str[i]);
    return lhs;
}

Mystring operator++(Mystring &lhs, int rhs){
    Mystring temp{lhs};
    ++lhs;
    return temp;
}