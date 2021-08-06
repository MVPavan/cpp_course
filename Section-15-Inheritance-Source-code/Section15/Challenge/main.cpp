// Section 15
// Challenge 
#include <iostream>
#include <vector>
#include "SavingsAccount.h"
#include "Account_Util.h"

#include <ctime>

using namespace std;

int main() {
    cout.precision(2);
    cout << fixed;
   
    // Accounts
    vector<Account> accounts;
    accounts.push_back(Account {});
    accounts.push_back(Account {"Larry"});
    accounts.push_back(Account {"Moe", 2000} );
    accounts.push_back(Account {"Curly", 5000} );
    
    display(accounts);
    deposit(accounts, 1000);
    withdraw(accounts,2000);
    
    // Savings 

    vector<SavingsAccount> sav_accounts;
    sav_accounts.push_back(SavingsAccount {} );
    sav_accounts.push_back(SavingsAccount {"Superman"} );
    sav_accounts.push_back(SavingsAccount {"Batman", 2000} );
    sav_accounts.push_back(SavingsAccount {"Wonderwoman", 5000, 5.0} );

    display(sav_accounts);
    deposit(sav_accounts, 1000);
    withdraw(sav_accounts, 2000);

    // Checking Accounts
    vector<CheckingAccount> check_accounts;
    check_accounts.push_back(CheckingAccount {});
    check_accounts.push_back(CheckingAccount {"Larry1"});
    check_accounts.push_back(CheckingAccount {"Moe1", 2000} );
    check_accounts.push_back(CheckingAccount {"Curly1", 5000} );

    display(check_accounts);
    deposit(check_accounts, 1000);
    withdraw(check_accounts,2000);

    // Trust Accounts
    vector<TrustAccount> trust_accounts;
    trust_accounts.push_back(TrustAccount {});
    trust_accounts.push_back(TrustAccount {"Superman1"} );
    trust_accounts.push_back(TrustAccount {"Batman1", 2000} );
    trust_accounts.push_back(TrustAccount {"Wonderwoman1", 5000, 5.0} );

    display(trust_accounts);
    deposit(trust_accounts, 1000);
    withdraw(trust_accounts,2000);
    withdraw(trust_accounts,1000);

    return 0;
}

