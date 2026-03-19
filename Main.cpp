#include "Bank.h"
#include <iostream>
#include <limits>

template <typename T>
T readInput(const std::string& prompt) {
    T value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) return value;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Try again.\n";
    }
}

void menu() {
    std::cout << "\n1. Create Saving Account\n2. Create Current Account\n3. Deposit Amount\n4. Withdraw Amount\n5. Transfer Amount\n6. Bank Balance\n7. Bank Details\n8. Transaction History\n9. All Accounts Details\n0. Exit\nChoice: ";
}

int main() {
    Bank bank;
    int choice;

    while (true) {
        menu();
        std::cin >> choice;

        if (choice == 0) break;

        try {
            if (choice == 1) {
                int acc = readInput<int>("Acc No: ");
                std::string name;
                std::cout << "Name: "; std::cin >> name;
                double bal = readInput<double>("Balance: ");
                int pin = readInput<int>("Set PIN: ");

                bank.addAccount(std::make_unique<SavingsAccount>(acc, name, bal, pin));

            } else if (choice == 2) {
                int acc = readInput<int>("Acc No: ");
                std::string name;
                std::cout << "Name: "; std::cin >> name;
                double bal = readInput<double>("Balance: ");
                int pin = readInput<int>("Set PIN: ");
                double od = readInput<double>("Overdraft: ");

                bank.addAccount(std::make_unique<CurrentAccount>(acc, name, bal, pin, od));

            } else if (choice == 3) {
                bank.deposit(readInput<int>("Acc: "), readInput<double>("Amt: "));
            } else if (choice == 4) {
                bank.withdraw(readInput<int>("Acc: "), readInput<double>("Amt: "));
            } else if (choice == 5) {
                int f = readInput<int>("From: ");
                int t = readInput<int>("To: ");
                double a = readInput<double>("Amt: ");
                bank.transfer(f, t, a);
            } else if (choice == 6) {
                bank.checkBalance(readInput<int>("Acc: "));
            } else if (choice == 7) {
                bank.displayAccount(readInput<int>("Acc: "));
            } else if (choice == 8) {
                bank.printHistory(readInput<int>("Acc: "));
            } else if (choice == 9) {
                bank.displayAllAccounts();
            }

        } catch (const BankingException& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
}
