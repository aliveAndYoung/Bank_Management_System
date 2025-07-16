#include "account.h"
using namespace std;
Account::Account(string account_name, string user_address, int account_number)
    : name(account_name), address(user_address), number(account_number) {};

Account::~Account() { cout << this->number << "Account destructor called \n"; };

int Account::get_account_number() const
{
    return this->number;
}
void Account::set_account_number(int account_number)
{
    this->number = account_number;
}

string Account::get_address() const
{
    return this->address;
}
void Account::set_address(string address)
{
    this->address = address;
}

string Account::get_account_name() const
{
    return this->name;
}
void Account::set_account_name(string account_name)
{
    this->name = account_name;
}

double Account::get_balance() const
{
    return this->balance;
}

void Account::deactivate()
{
    if (!this->is_active)
    {
        cout << "Account is already inactive \n";
        return;
    }
    this->is_active = false;
}

void Account::deposit(double amount)
{
    if (!this->is_active)
    {
        cout << "Account is not active \n";
        return;
    }
    if (amount <= 0)
    {
        cout << "Amount must be greater than 0 \n";
        return;
    }
    this->balance += amount;
}

void Account::withdraw(double amount)
{
    if (!this->is_active)
    {
        cout << "Account is not active \n";
        return;
    }
    if (amount <= 0)
    {
        cout << "Amount must be greater than 0 \n";
        return;
    }
    this->balance -= amount;
}

void Account::display() const
{
    cout << "Account number: " << this->number << endl;
    cout << "Account name: " << this->name << endl;
    cout << "Account address: " << this->address << endl;
    cout << "Account balance: " << this->balance << endl;
}