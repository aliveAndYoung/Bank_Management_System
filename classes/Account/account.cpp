#include "account.h"
#include <iomanip>
using namespace std;
Account::Account(string account_name, string user_address, int account_number, double balance, bool is_active)
    : name(account_name), address(user_address), number(account_number), balance(balance), is_active(is_active) {};

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
    cout << "Deposited to account " << this->number << " successfully" << endl;
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
    if (amount > balance)
    {
        cout << "Insufficient balance\n";
        return;
    }
    this->balance -= amount;
    cout << "Withdrawn from account " << this->number << " successfully" << endl;
}
char Account::get_type() const
{
    return this->is_active ? 'T' : 'F';
}

void Account::display() const
{
    cout << "\n-------------------------------\n";
    cout << "      Account Information      \n";
    cout << "-------------------------------\n";
    cout << left << setw(15) << "Number:" << number << endl;
    cout << left << setw(15) << "Name:" << name << endl;
    cout << left << setw(15) << "Address:" << address << endl;
    cout << left << setw(15) << "Balance:" << fixed << setprecision(2) << balance << endl;
    cout << left << setw(15) << "Status:" << (is_active ? "Active" : "Inactive") << endl;
    cout << "-------------------------------\n";
}