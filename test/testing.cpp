
/*
VS code for some reason doesnt have a configuration to link the cpp file to the header file automatically
so to avoid the overhead of manually linking the header file to the cpp file,
I'm just going to include the whole code in one file and compile all at once.
*/

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <ctime>
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
    Account(string account_name, string user_address, int account_number, double balance = 0, bool is_active = true)
        : name(account_name), address(user_address), number(account_number), balance(balance), is_active(is_active) {}

    ~Account()
    {
        cout << number << " Account destructor called\n";
    }

    void deposit(double amount)
    {
        if (!is_active)
        {
            cout << "Account is not active\n";
            return;
        }
        if (amount <= 0)
        {
            cout << "Amount must be greater than 0\n";
            return;
        }
        balance += amount;
        cout << "Deposited to account " << number << " successfully" << endl;
    }

    void withdraw(double amount)
    {
        if (!is_active)
        {
            cout << "Account is not active\n";
            return;
        }
        if (amount <= 0)
        {
            cout << "Amount must be greater than 0\n";
            return;
        }
        if (amount > balance)
        {
            cout << "Insufficient balance\n";
            return;
        }
        balance -= amount;
        cout << "Withdrawn from account " << number << " successfully" << endl;
    }

    void display() const
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

    int get_account_number() const { return number; }
    void set_account_number(int account_number) { number = account_number; }

    string get_address() const { return address; }
    void set_address(string addr) { address = addr; }

    string get_account_name() const { return name; }
    void set_account_name(string account_name) { name = account_name; }

    double get_balance() const { return balance; }

    void deactivate()
    {
        if (!is_active)
        {
            cout << "Account is already inactive\n";
            return;
        }
        is_active = false;
    }

    char get_type() const
    {
        return is_active ? 'T' : 'F';
    }
};

class Bank
{
private:
    vector<Account *> accounts;

public:
    Bank()
    {
        // updateVector();
        cout << "Bank created" << endl;
    }

    ~Bank()
    {
        deallocateAccounts();
        cout << "Bank destroyed" << endl;
    }

    void deallocateAccounts()
    {
        for (size_t i = 0; i < accounts.size(); i++)
        {
            delete accounts[i];
            accounts[i] = nullptr;
        }
        accounts.clear();
    }

    void updateVector()
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

    void updateFile()
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

    void addAccount()
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

    void viewAccount()
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

    void depositToAccount()
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

    void withdrawFromAccount()
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

    void deleteAccount()
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

    void listAllAccounts()
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

    void updateAccount()
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
};

// void mainFlow()
// {
//     int choice;
//     while (true)
//     {
//         cout << "1. Add account" << endl;
//         cout << "2. View account" << endl;
//         cout << "3. Update account" << endl;
//         cout << "4. Delete account" << endl;
//         cout << "5. List all accounts" << endl;
//         cout << "6. Deposit to account" << endl;
//         cout << "7. Withdraw from account" << endl;
//         cout << "8. Exit" << endl;
//         cout << "Enter your choice: ";
//         cin >> choice;
//         if (cin.fail())
//         {
//             cin.clear();
//             cin.ignore(10000, '\n');
//             cout << "Invalid input. Please enter a valid choice." << endl;
//             continue;
//         }
//         if (choice == 1)
//             cout << choice;
//         else if (choice == 2)
//             cout << choice;
//         else if (choice == 3)
//             cout << choice;
//         else if (choice == 4)
//             cout << choice;
//         else if (choice == 5)
//             cout << choice;
//         else if (choice == 6)
//             cout << choice;
//         else if (choice == 7)
//             cout << choice;
//         else if (choice == 8)
//             break;
//         else
//             cout << "Invalid choice" << endl;
//     }
// }

void mainFlow(Bank &myBank)
{
    int choice;
    while (true)
    {
        cout << "\n"
             << string(40, '=') << endl;
        cout << "         Bank System Menu         " << endl;
        cout << string(40, '=') << endl;
        cout << left << setw(3) << "1." << "Add account" << endl;
        cout << left << setw(3) << "2." << "View account" << endl;
        cout << left << setw(3) << "3." << "Update account" << endl;
        cout << left << setw(3) << "4." << "Delete account" << endl;
        cout << left << setw(3) << "5." << "List all accounts" << endl;
        cout << left << setw(3) << "6." << "Deposit to account" << endl;
        cout << left << setw(3) << "7." << "Withdraw from account" << endl;
        cout << left << setw(3) << "8." << "Exit" << endl;
        cout << string(40, '-') << endl;
        cout << left << setw(25) << "Enter your choice: ";
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << left << setw(30) << "Invalid input. Please enter a valid choice." << endl;
            continue;
        }
        if (choice == 1)
            myBank.addAccount();
        else if (choice == 2)
            myBank.viewAccount();
        else if (choice == 3)
            myBank.updateAccount();
        else if (choice == 4)
            myBank.deleteAccount();
        else if (choice == 5)
            myBank.listAllAccounts();
        else if (choice == 6)
            myBank.depositToAccount();
        else if (choice == 7)
            myBank.withdrawFromAccount();
        else if (choice == 8)
            break;
        else
            cout << left << setw(30) << "Invalid choice" << endl;
    }
}

int main()
{
    srand(time(0)); // Seed the random number generator
    Bank myBank;
    mainFlow(myBank);
    myBank.deallocateAccounts();
    // mainFlow();
    return 0;
}
