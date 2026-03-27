#pragma once
#include "User.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

class Employee : public User {
private:
    string employeeId;
    string fullName;

public:
    Employee() {}

    Employee(string empId, string name, string uname, string pwd)
        : User(uname, pwd, "employee"), employeeId(empId), fullName(name) {}

    string getEmployeeId() const { return employeeId; }
    string getFullName()   const { return fullName; }

    void setFullName(const string& name) { fullName = name; }
    void setUsername(const string& uname) { username = uname; }
    void setPassword(const string& pwd)   { password = pwd; }

    void printRow() const {
        cout << left
             << setw(12) << employeeId
             << setw(22) << fullName
             << setw(18) << username
             << "\n";
    }

    static void printHeader() {
        cout << left
             << setw(12) << "Emp ID"
             << setw(22) << "Full Name"
             << setw(18) << "Username"
             << "\n";
        cout << string(52, '-') << "\n";
    }

    // saves to CSV: empId,fullName,username,password
    string toCSV() const {
        return employeeId + "," + fullName + "," + username + "," + password;
    }

    static Employee fromCSV(const string& line) {
        stringstream ss(line);
        string empId, name, uname, pwd;
        getline(ss, empId, ',');
        getline(ss, name,  ',');
        getline(ss, uname, ',');
        getline(ss, pwd,   ',');
        return Employee(empId, name, uname, pwd);
    }

    // employee dashboard - defined in main after InventoryManager is ready
    void showDashboard() override;
};
