#ifndef BANK_H
#define BANK_H
#include <vector>
#include "../Account/account.h"

class Bank
{
private:
    vector<Account *> accounts;

public:
    Bank();
    ~Bank();

    void deallocateAccounts();
    void updateVector();
    void updateFile();
    void addAccount();
    void viewAccount();
    void depositToAccount();
    void withdrawFromAccount();
    void deleteAccount();
    void listAllAccounts();
    void updateAccount();
};
#endif