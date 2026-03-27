===================================================
  WAREHOUSE INVENTORY MANAGEMENT SYSTEM
  TEST PLAN & HOW TO RUN
===================================================

HOW TO RUN TESTS
-----------------
1. Open main.cpp in VS Code stored in SRC Folder.
2. Run code using code runner, (make sure MinGW-w64 is installed in your system)
This will create an .exe file. Now Close the terminal
3. Run the .exe from the Debug or Release folder
4. Follow the test cases below manually, using the
   sample data provided.

Default Manager Login:
  Username : manager
  Password : manager123

Sample Employee Login (after adding via manager):
  Username : david
  Password : emp123


===================================================
TEST CASES
===================================================

--- TC01: Manager Login ---
Steps:
  1. Run program
  2. Select 1 (Login)
  3. Enter username: manager
  4. Enter password: manager123
Expected: "Welcome, Manager!" and manager dashboard shown
Result: PASS

--- TC02: Wrong Password ---
Steps:
  1. Select 1 (Login)
  2. Enter username: manager
  3. Enter password: wrongpass
Expected: "Incorrect username or password."
Result: PASS

--- TC03: Add Product ---
Steps:
  1. Login as manager
  2. Go to Product Management > Add Product
  3. Enter: ID=W_MOUSE-101, Name=Wireless Mouse,
     Qty=500, Location=Aisle C Shelf 4, Price=15.99
Expected: "Product added successfully."
Result: PASS

--- TC04: Duplicate Product ID ---
Steps:
  1. Try to add product with ID=W_MOUSE-101 again
Expected: "A product with that ID already exists."
Result: PASS

--- TC05: View All Products ---
Steps:
  1. Product Management > View All Products
Expected: Table shows W_MOUSE-101 row
Result: PASS

--- TC06: Edit Product ---
Steps:
  1. Product Management > Edit Product
  2. Enter ID: W_MOUSE-101
  3. Choose option 4 (Price), enter 19.99
Expected: Product price updated, shows "Product updated."
Result: PASS

--- TC07: Add Employee ---
Steps:
  1. Employee Management > Add Employee
  2. Enter: ID=EMP001, Name=David Smith,
     Username=david, Password=emp123
Expected: "Employee added successfully."
Result: PASS

--- TC08: Employee Login ---
Steps:
  1. Logout from manager
  2. Login with username=david, password=emp123
Expected: "Welcome, David Smith!" and employee dashboard
Result: PASS

--- TC09: Create Order ---
Steps:
  1. Login as manager
  2. Order Management > Create Order
  3. Order ID: ORD101
  4. Add W_MOUSE-101 x50
  5. Type 'done'
Expected: "Order ORD101 created."
Result: PASS

--- TC10: Edit Order (add item) ---
Steps:
  1. Order Management > Edit Order
  2. Enter ORD101
  3. Choose Add Item
  4. Add KEYBOARD-102 x30 (add that product first)
Expected: Item added to order
Result: PASS

--- TC11: Assign Order ---
Steps:
  1. Order Management > Assign Order
  2. Select ORD101, assign to EMP001
Expected: "Order ORD101 assigned to EMP001."
Result: PASS

--- TC12: Employee Views Order ---
Steps:
  1. Login as david
  2. Select View My Assigned Orders
Expected: ORD101 shows in list with both items
Result: PASS

--- TC13: Find Product (Employee) ---
Steps:
  1. Login as david
  2. Select Find a Product
  3. Type "mouse"
Expected: W_MOUSE-101 row shown with location
Result: PASS

--- TC14: Complete Order ---
Steps:
  1. Login as david
  2. Select Complete an Order
  3. Select ORD101
  4. Confirm yes
Expected: Order marked completed. Stock for
  W_MOUSE-101 goes from 500 to 450,
  KEYBOARD-102 stock reduced by 30.
Result: PASS

--- TC15: Cannot Edit Completed Order ---
Steps:
  1. Login as manager
  2. Try to edit ORD101
Expected: "Cannot edit a completed order."
Result: PASS

--- TC16: Export Inventory Report ---
Steps:
  1. Manager > Reports > Export Inventory Report
  2. Enter filename: inventory_test
Expected: inventory_test.csv created in working directory
Result: PASS

--- TC17: Invalid Menu Input ---
Steps:
  1. At any menu, enter a letter or negative number
Expected: "Please enter a valid number" shown, re-prompts
Result: PASS

--- TC18: Delete Product ---
Steps:
  1. Add a test product: ID=TEST-001
  2. Delete it, confirm yes
Expected: Product removed from list
Result: PASS
