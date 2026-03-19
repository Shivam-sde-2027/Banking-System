#pragma once
#include "BankAccount.h"
#include <unordered_map>
#include <memory>

class Bank {
private:
    std::unordered_map<int, std::unique_ptr<BankAccount>> accounts;

    BankAccount& getAccount(int accNo) {
        auto it = accounts.find(accNo);
        if (it == accounts.end())
            throw AccountNotFoundException();
        return *it->second;
    }

    void verify(int accNo) {
        int pin;
        std::cout << "Enter PIN: ";
        std::cin >> pin;

        if (!getAccount(accNo).authenticate(pin))
            throw AuthenticationException();
    }

public:
    void addAccount(std::unique_ptr<BankAccount> account) {
        accounts[account->getAccountNumber()] = std::move(account);
        std::cout << "Account created successfully.\n";
    }

    void deposit(int accNo, double amount) {
        verify(accNo);
        getAccount(accNo).deposit(amount);
        std::cout << "Deposit successful.\n";
    }

    void withdraw(int accNo, double amount) {
        verify(accNo);
        getAccount(accNo).withdraw(amount);
        std::cout << "Withdrawal successful.\n";
    }

    void transfer(int fromAccNo, int toAccNo, double amount) {
        verify(fromAccNo);

        BankAccount& from = getAccount(fromAccNo);
        BankAccount& to   = getAccount(toAccNo);

        from.withdraw(amount);
        to.deposit(amount);

        std::cout << "Transfer successful.\n";
    }

    void checkBalance(int accNo) {
        verify(accNo);
        std::cout << "Balance: Rs. " << getAccount(accNo).getBalance() << "\n";
    }

    void displayAccount(int accNo) {
        verify(accNo);
        getAccount(accNo).displayInfo();
    }

    void displayAllAccounts() {
        std::cout << "\n===== All Accounts =====\n";
        for (const auto& pair : accounts) {
            pair.second->displayInfo();
        }
    }

    void printHistory(int accNo) {
        verify(accNo);
        getAccount(accNo).printHistory();
    }
};
