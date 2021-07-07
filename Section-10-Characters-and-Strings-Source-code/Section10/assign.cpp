//
// Created by jmuppave on 6/15/2021.
//

#include <iostream>
#include <string>

using namespace std;

int main() {

    string key {};
    cout << "Enter pyramid key :";
    getline(cin, key);

    string rkey (key.rbegin(), key.rend());

    for (size_t i {0}; i<key.length(); i++){
        string temp (key.length()*2-1, ' ');
        temp.replace(key.length(),i,rkey.substr(rkey.length()-i,rkey.length()));
        temp.replace(key.length()-i,i,key.substr(0,i+1));
        cout << temp << endl;
    }
    cout << endl;
    return 0;
}