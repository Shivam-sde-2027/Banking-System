#pragma once
#include <exception>
#include <string>

class BankingException : public std::exception {
protected:
    std::string message;
public:
    BankingException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class InsufficientFundsException : public BankingException {
public:
    InsufficientFundsException()
        : BankingException("Insufficient funds.") {}
};

class InvalidAmountException : public BankingException {
public:
    InvalidAmountException()
        : BankingException("Invalid amount.") {}
};

class AccountNotFoundException : public BankingException {
public:
    AccountNotFoundException()
        : BankingException("Account not found.") {}
};

class AuthenticationException : public BankingException {
public:
    AuthenticationException()
        : BankingException("Invalid PIN. Access denied.") {}
};
