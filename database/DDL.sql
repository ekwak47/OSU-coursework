-- Employees table
CREATE TABLE Employees (
    employeeID INT AUTO_INCREMENT PRIMARY KEY,
    firstName VARCHAR(255) NOT NULL,
    lastName VARCHAR(255) NOT NULL,
    email VARCHAR(255),
    phone VARCHAR(12),
    role VARCHAR(255) NOT NULL
);

-- Customers table
CREATE TABLE Customers (
    customerID INT AUTO_INCREMENT PRIMARY KEY,
    firstName VARCHAR(255) NOT NULL,
    lastName VARCHAR(255) NOT NULL,
    email VARCHAR(255),
    phone VARCHAR(12),
    address VARCHAR(255)
);

-- Suppliers table
CREATE TABLE Suppliers (
    supplierID INT AUTO_INCREMENT PRIMARY KEY,
    supplierName VARCHAR(255) NOT NULL,
    location VARCHAR(255) NOT NULL
);

-- Products table
CREATE TABLE Products (
    productID INT AUTO_INCREMENT PRIMARY KEY,
    category VARCHAR(255) NOT NULL CHECK (category IN ('Basketball', 'Tennis', 'Golf', 'Soccer', 'Football')),
    name VARCHAR(255) NOT NULL,
    price DECIMAL(10, 2) NOT NULL,
    quantity INT NOT NULL
);

-- PurchaseOrders table
CREATE TABLE PurchaseOrders (
    purchaseID INT AUTO_INCREMENT PRIMARY KEY,
    supplierID INT NOT NULL,
    purchaseStatus VARCHAR(255) NOT NULL,
    purchaseDate DATE NOT NULL,
-- keep purchase orders when supplier is deleted but update to suppliers should update purchaseorders
    FOREIGN KEY (supplierID) REFERENCES Suppliers(supplierID) ON UPDATE CASCADE
);

-- Orders table
CREATE TABLE Orders (
    orderID INT AUTO_INCREMENT PRIMARY KEY,
    customerID INT NOT NULL,
    -- initially set employee to NULL as optional
    employeeID INT NULL,
    orderType VARCHAR(255) NOT NULL,
    orderStatus VARCHAR(255) NOT NULL,
    orderDate DATE NOT NULL,
    total DECIMAL(10, 2) NOT NULL,
-- Keep previous orders for deleted customers, since employee is optional no need to cascade
    FOREIGN KEY (customerID) REFERENCES Customers(customerID) ON UPDATE CASCADE,
    FOREIGN KEY (employeeID) REFERENCES Employees(employeeID) ON UPDATE CASCADE 
);

-- Junction table for Orders and Products (OrderProducts)
CREATE TABLE OrderProducts (
    productID INT,
    orderID INT,
    quantity INT NOT NULL,
    priceAtSale INT NOT NULL,
    PRIMARY KEY (productID, orderID),
-- keep order productID in the case it is deleted
    FOREIGN KEY (productID) REFERENCES Products(productID) ON UPDATE CASCADE,
    FOREIGN KEY (orderID) REFERENCES Orders(orderID) ON DELETE CASCADE ON UPDATE CASCADE
);

-- Junction table for Products and PurchaseOrders (ProductsPurchaseOrders)
CREATE TABLE PurchaseOrderProducts (
    productID INT,
    purchaseID INT,
    quantity INT NOT NULL,
    unitPrice DECIMAL(10, 2) NOT NULL,
    PRIMARY KEY (productID, purchaseID),
    FOREIGN KEY (productID) REFERENCES Products(productID) ON UPDATE CASCADE,
    FOREIGN KEY (purchaseID) REFERENCES PurchaseOrders(purchaseID) ON DELETE CASCADE ON UPDATE CASCADE
);

INSERT INTO Employees (firstName, lastName, email, phone, role) VALUES
('John', 'Wick', 'johnwick@example.com', 2062062062, 'Sales Associate'),
('Matt', 'Russo', 'mattrusso@example.com', 2092092092, 'Manager'),
('Sarah', 'Miller', 'sarahmiller@example.com', 3513513513, 'Sales Associate');

INSERT INTO Customers (firstName, lastName, email, phone, address) VALUES
('Michael', 'Wilson', 'michaelwilson@example.com', 1234567891, '221 Jane St'),
('James', 'Turner', 'jamesturner@example.com', 1234567892, '341 River Ave'),
('Emily', 'Johnson', 'emilyjohnson@example.com', 1234567893, '777 Mission');

INSERT INTO Suppliers (supplierName, location) VALUES
('Best Sports Goods', 'Chicago'),
('All Sports Inc', 'Beijing'),
('Athletics Supplies Ltd.', 'New Jersey');

INSERT INTO Products (productID, category, name, price, quantity) VALUES
(1, 'Basketball', 'Size 7 Performance Basketball', 59.99, 30),
(2, 'Tennis', 'Winners Tennis Racket', 119.99, 30),
(3, 'Golf', 'Golf Gloves', 49.99, 50),
(4, 'Soccer', 'Indoor Soccer Ball', 36.99, 40),
(5, 'Football', 'Grit Football Helmet', 79.99, 25);

INSERT INTO Orders (customerID, employeeID, orderType, orderStatus, orderDate, total) VALUES
(1, 1, 'Store Pickup', 'Completed', '2024-02-01', 120.00),
(3, 3, 'Retail', 'Completed', '2024-02-03', 300.00),
(2, 3, 'Online', 'Shipped', '2024-02-05', 239.00);

INSERT INTO OrderProducts (orderID, productID, priceAtSale, quantity) VALUES
(1, 1, 59.99, 2),
(2, 4, 39.99, 8),
(3, 3, 49.99, 5);

INSERT INTO PurchaseOrders (supplierID, purchaseStatus, purchaseDate) VALUES
(1, 'Processed', '2024-01-25'),
(2, 'Shipped', '2024-02-03'),
(3, 'Completed', '2024-02-08');

INSERT INTO PurchaseOrderProducts (purchaseID, productID, unitPrice, quantity) VALUES
(1, 1, 5.99, 40),
(1, 3, 19.99, 30),
(2, 3, 18.59, 60),
(3, 2, 23.00, 20);