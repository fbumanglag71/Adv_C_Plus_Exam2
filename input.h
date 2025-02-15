#pragma once
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

string& ltrim(string& s)
{
	s.erase(s.begin(), find_if_not(s.begin(), s.end(), [](int c) {return isspace(c); }));
	return s;
}

string& rtrim(string& s)
{
	s.erase(find_if_not(s.rbegin(), s.rend(), [](int c) {return isspace(c); }).base(), s.end());
	return s;
}

string trim(const string& s)
{
	string t = s;
	return ltrim(rtrim(t));
}

//return an input string
string inputString(string prompt, bool haveSpaces, int length)
{
	string input;
	while (true)
	{
		cout << prompt;
		if (haveSpaces)
			getline(cin, input);
		else
		{
			cin >> input;
			cin.clear();
			cin.ignore(999, '\n');
		}

		if (input.length() > length)
			cout << "ERROR-2: Invalid input. Length must not be exceeded " << length << " characters.\n";
		else
			break;
	}
	input.resize(length);
	return trim(input);
}

//return an input string
string inputString(string prompt, bool haveSpaces)
{
	string input;
	cout << prompt;
	if (haveSpaces)
		getline(cin, input);
	else
	{
		cin >> input;
		cin.clear();
		cin.ignore(999, '\n');
	}

	return trim(input);
}

//return an input char
char inputChar(string prompt, string listChars)
{
	char input;
	while (true)
	{
		cout << prompt;
		if (!(cin >> input))
			cout << "ERROR-1: Invalid input. Must be a character type.\n";
		else
		{
			bool bfound = false;
			for (unsigned c = 0; c < listChars.length(); c++)
				if (toupper(listChars[c]) == toupper(input))
				{
					bfound = true;
					break;
				}
			if (!bfound)
			{
				cout << "ERROR-2: Invalid input. Must be a character from the list of '";
				for (unsigned c = 0; c < listChars.length() - 1; c++)
					cout << "'" << static_cast<char>(toupper(listChars[c])) << "', ";
				cout << "or '" << static_cast<char>(toupper(listChars.back())) << "'.\n";
			}
			else
				break;
		}
		cin.clear();
		cin.ignore(999, '\n');

	};

	cin.clear();
	cin.ignore(999, '\n');

	return input;
}

//return an input char
char inputChar(string prompt, char yes, char no)
{
	char input;
	do
	{
		cout << prompt;
		if (!(cin >> input))
		{
			cout << "ERROR-1A: Invalid input. Must be a character type.\n";
			cin.clear();
			cin.ignore(999, '\n');
		}
		else if (tolower(input) != tolower(yes) && tolower(input) != tolower(no))
			cout << "ERROR-2A: Invalid input. Must be a '" << static_cast<char>(toupper(yes)) << "' or '" << static_cast<char>(toupper(no)) << "' character.\n";
		else
			break;
	} while (true);
	cin.clear();
	cin.ignore(999, '\n');
	return input;
}

//return an input char
char inputChar(string prompt, bool alphaOrDigit)
{
	char input;
	do
	{
		cout << prompt;
		if (!(cin >> input))
		{
			cout << "ERROR-1A: Invalid input. Must be a character type.\n";
			cin.clear();
			cin.ignore(999, '\n');
		}
		else if (alphaOrDigit && !isalpha(input))
			cout << "ERROR-2A: Invalid input. Must be an alphabet character.\n";
		else if (!alphaOrDigit && !isdigit(input))
			cout << "ERROR-2A: Invalid input. Must be a digit character.\n";
		else
			break;
	} while (true);
	cin.clear();
	cin.ignore(999, '\n');
	return input;
}

//return an input char
char inputChar(string prompt)
{
	char input;
	do
	{
		cout << prompt;
		if (!(cin >> input))
		{
			cout << "ERROR-1A: Invalid input. Must be a character type.\n";
			cin.clear();
			cin.ignore(999, '\n');
		}
		else
			break;
	} while (true);
	cin.clear();
	cin.ignore(999, '\n');
	return input;
}

//return an input interger
int inputInteger(string prompt)
{
	int input;
	do
	{
		cout << prompt;
		if (!(cin >> input))
		{
			cout << "ERROR-1A: Invalid input. Must be an integer type.\n";
			cin.clear();
			cin.ignore(999, '\n');
		}
		else
			break;
	} while (true);
	cin.clear();
	cin.ignore(999, '\n');
	return input;
}

//return an integer where posNeg is positive (true) or negative (false)
int inputInteger(string prompt, bool posNeg)
{
	int input;
	do
	{
		cout << prompt;
		if (!(cin >> input))
		{
			cout << "ERROR-2A: Invalid input. Must be an integer type.\n";
			cin.clear();
			cin.ignore(999, '\n');
		}
		else if (posNeg && input < 0)
			cout << "ERROR-2A: Invalid input. Must be a positive number.\n";
		else if (!posNeg && input >= 0)
			cout << "ERROR-2A: Invalid input. Must be a negative number.\n";
		else
			break;
	} while (true);
	cin.clear();
	cin.ignore(999, '\n');
	return input;
}

//return an input integer within range ,start and end
int inputInteger(string prompt, int startRange, int endRange)
{

	int input;
	do
	{
		cout << prompt;
		if (!(cin >> input))
		{
			cout << "ERROR-3A: Invalid input. Must be an integer type.\n";
			cin.clear();
			cin.ignore(999, '\n');
		}
		else if (!(input >= min(startRange, endRange) && input <= max(startRange, endRange)))
			cout << "ERROR-3A: Invalid input. Must be from " << startRange << ".." << endRange << ".\n";
		else
			break;
	} while (true);
	cin.clear();
	cin.ignore(999, '\n');
	return input;
}

//return an input double
double inputDouble(string prompt)
{
	double input;
	do
	{
		cout << prompt;
		if (!(cin >> input))
		{
			cout << "ERROR-1B: Invalid input. Must be a double type.\n";
			cin.clear();
			cin.ignore(999, '\n');
		}
		else
			break;
	} while (true);
	return input;
}

//return a double where posNeg is positive (true) or negative (false)
double inputDouble(string prompt, bool posNeg)
{
	double input;
	do
	{
		cout << prompt;
		if (!(cin >> input))
		{
			cout << "ERROR-2B: Invalid input. Must be a double type.\n";
			cin.clear();
			cin.ignore(999, '\n');
		}
		else if (posNeg && input < 0.0)
			cout << "ERROR-2B: Invalid input. Must be a positive number.\n";
		else if (!posNeg && input >= 0.0)
			cout << "ERROR-2B: Invalid input. Must be a negative number.\n";
		else
			break;
	} while (true);
	return input;
}

//return an input double within range ,start and end
double inputDouble(string prompt, double startRange, double endRange)
{
	double input;
	do
	{
		cout << prompt;
		if (!(cin >> input))
		{
			cout << "ERROR-3A: Invalid input. Must be a double type.\n";
			cin.clear();
			cin.ignore(999, '\n');
		}
		else if (!(input >= min(startRange, endRange) && input <= max(startRange, endRange)))
			cout << "ERROR-3A: Invalid input. Must be from " << startRange << ".." << endRange << ".\n";
		else
			break;
	} while (true);
	return input;
}


