#pragma once
#include "ValidInput.h"
#include "Transaction.h"

class BankAccount : public ValidInput, public Transaction {
private:
	double balance;
	static int accountNumber;
	static int activeAccounts;
public:
	fstream BankAccountsTextFile;
	fstream AccNumActAccTextFile;
	ofstream temp;

	//string use to read file
	string userID, Name, accNum, accountType, bal, accType, storedName;

	//use for bank account menu
	bool bankAccountMenu;
	int currentUserAccounts;
	int ans;

	//use for adding and removing accounts
	bool accountExist;

	BankAccount();
	~BankAccount();
	void loadBankAccount(string userName);
	void removeBankAccount(string userName, string passWord);
	void addAccount(string userName);
	int getActiveAccounts();
	void showAll();
};

