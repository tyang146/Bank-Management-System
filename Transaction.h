#pragma once
#include "ValidInput.h"
#include <sstream>

class Transaction {
public:
    double amount;
    static void deposit(const string& userName, double amount, const string& accountType);
    static void withdraw(const string& userName, double amount, const string& accountType);
    static void displayHistory(const string& userName);
};