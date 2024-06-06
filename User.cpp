#include "User.h"

//constructor and deconstructor
User::User() { matches = false; }
User::~User() {}

//function for user login
int User::login(string userName, string passWord) {
    //open text file
    UsersTextFile.open("Users.txt");

    //fail to open file
    if (!UsersTextFile) {
        cout << "No such file found.\n" << endl;
        return 0;
    }

    //open file successfully
    //validate Username and Password input with Username and Password in user text file
    else {
        while (getline(UsersTextFile, this->userName, ';'), getline(UsersTextFile, this->passWord)) {
            if (this->userName == userName && this->passWord == passWord) {
                cout << "User successfully login.\n" << endl;
                //close the file
                UsersTextFile.close();
                return 1;//found matching username and password
            }
        } 
        //couldn't find matching username and password in user text file
        cout << "User login fail.\n" << endl;
        //close the file
        UsersTextFile.close();
        return 0;
    }   
}

//function to create user login
string User::createUser() {
    //ask for Username
    do { 
        matches = false;
        //check to see if user enter only letters and numbers
        do { 
            cout << "Enter Username: " << endl;
            cin >> userName;
        } while (!isAlphaNumeric(userName));

        //check to see if Username already exist
        if (userExist(userName) == 1) {
            cout << "Username already in use. Try again.\n" << endl;
            matches = true;
        }
    } while (matches == true);

    //ask for Password
    do {
        cout << "Enter Password: " << endl;
        cin >> passWord;
    } while (!isAlphaNumeric(passWord));

    //append username and password to user text file
    UsersTextFile.open("Users.txt", ios::app);
    if (!UsersTextFile) {
        cout << "No such file found.\n" << endl;
    }
    else {
        UsersTextFile << userName << ";" << passWord << endl;
        cout << "User successfully created.\n" << endl;
    }
    //close the file and return username use to create bank account
    //can return a userID if wanted but username is already unique
    UsersTextFile.close();
    return userName;
}

//function to check if a user account exist
int User::userExist(string userName) {
    UsersTextFile.open("Users.txt");
    if (!UsersTextFile) {
        cout << "No such file found.\n" << endl;
        return 0;
    }
    //validate Username input with Username in text file
    else {
        while (getline(UsersTextFile, user, ';'), getline(UsersTextFile, passWord)) {
            if (user == userName) {
                UsersTextFile.close();
                return 1;//user does exist

            }
        }
        UsersTextFile.close();
        return 0;//user doesn't exist
    }
}

//function to remove user account
void User::removeUser(string userName) {
    matches = false;//use to tell if user account is remove or not
    UsersTextFile.open("Users.txt");
    BankTextFile.open("BankAccounts.txt");
    temp.open("temp.txt");
    if (!BankTextFile && !temp && !UsersTextFile) {
        cout << "No such file found.\n" << endl;
        return;
    }
    else {
        //prevent deletion of user account if user still have open bank accounts
        while (getline(BankTextFile, this->userName, ';'), getline(BankTextFile, passWord)) {
            if (this->userName == userName) {
                cout << "There is still an open bank account for this user. Close bank accounts first and try again. \n" << endl;
                UsersTextFile.close();
                BankTextFile.close();
                temp.close();
                return;
            }
        }
        //else try to delete user
        while (getline(UsersTextFile, this->userName, ';'), getline(UsersTextFile, passWord)) {
            if (this->userName == userName) {//if user matches, don't write to temp text file
                cout << "Remove user successfully.\n" << endl;
                matches = true;
            }
            else {//write any user that doesn't match to temp text file
                temp << this->userName << ';' << passWord << endl;
            }
        }
        if (matches == false) {//no user remove
            cout << "Remove user fail.\n" << endl;
        }
    }

    BankTextFile.close();
    UsersTextFile.close();
    temp.close();
    //remove old Users.txt file and rename temp to new Users.txt file
    remove("Users.txt");
    if (rename("temp.txt", "Users.txt") == -1 ) {
        cout << "Rename file failed." << endl;
    }
    return;
}
