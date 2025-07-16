#ifndef BANK_H
#define BANK_H
#include <vector>
#include "../Account/account.h"

class Bank
{
private:
    std::vector<Account &> accounts;

public:
    Bank();
    ~Bank();

    // Services
    void addAccount();
    void viewAccount(int accNo);
    void depositToAccount(int accNo, double amount);
    void withdrawFromAccount(int accNo, double amount);
    void deleteAccount(int accNo);
    void listAllAccounts();
};
#endif