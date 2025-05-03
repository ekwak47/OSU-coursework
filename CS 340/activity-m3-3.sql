SELECT Customers.CustomerName, Invoices.InvoiceID, SUM(InvoiceDetails.LineTotal) AS LineSum
FROM Customers
INNER JOIN Invoices ON Customers.CustomerID = Invoices.CustomerID
INNER JOIN InvoiceDetails ON Invoices.InvoiceID = InvoiceDetails.InvoiceID
GROUP BY Invoices.InvoiceID, Customers.CustomerName
ORDER BY LineSum DESC;
--Selects three columns
--Two inner joins to join Customers to Invoices, and Invoices and InvoiceDetails
--Orders by linesum from greatest to least