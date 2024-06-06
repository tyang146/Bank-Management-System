#include "ValidInput.h"

//constructor and deconstructor
ValidInput::ValidInput() {};
ValidInput::~ValidInput() {};

//keep here or move?
//function to take only letters and numbers as input
bool ValidInput::isAlphaNumeric(string input) {
    for (char c : input) {
        if (!isalnum(c)) {
            cout << "Enter only letters and numbers. Try again.\n" << endl;
            return false;
        }
    }
    return true;
}

//keep here or move?
//function to take only numbers and if it is a decimal number no more than 2 decimal places
bool ValidInput::isTwoDecimalPlaces(double input) {
    if (input <= 0) {
        //clear error input due to input type doesn't match and ignore input
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter a number greater than 0. Try again.\n" << endl;
        return false;
    }
    double roundedInput = round(input * 100) / 100;
    if (input != roundedInput) {
        cout << "Enter a number with 2 decimal places. Try again.\n" << endl;
        return false;
    }
    return true;
}