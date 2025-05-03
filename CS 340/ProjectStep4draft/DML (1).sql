SELECT * FROM Employees;

SELECT * FROM Customers;

SELECT * FROM Suppliers;

SELECT * FROM Products;

-- Orders with JOINs to have customer name added to make more user friendly
SELECT 
    Orders.orderID,
    Orders.customerID,
    CONCAT(Customers.firstName, ' ', Customers.lastName) AS customerName,
    Orders.employeeID,
    Orders.orderType,
    Orders.orderStatus,
    Orders.orderDate,
    Orders.total
FROM Orders
INNER JOIN Customers ON Orders.customerID = Customers.customerID;

-- OrderProducts with JOINS to display product name
SELECT 
    OrderProducts.orderID,
    OrderProducts.productID,
    Products.name AS productName,
    OrderProducts.quantity,
    OrderProducts.priceAtSale
FROM OrderProducts
INNER JOIN Products ON OrderProducts.productID = Products.productID;

-- PurchaseOrders with JOINS to display Supplier name
SELECT 
    PurchaseOrders.purchaseID,
    PurchaseOrders.supplierID,
    Suppliers.name AS supplierName,
    PurchaseOrders.purchaseStatus,
    PurchaseOrders.purchaseDate
FROM PurchaseOrders
INNER JOIN Suppliers ON PurchaseOrders.supplierID = Suppliers.supplierID;

-- PurchaseOrderProducts with JOINS to display product name
SELECT 
    PurchaseOrderProducts.purchaseID,
    PurchaseOrderProducts.productID,
    Products.name AS productName,
    PurchaseOrderProducts.quantity,
    PurchaseOrderProducts.unitPrice
FROM PurchaseOrderProducts
INNER JOIN Products ON PurchaseOrderProducts.productID = Products.productID;

-- Query for add a new character functionality with colon : character being used to 
-- denote the variables that will have data from the backend programming language

-- new employee insert
INSERT INTO Employees (firstName, lastName, email, phone, role) 
    VALUES 
    (:firstNameInput, :lastNameInput, :emailInput, :phoneInput, :roleInput);

-- new customer insert
INSERT INTO Customers (firstName, lastName, email, phone, address) 
    VALUES 
    (:firstNameInput, :lastNameInput, :emailInput, :phoneInput, :addressInput);

-- new supplier insert
INSERT INTO Suppliers (supplierName, location) 
    VALUES 
    (:supplierNameInput, :locationInput);

-- new product insert
INSERT INTO Products (category, name, price, quantity) 
    VALUES 
    (:categoryInput, :nameInput, :priceInput, :quantityInput);

-- new order insert + insert into intersection table
-- order dates are set automatically with CURDATE()
INSERT INTO Orders (customerID, employeeID, orderType, orderStatus, orderDate, total) 
    VALUES 
    (:customerIDInput, :employeeIDInput, :orderTypeInput, :orderStatusInput, CURDATE(), :totalInput);

SET @orderID = LAST_INSERT_ID();
INSERT INTO OrderProducts (orderID, productID, quantity, priceAtSale) 
VALUES (@orderID, :productIDInput, :quantityinput, :priceInput);

-- new purchase order insert + insert into intersection table
-- order dates are set automatically with CURDATE()
INSERT INTO PurchaseOrders (supplierID, purchaseStatus, purchaseDate) 
    VALUES
    (:supplierIDinput, :statusInput, CURDATE());

SET @purchaseID = LAST_INSERT_ID();
INSERT INTO PurchaseOrderProducts (purchaseID, productID, unitPrice, quantity)
    VALUES
    (@purchaseID, :productIDinput, :unitPriceInput, :quantityInput)

-- query to search for orders with inputted customers first name
SELECT 
    Orders.orderID,
    Orders.customerID,
    CONCAT(Customers.firstName, ' ', Customers.lastName) AS customerName,
    Orders.orderDate,
    Orders.total
FROM Orders
INNER JOIN Customers ON Orders.customerID = Customers.customerID
WHERE Customers.firstName LIKE :firstNameInput;

-- query to search for certain order status

SELECT 
    Orders.orderID,
    Orders.customerID,
    CONCAT(Customers.firstName, ' ', Customers.lastName) AS customerName,
    Orders.employeeID,
    Orders.orderType,
    Orders.orderStatus,
    Orders.orderDate,
    Orders.total
FROM Orders
INNER JOIN Customers ON Orders.customerID = Customers.customerID
WHERE Orders.orderStatus LIKE :orderStatusInput;

-- query to search for certain purchase order status
SELECT 
    PurchaseOrders.purchaseID,
    PurchaseOrders.supplierID,
    Suppliers.name AS supplierName,
    PurchaseOrders.purchaseStatus,
    PurchaseOrders.purchaseDate
FROM PurchaseOrders
INNER JOIN Suppliers ON PurchaseOrders.supplierID = Suppliers.supplierID
WHERE PurchaseOrders.purchaseStatus LIKE :purchaseOrderStatusInput;

-- update example for products
UPDATE Products SET quantity = 50 WHERE productID = 1;

-- update status of consumer order 
UPDATE Orders SET orderStatus = 'Completed' where orderID = 1;

-- update status of purchase order
UPDATE PurchaseOrders SET purchaseStatus = 'Shipped' where purchaseID = 1;

-- delete example for M:N, handled by CASCADE in DDL
DELETE FROM OrderProducts WHERE orderID = 3;

-- delete example for M:N, handled by CASCADE in DDL
DELETE FROM PurchaseOrdersProducts WHERE purchaseID = 2;










