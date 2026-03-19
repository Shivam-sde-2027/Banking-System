#pragma once
#include "Exceptions.h"
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

class BankAccount {
private:
    double balance;
    int pin;

protected:
    int accountNumber;
    std::string holderName;

    void setBalance(double newBalance) { balance = newBalance; }

public:
    std::vector<std::string> transactionHistory;

    BankAccount(int accNo, const std::string& name, double initialBalance, int pin)
        : balance(initialBalance), accountNumber(accNo), holderName(name), pin(pin)
    {
        if (initialBalance < 0)
            throw InvalidAmountException();

        transactionHistory.push_back("Account opened.");
    }

    bool authenticate(int enteredPin) const {
        return enteredPin == pin;
    }

    // 🔐 Masking
    std::string getMaskedAccountNumber() const {
        std::string acc = std::to_string(accountNumber);
        if (acc.length() <= 4) return acc;
        return std::string(acc.length() - 4, '*') + acc.substr(acc.length() - 4);
    }

    void deposit(double amount) {
        if (amount <= 0)
            throw InvalidAmountException();
        balance += amount;
        transactionHistory.push_back("Deposited: " + std::to_string(amount));
    }

    virtual void withdraw(double amount) = 0;

    virtual void displayInfo() const {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "----------------------------------\n";
        std::cout << "Account Number : " << getMaskedAccountNumber() << "\n";
        std::cout << "Holder Name    : " << holderName << "\n";
        std::cout << "Balance        : Rs. " << balance << "\n";
    }

    double getBalance() const { return balance; }
    int getAccountNumber() const { return accountNumber; }

    void printHistory() const {
        std::cout << "\n-- Transaction History --\n";
        for (const auto& entry : transactionHistory)
            std::cout << "  > " << entry << "\n";
    }

    virtual ~BankAccount() {}
};

// ================= Savings =================
class SavingsAccount : public BankAccount {
private:
    static const double MINIMUM_BALANCE;

public:
    SavingsAccount(int accNo, const std::string& name, double initialBalance, int pin)
        : BankAccount(accNo, name, initialBalance, pin) {}

    void withdraw(double amount) override {
        if (amount <= 0)
            throw InvalidAmountException();
        if (getBalance() - amount < MINIMUM_BALANCE)
            throw InsufficientFundsException();

        setBalance(getBalance() - amount);
        transactionHistory.push_back("Withdrawn: " + std::to_string(amount));
    }

    void displayInfo() const override {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "----------------------------------\n";
        std::cout << "Account Number : " << getMaskedAccountNumber() << "\n";
        std::cout << "Holder Name    : " << holderName << "\n";
        std::cout << "Balance        : Rs. " << getBalance() << "\n";
        std::cout << "Account Type   : Savings Account\n";
        std::cout << "Minimum Balance: Rs. 500\n";
    }
};

const double SavingsAccount::MINIMUM_BALANCE = 500.0;

// ================= Current =================
class CurrentAccount : public BankAccount {
private:
    double overdraftLimit;

public:
    CurrentAccount(int accNo, const std::string& name,
                   double initialBalance, int pin, double overdraft = 5000.0)
        : BankAccount(accNo, name, initialBalance, pin), overdraftLimit(overdraft) {}

    void withdraw(double amount) override {
        if (amount <= 0)
            throw InvalidAmountException();
        if (getBalance() - amount < -overdraftLimit)
            throw InsufficientFundsException();

        setBalance(getBalance() - amount);
        transactionHistory.push_back("Withdrawn: " + std::to_string(amount));
    }

    void displayInfo() const override {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "----------------------------------\n";
        std::cout << "Account Number : " << getMaskedAccountNumber() << "\n";
        std::cout << "Holder Name    : " << holderName << "\n";
        std::cout << "Balance        : Rs. " << getBalance() << "\n";
        std::cout << "Account Type   : Current Account\n";
        std::cout << "Overdraft Limit: Rs. " << overdraftLimit << "\n";
    }
};
