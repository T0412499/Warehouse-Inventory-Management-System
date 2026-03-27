#pragma once
#include <string>
using namespace std;

// base class - both Manager and Employee share these fields
class User {
protected:
    string username;
    string password;
    string role;  // "manager" or "employee"

public:
    User() {}
    User(string uname, string pwd, string r)
        : username(uname), password(pwd), role(r) {}

    string getUsername() const { return username; }
    string getRole()     const { return role; }

    // checks if login details match
    bool checkLogin(const string& uname, const string& pwd) const {
        return (username == uname && password == pwd);
    }

    virtual void showDashboard() = 0;  // each role has its own menu

    virtual ~User() {}
};
