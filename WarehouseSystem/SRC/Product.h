#pragma once
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

class Product {
private:
    string productId;
    string productName;
    int    quantity;
    string location;   // e.g. "Aisle C, Shelf 4"
    double price;

public:
    Product() : quantity(0), price(0.0) {}

    Product(string id, string name, int qty, string loc, double prc)
        : productId(id), productName(name), quantity(qty), location(loc), price(prc) {}

    // getters
    string getProductId()   const { return productId; }
    string getProductName() const { return productName; }
    int    getQuantity()    const { return quantity; }
    string getLocation()    const { return location; }
    double getPrice()       const { return price; }

    // setters
    void setProductName(const string& name) { productName = name; }
    void setQuantity(int qty)               { quantity = qty; }
    void setLocation(const string& loc)     { location = loc; }
    void setPrice(double prc)               { price = prc; }

    // reduces stock when an order is completed
    bool deductStock(int amount) {
        if (amount > quantity) return false;
        quantity -= amount;
        return true;
    }

    // adds stock
    void addStock(int amount) {
        quantity += amount;
    }

    // print one row in a table
    void printRow() const {
        cout << left
             << setw(15) << productId
             << setw(22) << productName
             << setw(10) << quantity
             << setw(20) << location
             << "$" << fixed << setprecision(2) << price
             << "\n";
    }

    // print table header
    static void printHeader() {
        cout << left
             << setw(15) << "Product ID"
             << setw(22) << "Name"
             << setw(10) << "Qty"
             << setw(20) << "Location"
             << "Price"
             << "\n";
        cout << string(75, '-') << "\n";
    }

    // saves to CSV line: id,name,qty,location,price
    string toCSV() const {
        ostringstream ss;
        ss << productId << "," << productName << "," << quantity
           << "," << location << "," << fixed << setprecision(2) << price;
        return ss.str();
    }

    // loads from a CSV line
    static Product fromCSV(const string& line) {
        stringstream ss(line);
        string id, name, loc, priceStr;
        string qtyStr;
        getline(ss, id,      ',');
        getline(ss, name,    ',');
        getline(ss, qtyStr,  ',');
        getline(ss, loc,     ',');
        getline(ss, priceStr,',');
        int    qty = stoi(qtyStr);
        double prc = stod(priceStr);
        return Product(id, name, qty, loc, prc);
    }
};
