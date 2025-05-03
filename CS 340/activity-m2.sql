/*
    TASK 1 - CREATE A CUSTOMER OBJECT TABLE

    ! NOTES !

    Anytime you see [SQUARE BRACKETS] it means something that is optional.

    Anytime you see ... three dots - it means continued iterations of the same thing.
*/



/*
    CREATE THE CUSTOMERS TABLE

    Create the table customers, replace it if it exists, defined by the columns within the parentheses.

    We can use CREATE OR REPLACE instead of putting the usual DROP IF EXISTS statements at the top of the SQL file.

    The general syntax of CREATE [OR REPLACE] (Square brackets indicates its optional) is:

    CREATE [OR REPLACE] tableName 
    (
        columnName datatype constraints,
        ...
        [[PRIMARY KEY (columnName, ...)],
        FOREIGN KEY (columnName) REFERENCES primaryTableName(primaryKey, ...)]
    );
*/

CREATE OR REPLACE TABLE Customers (
    CustomerID int NOT NULL AUTO_INCREMENT,
    CustomerName varchar(50),
    AddressLine1 varchar(50),
    AddressLine2 varchar(50),
    City varchar(50),
    State varchar(50),
    PostalCode varchar(50),
    YTDPurchases decimal(19,2),
    PRIMARY KEY (CustomerID)
)  ENGINE = InnoDB;


INSERT INTO Customers (CustomerID, CustomerName, AddressLine1, AddressLine2, City, State, PostalCode, YTDPurchases)
VALUES
(1, 'Bike World', '60025 Bollinger Canyon Road', NULL, 'San Ramon', 'California', '94583', NULL),
(2, 'Metro Sports', '482505 Warm Springs Blvd', NULL, 'Fremont', 'California', '94536', NULL),
(3, 'Encina Bikes', '1232 Clayton Road', NULL, 'Clayton', 'California', '94524', NULL),
(4, 'Dicks Sporting Goods', '1232 Monument Blvd', NULL, 'Pleasant Hill', 'California', '94523', NULL);


CREATE TABLE TermsCode (
    TermsCodeID varchar(50) NOT NULL,
    Description varchar(50),
    PRIMARY KEY (TermsCodeID)
);

INSERT INTO TermsCode (TermsCodeID, Description)
VALUES
('NET30', 'Payment due in 30 days.'),
('NET15', 'Payment due in 15 days.'),
('210NET30', '2% discount in 10 days Net 30');


CREATE TABLE Invoices (
    InvoiceID int NOT NULL AUTO_INCREMENT,
    CustomerID int,
    InvoiceDate datetime,
    TermsCodeID varchar(50),
    TotalDue decimal(19,2),
    PRIMARY KEY (InvoiceID),
    FOREIGN KEY (CustomerID) REFERENCES Customers(CustomerID),
    FOREIGN KEY (TermsCodeID) REFERENCES TermsCode(TermsCodeID)
);

INSERT INTO Invoices (InvoiceID, CustomerID, InvoiceDate, TermsCodeID, TotalDue)
VALUES
(1, '2', '20140207', 'NET30', '2388.98'),
(2, '1', '20140202', '210NET30', '2443.35'),
(3, '1', '20140209', 'NET30', '8752.32');
