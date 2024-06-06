#pragma once
#include <iostream>
#include <fstream>//I/O files
#include <string>
#include <iomanip>//setprecision()

using namespace std;

class ValidInput {
private:
public:
	ValidInput();
	~ValidInput();
	bool isAlphaNumeric(string input);
	bool isTwoDecimalPlaces(double input);
};