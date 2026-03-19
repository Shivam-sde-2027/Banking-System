🏦 Banking System (C++ | OOP-Based Project)

A console-based Banking System implemented in C++ demonstrating core Object-Oriented Programming (OOP) principles along with basic security and data privacy features.

🚀 Features

Create Savings Account and Current Account
Deposit, Withdraw, and Transfer money
Check account balance
View detailed account information
Maintain transaction history
Display all accounts
PIN-based authentication for secure access
Masked account numbers to protect sensitive data
Robust exception handling

🔐 Security & Privacy Features

🔒 PIN Authentication
Each account is protected by a user-defined PIN required for all operations

🔐 Account Number Masking
Only last 4 digits are visible (e.g., ****1001)

🛡️ Safe Logging
Sensitive information like full account numbers is never displayed in outputs

🧠 OOP Concepts Used

Encapsulation
Private balance and PIN with controlled access

Abstraction
Abstract base class BankAccount with pure virtual withdraw()

Inheritance
SavingsAccount and CurrentAccount extend BankAccount

Polymorphism
Runtime method overriding (withdraw(), displayInfo())

💼 Account Types
🟢 Savings Account

Minimum balance must be maintained (Rs. 500)
Prevents withdrawal below minimum balance

🔵 Current Account

Supports overdraft facility
Allows negative balance up to a predefined limit

⚠️ Exception Handling

Custom exceptions implemented:

InsufficientFundsException
InvalidAmountException
AccountNotFoundException
AuthenticationException

🛠️ Technologies Used

C++ (C++17)
STL (vector, unordered_map)
Smart Pointers (unique_ptr)
CLI (Command Line Interface)

📂 Project Structure
BankingSystem/
│
├── main.cpp
├── Bank.h
├── BankAccount.h
├── Exceptions.h
└── README.md

▶️ How to Run
1. Compile
g++ -std=c++17 main.cpp -o main
2. Run
./main

🎬 Demo Flow

Create accounts (Savings / Current)
Perform deposit, withdrawal, and transfer
Enter PIN for authentication during operations
View masked account details
Check transaction history
Attempt wrong PIN → access denied

🎯 Key Highlights

Clean modular design using OOP principles
Secure handling of sensitive data (PIN + masking)
Memory-safe implementation using smart pointers
Scalable architecture (easy to extend with new account types)
Interview-ready project demonstrating real-world system design

🔮 Future Enhancements

File/database storage for persistence
GUI-based application (Qt / Web Interface)
Multi-threading for concurrent transactions

Encryption for sensitive data
