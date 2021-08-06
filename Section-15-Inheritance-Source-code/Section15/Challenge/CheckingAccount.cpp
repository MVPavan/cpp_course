//
// Created by jmuppave on 8/6/2021.
//

#include <string>
#include "CheckingAccount.h"

CheckingAccount::CheckingAccount(std::string name, double balance)
    : Account(name,balance){
}

bool CheckingAccount::withdraw(double amount) {
    std::cout << "Deducting Checking Account withdraw fee : $1.50" << std::endl;
    amount += 1.5;
    return Account::withdraw(amount);
}


std::ostream &operator<<(std::ostream &os, const CheckingAccount &account) {
    os << "[CheckingAccount: " << account.name << ": " << account.balance << "]";
    return os;
}