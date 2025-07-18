#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
#include <iostream>
using namespace std;

class Account
{
private:
    int number;
    string name;
    string address;
    double balance;
    bool is_active;

public:
    Account(string account_name, string user_address, int account_number, double balance = 0, bool is_active = true);
    ~Account();
    void deposit(double amount);
    void withdraw(double amount);
    void display() const;

    int get_account_number() const;
    void set_account_number(int account_number);

    string get_address() const;
    void set_address(string address);

    string get_account_name() const;
    void set_account_name(string account_name);

    double get_balance() const;

    void deactivate();
    char get_type() const;
};

#endif
