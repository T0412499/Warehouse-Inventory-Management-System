#pragma once
#include "Product.h"
#include "Employee.h"
#include "Order.h"
#include "Utils.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <iomanip>
using namespace std;

// file paths for data storage
const string PRODUCTS_FILE  = "products.csv";
const string EMPLOYEES_FILE = "employees.csv";
const string ORDERS_FILE    = "orders.csv";

class InventoryManager {
private:
    vector<Product>  products;
    vector<Employee> employees;
    vector<Order>    orders;

    // ---- FILE I/O ----

    void loadProducts() {
        products.clear();
        ifstream file(PRODUCTS_FILE);
        if (!file.is_open()) return;
        string line;
        while (getline(file, line)) {
            if (!line.empty())
                products.push_back(Product::fromCSV(line));
        }
        file.close();
    }

    void saveProducts() {
        ofstream file(PRODUCTS_FILE);
        for (const auto& p : products)
            file << p.toCSV() << "\n";
        file.close();
    }

    void loadEmployees() {
        employees.clear();
        ifstream file(EMPLOYEES_FILE);
        if (!file.is_open()) return;
        string line;
        while (getline(file, line)) {
            if (!line.empty())
                employees.push_back(Employee::fromCSV(line));
        }
        file.close();
    }

    void saveEmployees() {
        ofstream file(EMPLOYEES_FILE);
        for (const auto& e : employees)
            file << e.toCSV() << "\n";
        file.close();
    }

    void loadOrders() {
        orders.clear();
        ifstream file(ORDERS_FILE);
        if (!file.is_open()) return;
        string line;
        while (getline(file, line)) {
            if (!line.empty())
                orders.push_back(Order::fromCSV(line));
        }
        file.close();
    }

    void saveOrders() {
        ofstream file(ORDERS_FILE);
        for (const auto& o : orders)
            file << o.toCSV() << "\n";
        file.close();
    }

    // ---- HELPERS ----

    // find product index by id (-1 if not found)
    int findProductIndex(const string& pid) const {
        for (int i = 0; i < (int)products.size(); i++) {
            if (toLower(products[i].getProductId()) == toLower(pid))
                return i;
        }
        return -1;
    }

    // find employee index by id
    int findEmployeeIndex(const string& eid) const {
        for (int i = 0; i < (int)employees.size(); i++) {
            if (toLower(employees[i].getEmployeeId()) == toLower(eid))
                return i;
        }
        return -1;
    }

    // find order index by id
    int findOrderIndex(const string& oid) const {
        for (int i = 0; i < (int)orders.size(); i++) {
            if (toLower(orders[i].getOrderId()) == toLower(oid))
                return i;
        }
        return -1;
    }

    // check if product id is already taken
    bool productIdExists(const string& pid) const {
        return findProductIndex(pid) != -1;
    }

    bool employeeIdExists(const string& eid) const {
        return findEmployeeIndex(eid) != -1;
    }

    bool orderIdExists(const string& oid) const {
        return findOrderIndex(oid) != -1;
    }

public:
    // loads all data from disk on startup
    void init() {
        loadProducts();
        loadEmployees();
        loadOrders();
    }

    // =============================================
    //  PRODUCT MANAGEMENT (Manager)
    // =============================================

    void addProduct() {
        printHeading("ADD NEW PRODUCT");
        string pid = getStringInput("  Enter Product ID   : ");
        if (productIdExists(pid)) {
            cout << "  A product with that ID already exists.\n";
            return;
        }
        string name  = getStringInput("  Enter Product Name  : ");
        int    qty   = getIntInputZeroOk("  Enter Quantity      : ");
        string loc   = getStringInput("  Enter Location      : ");
        double price = getDoubleInput("  Enter Price ($)     : ");

        products.push_back(Product(pid, name, qty, loc, price));
        saveProducts();
        cout << "  Product added successfully.\n";
    }

    void viewAllProducts() {
        printHeading("ALL PRODUCTS");
        if (products.empty()) {
            cout << "  No products in the system yet.\n";
            return;
        }
        Product::printHeader();
        // sort by product id before showing
        vector<Product> sorted = products;
        sort(sorted.begin(), sorted.end(), [](const Product& a, const Product& b) {
            return a.getProductId() < b.getProductId();
        });
        for (const auto& p : sorted)
            p.printRow();
    }

    void editProduct() {
        printHeading("EDIT PRODUCT");
        string pid = getStringInput("  Enter Product ID to edit: ");
        int idx = findProductIndex(pid);
        if (idx == -1) {
            cout << "  Product not found.\n";
            return;
        }
        Product& p = products[idx];
        cout << "  Current details:\n";
        Product::printHeader();
        p.printRow();
        cout << "\n  What would you like to change?\n";
        cout << "  1. Name\n  2. Quantity\n  3. Location\n  4. Price\n  0. Cancel\n";
        int choice = getIntInputZeroOk("  Choice: ");
        switch (choice) {
            case 1: p.setProductName(getStringInput("  New Name: "));     break;
            case 2: p.setQuantity(getIntInputZeroOk("  New Quantity: ")); break;
            case 3: p.setLocation(getStringInput("  New Location: "));   break;
            case 4: p.setPrice(getDoubleInput("  New Price ($): "));      break;
            case 0: cout << "  Cancelled.\n"; return;
            default: cout << "  Invalid choice.\n"; return;
        }
        saveProducts();
        cout << "  Product updated.\n";
    }

    void deleteProduct() {
        printHeading("DELETE PRODUCT");
        string pid = getStringInput("  Enter Product ID to delete: ");
        int idx = findProductIndex(pid);
        if (idx == -1) {
            cout << "  Product not found.\n";
            return;
        }
        products[idx].printRow();
        if (confirmAction("  Are you sure you want to delete this product?")) {
            products.erase(products.begin() + idx);
            saveProducts();
            cout << "  Product deleted.\n";
        } else {
            cout << "  Deletion cancelled.\n";
        }
    }

    // =============================================
    //  EMPLOYEE MANAGEMENT (Manager)
    // =============================================

    void addEmployee() {
        printHeading("ADD NEW EMPLOYEE");
        string eid   = getStringInput("  Enter Employee ID  : ");
        if (employeeIdExists(eid)) {
            cout << "  An employee with that ID already exists.\n";
            return;
        }
        string name  = getStringInput("  Enter Full Name    : ");
        string uname = getStringInput("  Enter Username     : ");
        string pwd   = getStringInput("  Enter Password     : ");
        employees.push_back(Employee(eid, name, uname, pwd));
        saveEmployees();
        cout << "  Employee added successfully.\n";
    }

    void viewAllEmployees() {
        printHeading("ALL EMPLOYEES");
        if (employees.empty()) {
            cout << "  No employees registered yet.\n";
            return;
        }
        Employee::printHeader();
        for (const auto& e : employees)
            e.printRow();
    }

    void editEmployee() {
        printHeading("EDIT EMPLOYEE");
        string eid = getStringInput("  Enter Employee ID to edit: ");
        int idx = findEmployeeIndex(eid);
        if (idx == -1) {
            cout << "  Employee not found.\n";
            return;
        }
        Employee& e = employees[idx];
        cout << "  What would you like to change?\n";
        cout << "  1. Full Name\n  2. Username\n  3. Password\n  0. Cancel\n";
        int choice = getIntInputZeroOk("  Choice: ");
        switch (choice) {
            case 1: e.setFullName(getStringInput("  New Full Name: ")); break;
            case 2: e.setUsername(getStringInput("  New Username: "));  break;
            case 3: e.setPassword(getStringInput("  New Password: "));  break;
            case 0: cout << "  Cancelled.\n"; return;
            default: cout << "  Invalid choice.\n"; return;
        }
        saveEmployees();
        cout << "  Employee updated.\n";
    }

    void deleteEmployee() {
        printHeading("DELETE EMPLOYEE");
        string eid = getStringInput("  Enter Employee ID to delete: ");
        int idx = findEmployeeIndex(eid);
        if (idx == -1) {
            cout << "  Employee not found.\n";
            return;
        }
        employees[idx].printRow();
        if (confirmAction("  Are you sure?")) {
            employees.erase(employees.begin() + idx);
            saveEmployees();
            cout << "  Employee deleted.\n";
        }
    }

    // =============================================
    //  ORDER MANAGEMENT (Manager)
    // =============================================

    void createOrder() {
        printHeading("CREATE NEW ORDER");
        string oid = getStringInput("  Enter Order ID: ");
        if (orderIdExists(oid)) {
            cout << "  An order with that ID already exists.\n";
            return;
        }
        Order newOrder(oid);
        cout << "  Now add items to this order.\n";
        while (true) {
            string pid = getStringInput("  Product ID (or 'done' to finish): ");
            if (toLower(pid) == "done") break;
            int pidx = findProductIndex(pid);
            if (pidx == -1) {
                cout << "  Product not found. Try again.\n";
                continue;
            }
            products[pidx].printRow();
            int qty = getIntInput("  Quantity: ");
            if (qty > products[pidx].getQuantity()) {
                cout << "  Warning: requested qty (" << qty << ") exceeds stock ("
                     << products[pidx].getQuantity() << "). Adding anyway.\n";
            }
            newOrder.addItem(pid, qty);
            cout << "  Item added.\n";
        }
        if (newOrder.getItems().empty()) {
            cout << "  Order has no items. Cancelled.\n";
            return;
        }
        orders.push_back(newOrder);
        saveOrders();
        cout << "  Order " << oid << " created.\n";
    }

    void viewAllOrders() {
        printHeading("ALL ORDERS");
        if (orders.empty()) {
            cout << "  No orders in the system yet.\n";
            return;
        }
        Order::printHeader();
        for (const auto& o : orders)
            o.printRow();
    }

    void editOrder() {
        printHeading("EDIT ORDER");
        string oid = getStringInput("  Enter Order ID to edit: ");
        int idx = findOrderIndex(oid);
        if (idx == -1) {
            cout << "  Order not found.\n";
            return;
        }
        if (orders[idx].isCompleted()) {
            cout << "  Cannot edit a completed order.\n";
            return;
        }
        Order& o = orders[idx];
        o.printDetails();
        cout << "\n  1. Add item\n  2. Remove item\n  0. Cancel\n";
        int choice = getIntInputZeroOk("  Choice: ");
        if (choice == 1) {
            string pid = getStringInput("  Product ID to add: ");
            if (findProductIndex(pid) == -1) {
                cout << "  Product not found.\n";
                return;
            }
            int qty = getIntInput("  Quantity: ");
            o.addItem(pid, qty);
            saveOrders();
            cout << "  Item added to order.\n";
        } else if (choice == 2) {
            string pid = getStringInput("  Product ID to remove: ");
            if (o.removeItem(pid))
                cout << "  Item removed.\n";
            else
                cout << "  Item not found in this order.\n";
            saveOrders();
        } else {
            cout << "  Cancelled.\n";
        }
    }

    void deleteOrder() {
        printHeading("DELETE ORDER");
        string oid = getStringInput("  Enter Order ID to delete: ");
        int idx = findOrderIndex(oid);
        if (idx == -1) {
            cout << "  Order not found.\n";
            return;
        }
        if (orders[idx].isCompleted()) {
            cout << "  Cannot delete a completed order.\n";
            return;
        }
        orders[idx].printDetails();
        if (confirmAction("  Delete this order?")) {
            orders.erase(orders.begin() + idx);
            saveOrders();
            cout << "  Order deleted.\n";
        }
    }

    void assignOrder() {
        printHeading("ASSIGN ORDER TO EMPLOYEE");
        // show unassigned pending orders
        cout << "  Pending / Unassigned Orders:\n";
        Order::printHeader();
        bool any = false;
        for (const auto& o : orders) {
            if (!o.isCompleted()) {
                o.printRow();
                any = true;
            }
        }
        if (!any) {
            cout << "  No pending orders.\n";
            return;
        }
        string oid = getStringInput("\n  Enter Order ID to assign: ");
        int oidx = findOrderIndex(oid);
        if (oidx == -1) {
            cout << "  Order not found.\n";
            return;
        }
        if (orders[oidx].isCompleted()) {
            cout << "  Order is already completed.\n";
            return;
        }
        // show employees
        viewAllEmployees();
        string eid = getStringInput("\n  Enter Employee ID to assign to: ");
        if (findEmployeeIndex(eid) == -1) {
            cout << "  Employee not found.\n";
            return;
        }
        orders[oidx].setAssignedTo(eid);
        saveOrders();
        cout << "  Order " << oid << " assigned to " << eid << ".\n";
    }

    // =============================================
    //  REPORTS (Advanced Feature)
    // =============================================

    void generateInventoryReport() {
        printHeading("EXPORT INVENTORY REPORT");
        string filename = getStringInput("  Enter filename (without .csv): ");
        filename += ".csv";
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "  Could not create file.\n";
            return;
        }
        file << "Product ID,Name,Quantity,Location,Price\n";
        for (const auto& p : products)
            file << p.toCSV() << "\n";
        file.close();
        cout << "  Inventory report saved to " << filename << "\n";
    }

    void generateOrdersReport() {
        printHeading("EXPORT ORDERS REPORT");
        cout << "  1. All Orders\n  2. Completed Only\n  3. Pending Only\n";
        int choice = getIntInput("  Choice: ");
        string filename = getStringInput("  Enter filename (without .csv): ");
        filename += ".csv";
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "  Could not create file.\n";
            return;
        }
        file << "Order ID,Assigned To,Status,Items\n";
        for (const auto& o : orders) {
            bool include = false;
            if (choice == 1) include = true;
            else if (choice == 2 && o.isCompleted()) include = true;
            else if (choice == 3 && !o.isCompleted()) include = true;
            if (include) {
                string itemStr = "";
                for (const auto& item : o.getItems())
                    itemStr += item.productId + "x" + to_string(item.qty) + " ";
                file << o.getOrderId() << ","
                     << o.getAssignedTo() << ","
                     << o.getStatus() << ","
                     << itemStr << "\n";
            }
        }
        file.close();
        cout << "  Orders report saved to " << filename << "\n";
    }

    // =============================================
    //  EMPLOYEE ACTIONS
    // =============================================

    // returns all orders assigned to a specific employee
    void viewMyOrders(const string& empId) {
        printHeading("MY ASSIGNED ORDERS");
        bool found = false;
        Order::printHeader();
        for (const auto& o : orders) {
            if (toLower(o.getAssignedTo()) == toLower(empId)) {
                o.printRow();
                found = true;
            }
        }
        if (!found)
            cout << "  No orders assigned to you.\n";
    }

    // view details of a specific assigned order
    void viewOrderDetails(const string& empId) {
        string oid = getStringInput("  Enter Order ID: ");
        int idx = findOrderIndex(oid);
        if (idx == -1) {
            cout << "  Order not found.\n";
            return;
        }
        if (toLower(orders[idx].getAssignedTo()) != toLower(empId)) {
            cout << "  That order is not assigned to you.\n";
            return;
        }
        orders[idx].printDetails();
        // also show product locations to help employee find them
        cout << "\n  Product locations:\n";
        cout << string(40, '-') << "\n";
        for (const auto& item : orders[idx].getItems()) {
            int pidx = findProductIndex(item.productId);
            if (pidx != -1) {
                cout << "  " << left << setw(15) << item.productId
                     << "-> " << products[pidx].getLocation() << "\n";
            }
        }
    }

    // search product by id or name (employee feature)
    void findProduct() {
        printHeading("FIND PRODUCT");
        string keyword = getStringInput("  Enter product ID or name: ");
        string kLower  = toLower(keyword);
        bool found = false;
        Product::printHeader();
        for (const auto& p : products) {
            if (toLower(p.getProductId()).find(kLower)   != string::npos ||
                toLower(p.getProductName()).find(kLower) != string::npos) {
                p.printRow();
                found = true;
            }
        }
        if (!found)
            cout << "  No products matched your search.\n";
    }

    // mark an order as complete and deduct stock
    void completeOrder(const string& empId) {
        printHeading("COMPLETE ORDER");
        viewMyOrders(empId);
        string oid = getStringInput("\n  Enter Order ID to complete: ");
        int idx = findOrderIndex(oid);
        if (idx == -1) {
            cout << "  Order not found.\n";
            return;
        }
        if (toLower(orders[idx].getAssignedTo()) != toLower(empId)) {
            cout << "  That order is not assigned to you.\n";
            return;
        }
        if (orders[idx].isCompleted()) {
            cout << "  Order is already completed.\n";
            return;
        }
        // check stock is enough before doing anything
        bool stockOk = true;
        for (const auto& item : orders[idx].getItems()) {
            int pidx = findProductIndex(item.productId);
            if (pidx == -1 || products[pidx].getQuantity() < item.qty) {
                cout << "  Not enough stock for: " << item.productId << "\n";
                stockOk = false;
            }
        }
        if (!stockOk) {
            cout << "  Order cannot be completed due to stock issues.\n";
            return;
        }
        if (!confirmAction("  Confirm complete order " + oid + "?"))
            return;

        // deduct stock for every item
        for (const auto& item : orders[idx].getItems()) {
            int pidx = findProductIndex(item.productId);
            products[pidx].deductStock(item.qty);
        }
        orders[idx].setStatus("completed");
        saveProducts();
        saveOrders();
        cout << "  Order " << oid << " marked as completed. Stock updated.\n";
    }

    // employee can export their completed/pending orders
    void generateMyOrdersReport(const string& empId) {
        printHeading("EXPORT MY ORDERS REPORT");
        cout << "  1. All My Orders\n  2. Completed\n  3. Pending\n";
        int choice = getIntInput("  Choice: ");
        string filename = getStringInput("  Enter filename (without .csv): ");
        filename += ".csv";
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "  Could not create file.\n";
            return;
        }
        file << "Order ID,Status,Items\n";
        for (const auto& o : orders) {
            if (toLower(o.getAssignedTo()) != toLower(empId)) continue;
            bool include = false;
            if (choice == 1) include = true;
            else if (choice == 2 && o.isCompleted()) include = true;
            else if (choice == 3 && !o.isCompleted()) include = true;
            if (include) {
                string itemStr = "";
                for (const auto& item : o.getItems())
                    itemStr += item.productId + "x" + to_string(item.qty) + " ";
                file << o.getOrderId() << "," << o.getStatus() << "," << itemStr << "\n";
            }
        }
        file.close();
        cout << "  Report saved to " << filename << "\n";
    }

    // login check - returns pointer to Employee if found, nullptr if not
    Employee* loginEmployee(const string& uname, const string& pwd) {
        for (auto& e : employees) {
            if (e.checkLogin(uname, pwd))
                return &e;
        }
        return nullptr;
    }
};
