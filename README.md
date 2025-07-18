## Bank Management System (C++ Console App)

A simple console-based bank management system written in C++ using object-oriented programming. It allows users to manage bank accounts with file-based persistence.

### Features
- Create, view, update, and deactivate accounts  
- Deposit and withdraw funds  
- List all accounts in a formatted table  
- Data saved to and loaded from `Accounts.txt`  

All code is in one `.cpp` file to avoid header linking issues in some IDEs like VS Code.

### Notes
- Accounts are stored in `Accounts.txt`  
- Inactive accounts remain in the file  
- Input validation and formatting included

### Next Steps
- Replace raw pointers with smart pointers (`std::unique_ptr`) for safer memory management  
- Add transaction history tracking for each account  
- Implement password protection or user authentication  
- Improve file structure and add logging for system events  
- Add support for saving data in other formats (CSV or JSON)
