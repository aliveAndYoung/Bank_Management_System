#include <iostream>
#include "classes/Bank/bank.h"
#include <iomanip>
using namespace std;

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
    Bank myBank;
    mainFlow(myBank);
    myBank.deallocateAccounts();
    return 0;
}
