//
// Created by jmuppave on 8/6/2021.
//

#ifndef UDEMY_CHECKING_H
#define UDEMY_CHECKING_H
#include <string>
#include <iostream>

#include "Account.h"

class CheckingAccount: public Account{
    friend std::ostream &operator<<(std::ostream &os, const CheckingAccount &account);
private:
    static constexpr const char *def_name = "Unnamed Checking Account";
    static constexpr double def_balance = 0.0;
protected:
    double withdrawl_fee = 1.5;
public:
    explicit CheckingAccount(std::string name = def_name, double balance = def_balance);
    bool withdraw(double amount);
};


#endif //UDEMY_CHECKING_H
