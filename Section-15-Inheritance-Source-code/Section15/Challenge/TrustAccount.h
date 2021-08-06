//
// Created by jmuppave on 8/6/2021.
//

#ifndef UDEMY_TRUSTACCOUNT_H
#define UDEMY_TRUSTACCOUNT_H

#include <iostream>
#include <string>
#include <ctime>

#include "SavingsAccount.h"

int get_current_year();

class TrustAccount: public SavingsAccount{
    friend std::ostream &operator<<(std::ostream &os, const TrustAccount &account);

private:
    static constexpr const char *def_name = "Unnamed Trust Account";
    static constexpr double def_balance = 0.0;
    static constexpr double def_int_rate = 0.0;

    int current_year = 2021;
    int withdrawl_count = 0;
protected:
    const double deposit_bonus_threshold = 3000;
    const double deposit_bonus = 50;
    const int allowed_num_of_withdrawls = 3;
    const double max_withdrawl_percent = 0.2;  // percentage w.r.t balance
public:
    explicit TrustAccount(std::string name = def_name, double balance = def_balance, double int_rate = def_int_rate);
    bool deposit(double amount);
    bool withdraw(double amount);
};

#endif //UDEMY_TRUSTACCOUNT_H
