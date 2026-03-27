#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

// one item line inside an order: product id + how many
struct OrderItem {
    string productId;
    int    qty;

    OrderItem(string pid, int q) : productId(pid), qty(q) {}
};

class Order {
private:
    string orderId;
    string assignedTo;   // employee ID, empty if not assigned yet
    string status;       // "pending" or "completed"
    vector<OrderItem> items;

public:
    Order() : status("pending") {}

    Order(string oid)
        : orderId(oid), assignedTo(""), status("pending") {}

    // getters
    string getOrderId()    const { return orderId; }
    string getAssignedTo() const { return assignedTo; }
    string getStatus()     const { return status; }
    const vector<OrderItem>& getItems() const { return items; }

    // setters
    void setAssignedTo(const string& empId) { assignedTo = empId; }
    void setStatus(const string& s)         { status = s; }

    void addItem(const string& prodId, int qty) {
        // if product already in order just update qty
        for (auto& item : items) {
            if (item.productId == prodId) {
                item.qty += qty;
                return;
            }
        }
        items.push_back(OrderItem(prodId, qty));
    }

    // remove item from order by product id
    bool removeItem(const string& prodId) {
        for (int i = 0; i < (int)items.size(); i++) {
            if (items[i].productId == prodId) {
                items.erase(items.begin() + i);
                return true;
            }
        }
        return false;
    }

    bool isCompleted() const { return status == "completed"; }
    bool isAssigned()  const { return !assignedTo.empty(); }

    // prints a summary row in a list
    void printRow() const {
        string assignInfo = assignedTo.empty() ? "Unassigned" : assignedTo;
        cout << left
             << setw(12) << orderId
             << setw(18) << assignInfo
             << setw(12) << status
             << items.size() << " item(s)"
             << "\n";
    }

    static void printHeader() {
        cout << left
             << setw(12) << "Order ID"
             << setw(18) << "Assigned To"
             << setw(12) << "Status"
             << "Items"
             << "\n";
        cout << string(55, '-') << "\n";
    }

    // prints full order details
    void printDetails() const {
        cout << "  Order ID   : " << orderId << "\n";
        cout << "  Assigned To: " << (assignedTo.empty() ? "Not assigned" : assignedTo) << "\n";
        cout << "  Status     : " << status << "\n";
        cout << "  Items:\n";
        for (const auto& item : items) {
            cout << "    - " << item.productId << "  x" << item.qty << "\n";
        }
    }

    // CSV format: orderId|assignedTo|status|prodId:qty,prodId:qty,...
    string toCSV() const {
        string itemStr = "";
        for (int i = 0; i < (int)items.size(); i++) {
            if (i > 0) itemStr += ",";
            itemStr += items[i].productId + ":" + to_string(items[i].qty);
        }
        return orderId + "|" + assignedTo + "|" + status + "|" + itemStr;
    }

    static Order fromCSV(const string& line) {
        stringstream ss(line);
        string oid, assigned, stat, itemsStr;
        getline(ss, oid,      '|');
        getline(ss, assigned, '|');
        getline(ss, stat,     '|');
        getline(ss, itemsStr, '|');

        Order o(oid);
        o.setAssignedTo(assigned);
        o.setStatus(stat);

        // parse items: prodId:qty,prodId:qty
        if (!itemsStr.empty()) {
            stringstream is(itemsStr);
            string token;
            while (getline(is, token, ',')) {
                size_t colonPos = token.find(':');
                if (colonPos != string::npos) {
                    string pid = token.substr(0, colonPos);
                    int    qty = stoi(token.substr(colonPos + 1));
                    o.items.push_back(OrderItem(pid, qty));
                }
            }
        }
        return o;
    }
};
