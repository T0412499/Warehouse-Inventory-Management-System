#pragma once
#include <iostream>
#include <string>
#include <limits>
#include <algorithm>

using namespace std;

// clears the input buffer so cin doesnt skip lines
void clearBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// trims spaces from both ends of a string
string trimSpaces(string str) {
    int start = 0;
    while (start < (int)str.size() && str[start] == ' ')
        start++;
    int end = (int)str.size() - 1;
    while (end >= start && str[end] == ' ')
        end--;
    return str.substr(start, end - start + 1);
}

// converts string to lowercase for comparisons
string toLower(string str) {
    for (char& c : str)
        c = tolower(c);
    return str;
}

// reads a non-empty string from user
string getStringInput(const string& prompt) {
    string val;
    while (true) {
        cout << prompt;
        getline(cin, val);
        val = trimSpaces(val);
        if (!val.empty())
            return val;
        cout << "  Input cannot be empty. Try again.\n";
    }
}

// reads a positive integer from user
int getIntInput(const string& prompt) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val && val > 0) {
            clearBuffer();
            return val;
        }
        cout << "  Please enter a valid positive number.\n";
        cin.clear();
        clearBuffer();
    }
}

// reads a non-negative integer (0 allowed, e.g. for quantity)
int getIntInputZeroOk(const string& prompt) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val && val >= 0) {
            clearBuffer();
            return val;
        }
        cout << "  Please enter a valid number (0 or above).\n";
        cin.clear();
        clearBuffer();
    }
}

// reads a positive decimal number (for price)
double getDoubleInput(const string& prompt) {
    double val;
    while (true) {
        cout << prompt;
        if (cin >> val && val >= 0.0) {
            clearBuffer();
            return val;
        }
        cout << "  Please enter a valid price (e.g. 9.99).\n";
        cin.clear();
        clearBuffer();
    }
}

// simple yes/no prompt
bool confirmAction(const string& msg) {
    cout << msg << " (y/n): ";
    char c;
    cin >> c;
    clearBuffer();
    return (tolower(c) == 'y');
}

// prints a divider line for the console UI
void printLine(char ch = '-', int len = 50) {
    cout << string(len, ch) << "\n";
}

// prints a heading with borders
void printHeading(const string& title) {
    printLine('=');
    cout << "  " << title << "\n";
    printLine('=');
}
