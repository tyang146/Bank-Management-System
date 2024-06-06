#pragma once
#include "ValidInput.h"

class User : public ValidInput {
private:
public:
	fstream BankTextFile;
	fstream UsersTextFile;
	ofstream temp;
	//string use to read file
	string userName, passWord, user;
	bool matches;

	User();
	~User();
	virtual int login(string userName, string passWord);
	string createUser();
	int userExist(string userName);
	void removeUser(string userName);
};