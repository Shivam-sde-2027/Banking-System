#include <iostream>
#include <unordered_map>
#include <memory>
#include <exception>
#include <limits>

using namespace std;

//These are custom exceptions
class BankingException : public exception {
protected:
    string message;
public:
    BankingException(const string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class InsufficientBalanceException : public BankingException {
public:
    InsufficientBalanceException() 
        : BankingException("Insufficient balance") {}
};

class InvalidAmountException : public BankingException {
public:
    InvalidAmountException() 
        : BankingException("Invalid transaction amount") {}
};

class AccountNotFoundException : public BankingException {
public:
    AccountNotFoundException() 
        : BankingException("Account not found") {}
};

//This is interface
class BankOperations {
public:
    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
    virtual double getBalance() const = 0;
    virtual void calculateInterest() = 0;
    virtual ~BankOperations() {}
};

//This is bank account class
class BankAccount : public BankOperations {
protected:
    int accountNumber;
    string holderName;
    double balance;

public:
    BankAccount(int accNo, const string& name, double bal)
        : accountNumber(accNo), holderName(name), balance(bal) {}

    void deposit(double amount) override {
        if (amount <= 0)
            throw InvalidAmountException();
        balance += amount;
    }

    double getBalance() const override {
        return balance;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    virtual void display() const {
        cout << "Account No: " << accountNumber
             << "\nHolder: " << holderName
             << "\nBalance: " << balance << endl;
    }

    virtual ~BankAccount() {}
};

//Saving account class
class SavingsAccount : public BankAccount {
private:
    const double interestRate = 4.0;

public:
    SavingsAccount(int accNo, const string& name, double bal)
        : BankAccount(accNo, name, bal) {}

    void withdraw(double amount) override {
        if (amount <= 0)
            throw InvalidAmountException();
        if (amount > balance)
            throw InsufficientBalanceException();
        balance -= amount;
    }

    void calculateInterest() override {
        double interest = balance * interestRate / 100;
        balance += interest;
    }
};

//current account class
class CurrentAccount : public BankAccount {
private:
    const double overdraftLimit = 5000;

public:
    CurrentAccount(int accNo, const string& name, double bal)
        : BankAccount(accNo, name, bal) {}

    void withdraw(double amount) override {
        if (amount <= 0)
            throw InvalidAmountException();
        if (amount > balance + overdraftLimit)
            throw InsufficientBalanceException();
        balance -= amount;
    }

    void calculateInterest() override {
        // No interest for current account
    }
};

//Bank manager
class Bank {
private:
    unordered_map<int, unique_ptr<BankAccount>> accounts;

public:
    void createAccount(unique_ptr<BankAccount> account) {
        int accNo = account->getAccountNumber();
        accounts[accNo] = move(account);
    }

    BankAccount& getAccount(int accNo) {
        if (accounts.find(accNo) == accounts.end())
            throw AccountNotFoundException();
        return *accounts[accNo];
    }
};

//Main function 
int main() {
    Bank bank;
    int choice = 0;

    while (true) {
        cout << "\n1. Create Savings Account"
             << "\n2. Create Current Account"
             << "\n3. Deposit"
             << "\n4. Withdraw"
             << "\n5. Check Balance"
             << "\n6. Calculate Interest"
             << "\n7. Exit\n"
             << "Enter choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }

        if (choice == 7) {
            cout << "Exiting...\n";
            break;
        }

        try {
            int accNo;
            cout << "Enter Account Number: ";
            if (!(cin >> accNo)) {
                throw AccountNotFoundException();
            }

            if (choice == 1 || choice == 2) {
                string name;
                double bal;

                cout << "Enter Name: ";
                cin >> name;

                cout << "Enter Initial Balance: ";
                if (!(cin >> bal))
                    throw InvalidAmountException();

                if (choice == 1)
                    bank.createAccount(make_unique<SavingsAccount>(accNo, name, bal));
                else
                    bank.createAccount(make_unique<CurrentAccount>(accNo, name, bal));

                cout << "Account created successfully.\n";
            }
            else if (choice == 3) {
                double amt;
                cout << "Enter Amount: ";
                if (!(cin >> amt))
                    throw InvalidAmountException();
                bank.getAccount(accNo).deposit(amt);
                cout << "Deposit successful.\n";
            }
            else if (choice == 4) {
                double amt;
                cout << "Enter Amount: ";
                if (!(cin >> amt))
                    throw InvalidAmountException();
                bank.getAccount(accNo).withdraw(amt);
                cout << "Withdrawal successful.\n";
            }
            else if (choice == 5) {
                cout << "Balance: "
                     << bank.getAccount(accNo).getBalance() << endl;
            }
            else if (choice == 6) {
                bank.getAccount(accNo).calculateInterest();
                cout << "Interest calculated.\n";
            }
            else {
                cout << "Invalid menu option.\n";
            }
        }
        catch (const BankingException& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
    return 0;
} 
