#pragma once
#include "User.h"
#include "BankAccount.h"

class Manager : public User, public BankAccount {
private:
public:
	fstream ManagerTextFile;
	bool managerMenu;

	Manager();
	~Manager();
	int login(string userName, string passWord);
};