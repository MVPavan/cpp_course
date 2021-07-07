// Section 14
// Challenge
#include <iostream>
//#include "Section-14-Operator-Overloading-Source-code/Section14/Challenge/Mystring.h"
//#include "Section-14-Operator-Overloading-Source-code/Section14/Challenge/Mystring.cpp"
#include "Section-14-Operator-Overloading-Source-code/Section14/Challenge2/Mystring.cpp"

//#include "Section-14-Operator-Overloading-Source-code/Section14/Challenge-Solution1/Mystring.h"
//#include "Section-14-Operator-Overloading-Source-code/Section14/Challenge-Solution1/Mystring.cpp"

using namespace std;

int main() {

    cout << boolalpha << endl;
    Mystring a {"frank"};
    Mystring b {"frank"};

    cout << (a==b) << endl;         // true
    cout << (a!=b) << endl;          // false

    b = "george";
    cout << (a==b) << endl;         // false
    cout << (a!=b) << endl;          // true
    cout << (a<b) << endl;          // true
    cout << (a>b) << endl;           // false

    Mystring s1 {"FRANK"};
    s1 = -s1;
    cout << s1 << endl;               // frank

    s1 = s1 + "*****";
    cout << s1 << endl;               // frank*****

    s1 += "-----";                        // frank*****-----
    cout << s1 << endl;

    Mystring s2{"12345--"};
    s1 = s2 * 7;
    cout << s1 << endl;              // 123451234512345

    Mystring s3{"abcdef--"};
    s3 *= 5;
    cout << s3 << endl;             // abcdefabcdefabcdefabcdefabcdef

    Mystring s = "Frank";
    ++s;
    cout << s << endl;                  // FRANK
    cout << "-------" << endl;
    s = -s;
    cout << s << endl;                  // frank

    Mystring result;
    result = ++s;
    cout << s << endl;                  // FRANK
    cout << result << endl;           // FRANK

    s = "Frank";
    s++;
    cout << s << endl;                  // FRANK
    cout << "-------" << endl;
    s = -s;
    cout << s << endl;                  // frank
    result = s++;
    cout << s << endl;                  // FRANK
    cout << result << endl;           // frank

    return 0;
}

