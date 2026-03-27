#include <iostream>
#include <string>
#include "Utils.h"
#include "InventoryManager.h"
#include "Employee.h"

using namespace std;

// global manager instance - all functions share the same data
InventoryManager mgr;

// =============================================
//  MANAGER MENUS
// =============================================

void productMenu() {
    while (true) {
        printHeading("PRODUCT MANAGEMENT");
        cout << "  1. Add Product\n";
        cout << "  2. View All Products\n";
        cout << "  3. Edit Product\n";
        cout << "  4. Delete Product\n";
        cout << "  0. Back\n";
        printLine();
        int choice = getIntInputZeroOk("  Choice: ");
        cout << "\n";
        switch (choice) {
            case 1: mgr.addProduct();      break;
            case 2: mgr.viewAllProducts(); break;
            case 3: mgr.editProduct();     break;
            case 4: mgr.deleteProduct();   break;
            case 0: return;
            default: cout << "  Invalid choice.\n";
        }
        cout << "\n";
    }
}

void employeeMenu() {
    while (true) {
        printHeading("EMPLOYEE MANAGEMENT");
        cout << "  1. Add Employee\n";
        cout << "  2. View All Employees\n";
        cout << "  3. Edit Employee\n";
        cout << "  4. Delete Employee\n";
        cout << "  0. Back\n";
        printLine();
        int choice = getIntInputZeroOk("  Choice: ");
        cout << "\n";
        switch (choice) {
            case 1: mgr.addEmployee();     break;
            case 2: mgr.viewAllEmployees();break;
            case 3: mgr.editEmployee();    break;
            case 4: mgr.deleteEmployee();  break;
            case 0: return;
            default: cout << "  Invalid choice.\n";
        }
        cout << "\n";
    }
}

void orderMenu() {
    while (true) {
        printHeading("ORDER MANAGEMENT");
        cout << "  1. Create Order\n";
        cout << "  2. View All Orders\n";
        cout << "  3. Edit Order\n";
        cout << "  4. Delete Order\n";
        cout << "  5. Assign Order to Employee\n";
        cout << "  0. Back\n";
        printLine();
        int choice = getIntInputZeroOk("  Choice: ");
        cout << "\n";
        switch (choice) {
            case 1: mgr.createOrder();    break;
            case 2: mgr.viewAllOrders();  break;
            case 3: mgr.editOrder();      break;
            case 4: mgr.deleteOrder();    break;
            case 5: mgr.assignOrder();    break;
            case 0: return;
            default: cout << "  Invalid choice.\n";
        }
        cout << "\n";
    }
}

void reportMenuManager() {
    while (true) {
        printHeading("REPORTS");
        cout << "  1. Export Inventory Report (CSV)\n";
        cout << "  2. Export Orders Report (CSV)\n";
        cout << "  0. Back\n";
        printLine();
        int choice = getIntInputZeroOk("  Choice: ");
        cout << "\n";
        switch (choice) {
            case 1: mgr.generateInventoryReport(); break;
            case 2: mgr.generateOrdersReport();    break;
            case 0: return;
            default: cout << "  Invalid choice.\n";
        }
        cout << "\n";
    }
}

// main manager dashboard
void managerDashboard() {
    while (true) {
        printHeading("MANAGER DASHBOARD");
        cout << "  1. Product Management\n";
        cout << "  2. Employee Management\n";
        cout << "  3. Order Management\n";
        cout << "  4. Reports\n";
        cout << "  0. Logout\n";
        printLine();
        int choice = getIntInputZeroOk("  Choice: ");
        cout << "\n";
        switch (choice) {
            case 1: productMenu();        break;
            case 2: employeeMenu();       break;
            case 3: orderMenu();          break;
            case 4: reportMenuManager();  break;
            case 0:
                cout << "  Logged out.\n\n";
                return;
            default:
                cout << "  Invalid choice.\n";
        }
        cout << "\n";
    }
}

// =============================================
//  EMPLOYEE DASHBOARD
// =============================================

// this is the employee menu - called from main login
void employeeDashboard(Employee* emp) {
    string empId = emp->getEmployeeId();
    while (true) {
        printHeading("EMPLOYEE DASHBOARD - " + emp->getFullName());
        cout << "  1. View My Assigned Orders\n";
        cout << "  2. View Order Details\n";
        cout << "  3. Find a Product\n";
        cout << "  4. Complete an Order\n";
        cout << "  5. Export My Orders Report (CSV)\n";
        cout << "  0. Logout\n";
        printLine();
        int choice = getIntInputZeroOk("  Choice: ");
        cout << "\n";
        switch (choice) {
            case 1: mgr.viewMyOrders(empId);           break;
            case 2: mgr.viewOrderDetails(empId);       break;
            case 3: mgr.findProduct();                 break;
            case 4: mgr.completeOrder(empId);          break;
            case 5: mgr.generateMyOrdersReport(empId); break;
            case 0:
                cout << "  Logged out.\n\n";
                return;
            default:
                cout << "  Invalid choice.\n";
        }
        cout << "\n";
    }
}

// showDashboard() for Employee class - defined here because it needs mgr
void Employee::showDashboard() {
    employeeDashboard(this);
}

// =============================================
//  LOGIN SCREEN
// =============================================

void loginScreen() {
    printHeading("LOGIN");

    // manager login is hardcoded (only one manager account)
    const string MANAGER_USER = "manager";
    const string MANAGER_PASS = "manager123";

    cout << "  Username: ";
    string uname;
    getline(cin, uname);
    cout << "  Password: ";
    string pwd;
    getline(cin, pwd);
    cout << "\n";

    // check manager first
    if (uname == MANAGER_USER && pwd == MANAGER_PASS) {
        cout << "  Welcome, Manager!\n\n";
        managerDashboard();
        return;
    }

    // check employees
    Employee* emp = mgr.loginEmployee(uname, pwd);
    if (emp != nullptr) {
        cout << "  Welcome, " << emp->getFullName() << "!\n\n";
        emp->showDashboard();
        return;
    }

    cout << "  Incorrect username or password.\n\n";
}

// =============================================
//  MAIN
// =============================================

int main() {
    mgr.init();   // load all data from files

    while (true) {
        printLine('=', 50);
        cout << "   WAREHOUSE INVENTORY MANAGEMENT SYSTEM\n";
        printLine('=', 50);
        cout << "  1. Login\n";
        cout << "  0. Exit\n";
        printLine();
        int choice = getIntInputZeroOk("  Choice: ");
        cout << "\n";
        if (choice == 1) {
            loginScreen();
        } else if (choice == 0) {
            cout << "  Goodbye!\n";
            break;
        } else {
            cout << "  Invalid choice.\n\n";
        }
    }
    return 0;
}
