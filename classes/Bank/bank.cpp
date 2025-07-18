#include "bank.h"
#include <cstdlib>
#include <fstream>
#include <iomanip>
using namespace std;
Bank::Bank()
{
    updateVector();
    cout << "Bank created" << endl;
};
Bank::~Bank()
{
    deallocateAccounts();
    cout << "Bank destroyed" << endl;
}
void Bank::deallocateAccounts()
{
    for (size_t i = 0; i < accounts.size(); i++)
    {
        delete accounts[i];
        accounts[i] = nullptr;
    }
    accounts.clear();
}

void Bank::updateVector()
{
    deallocateAccounts();
    ifstream file("Accounts.txt");
    int account_number;
    string account_name, user_address;
    double balance;
    char type;
    while (file >> account_number >> account_name >> user_address >> balance >> type)
    {
        Account *account = new Account(account_name, user_address, account_number, balance, type == 'T');
        accounts.push_back(account);
    }
    file.close();
}

void Bank::updateFile()
{
    ofstream file("Accounts.txt");
    for (int i = 0; i < accounts.size(); i++)
    {
        file << accounts[i]->get_account_number() << " "
             << accounts[i]->get_account_name() << " "
             << accounts[i]->get_address() << " "
             << accounts[i]->get_balance() << " "
             << accounts[i]->get_type() << endl;
    }
    file.close();
}
void Bank::addAccount()
{
    string account_name, user_address;
    cout << "\n"
         << string(40, '=') << endl;
    cout << "Add New Account" << endl;
    cout << string(40, '=') << endl;
    cout << left << setw(20) << "Enter user's name: ";
    cin >> account_name;
    cout << left << setw(20) << "Enter user's address: ";
    cin >> user_address;
    int account_number = rand() % 10000;
    Account *account = new Account(account_name, user_address, account_number);
    accounts.push_back(account);
    ofstream file("Accounts.txt", ios::app);
    file << "\n"
         << account_number << " " << account_name << " " << user_address << " " << 0 << " T";
    file.close();
    cout << left << setw(30) << "Account added successfully!" << endl;
    cout << string(40, '=') << "\n";
}

void Bank::viewAccount()
{
    updateVector();
    int accNo;
    cout << "\n"
         << string(40, '=') << endl;
    cout << "View Account" << endl;
    cout << string(40, '=') << endl;
    cout << left << setw(25) << "Enter account number: ";
    if (!(cin >> accNo))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << left << setw(30) << "Invalid input. Please enter a valid account number." << endl;
        return;
    }
    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i]->get_account_number() == accNo)
        {
            accounts[i]->display();
            return;
        }
    }
    cout << left << setw(30) << ("Account " + to_string(accNo) + " not found") << endl;
    cout << string(40, '=') << "\n";
}

void Bank::depositToAccount()
{
    updateVector();
    int accNo;
    cout << "\n"
         << string(40, '=') << endl;
    cout << "Deposit to Account" << endl;
    cout << string(40, '=') << endl;
    cout << left << setw(25) << "Enter account number: ";
    if (!(cin >> accNo))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << left << setw(30) << "Invalid input. Please enter a valid account number." << endl;
        return;
    }
    double amount;
    cout << left << setw(25) << "Enter amount to deposit: ";
    if (!(cin >> amount))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << left << setw(30) << "Invalid input. Please enter a valid amount." << endl;
        return;
    }
    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i]->get_account_number() == accNo)
        {
            accounts[i]->deposit(amount);
            updateFile();
            cout << left << setw(30) << "Deposit successful!" << endl;
            cout << string(40, '=') << "\n";
            return;
        }
    }
    cout << left << setw(30) << ("Account " + to_string(accNo) + " not found") << endl;
    cout << string(40, '=') << "\n";
}

void Bank::withdrawFromAccount()
{
    updateVector();
    int accNo;
    cout << "\n"
         << string(40, '=') << endl;
    cout << "Withdraw from Account" << endl;
    cout << string(40, '=') << endl;
    cout << left << setw(25) << "Enter account number: ";
    if (!(cin >> accNo))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << left << setw(30) << "Invalid input. Please enter a valid account number." << endl;
        return;
    }
    double amount;
    cout << left << setw(25) << "Enter amount to withdraw: ";
    if (!(cin >> amount))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << left << setw(30) << "Invalid input. Please enter a valid amount." << endl;
        return;
    }
    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i]->get_account_number() == accNo)
        {
            accounts[i]->withdraw(amount);
            updateFile();
            cout << left << setw(30) << "Withdrawal successful!" << endl;
            cout << string(40, '=') << "\n";
            return;
        }
    }
    cout << left << setw(30) << ("Account " + to_string(accNo) + " not found") << endl;
    cout << string(40, '=') << "\n";
}
void Bank::deleteAccount()
{
    updateVector();
    int accNo;
    cout << "\n"
         << string(40, '=') << endl;
    cout << "Delete Account" << endl;
    cout << string(40, '=') << endl;
    cout << left << setw(25) << "Enter account number: ";
    if (!(cin >> accNo))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << left << setw(30) << "Invalid input. Please enter a valid account number." << endl;
        return;
    }
    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i]->get_account_number() == accNo)
        {
            accounts[i]->deactivate();
            updateFile();
            cout << left << setw(30) << ("Account " + to_string(accNo) + " deleted") << endl;
            cout << string(40, '=') << "\n";
            return;
        }
    }
    cout << left << setw(30) << ("Account " + to_string(accNo) + " not found") << endl;
    cout << string(40, '=') << "\n";
}
void Bank::listAllAccounts()
{
    updateVector();
    cout << endl;
    cout << string(70, '=') << endl;
    cout << left << setw(12) << "No"
         << setw(20) << "Name"
         << setw(25) << "Address"
         << setw(12) << "Balance"
         << setw(10) << "Status" << endl;
    cout << string(70, '-') << endl;
    for (int i = 0; i < accounts.size(); i++)
    {
        cout << left << setw(12) << accounts[i]->get_account_number()
             << setw(20) << accounts[i]->get_account_name()
             << setw(25) << accounts[i]->get_address()
             << setw(12) << fixed << setprecision(2) << accounts[i]->get_balance()
             << setw(10) << (accounts[i]->get_type() == 'T' ? "Active" : "Inactive") << endl;
    }
    cout << string(70, '=') << endl;
}

void Bank::updateAccount()
{
    updateVector();
    int accNo;
    cout << "\n"
         << string(40, '=') << endl;
    cout << "Update Account" << endl;
    cout << string(40, '=') << endl;
    cout << left << setw(25) << "Enter account number: ";
    if (!(cin >> accNo))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << left << setw(30) << "Invalid input. Please enter a valid account number." << endl;
        return;
    }
    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i]->get_account_number() == accNo)
        {
            accounts[i]->display();
            string account_name, user_address;
            cout << left << setw(25) << "Enter new account name: ";
            cin >> account_name;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << left << setw(30) << "Invalid input. Please enter a valid account name." << endl;
                return;
            }
            cout << left << setw(25) << "Enter new account address: ";
            cin >> user_address;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << left << setw(30) << "Invalid input. Please enter a valid account address." << endl;
                return;
            }
            accounts[i]->set_account_name(account_name);
            accounts[i]->set_address(user_address);
            updateFile();
            cout << left << setw(30) << ("Account " + to_string(accNo) + " was updated") << endl;
            cout << string(40, '=') << "\n";
            return;
        }
    }
    cout << left << setw(30) << "Account not found" << endl;
    cout << string(40, '=') << "\n";
}
