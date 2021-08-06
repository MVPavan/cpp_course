//
// Created by jmuppave on 8/6/2021.
//
#include <string>

#include "TrustAccount.h"

int get_current_year(){
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return 1900+ltm->tm_year;
}

TrustAccount::TrustAccount(std::string name, double balance, double int_rate)
    : SavingsAccount(name, balance, int_rate){

}

bool TrustAccount::deposit(double amount) {
    if(amount>=deposit_bonus_threshold){amount += deposit_bonus;}
    return SavingsAccount::deposit(amount);
}

bool TrustAccount::withdraw(double amount) {
    int temp_year = get_current_year();
    if(current_year!= temp_year){
        current_year=temp_year;
        withdrawl_count = 0;
    }
    if(withdrawl_count < allowed_num_of_withdrawls){
        if(amount < max_withdrawl_percent*get_balance()){
            withdrawl_count += 1;
            return SavingsAccount::withdraw(amount);
        } else{
            std::cout << "TrustAccount withdraw amount should be less than "
            << max_withdrawl_percent*100 << "% of balance" << std::endl;
        }
    } else{
        std::cout  << "Exceeded allowed number of withdrawls: "
        << allowed_num_of_withdrawls << " in an year for Trust Account!"
        << std::endl;
    }
    return false;
}

std::ostream &operator<<(std::ostream &os, const TrustAccount &account) {
    os << "[TrustAccount: " << account.name << ": " << account.balance << ", " << account.int_rate << "%]";
    return os;
}