-- Exercise 2 Data manipulation commands
-- 2.1 Insert the following tuples in product_info
INSERT INTO Product_Info VALUES ('HCL', 'PC112', 'PC');
INSERT INTO Product_Info VALUES ('HCL', 'LP113', 'LP');
INSERT INTO Product_Info VALUES ('ZENITH', 'PR114', 'PR');
INSERT INTO Product_Info VALUES ('WIPRO', 'PC122', 'PC');
INSERT INTO Product_Info VALUES ('WIPRO', 'LP123', 'LP');
INSERT INTO Product_Info VALUES ('WIPRO', 'PR124', 'PR');
INSERT INTO Product_Info VALUES ('IBM', 'PC134', 'PC');
INSERT INTO Product_Info VALUES ('HCL', 'LP114', 'LP');
INSERT INTO Product_Info VALUES ('IBM', 'PC132', 'PC');
INSERT INTO Product_Info VALUES ('IBM', 'LP133', 'LP');
INSERT INTO Product_Info VALUES ('IBM', 'PR134', 'PR');
SELECT * FROM Product_Info;

-- 2.2 Insert the following tuples in PC
INSERT INTO PC VALUES ('PC112', 2, 256, 60, 52, 40000);
INSERT INTO PC VALUES ('PC122', 2, 256, 60, 48, 42000);
INSERT INTO PC VALUES ('PC132', 1, 128, 100, 68, 50000);
INSERT INTO PC VALUES ('PC134', 1, 512, 60, 68, 80000);
SELECT * FROM PC;

-- 2.3 Insert the following tuples in Laptop
INSERT INTO Laptop VALUES ('LP113', 1, 64, 40, 14, 59000);
INSERT INTO Laptop VALUES ('LP123', 2, 128, 60, 16, 72000);
INSERT INTO Laptop VALUES ('LP133', 2, 256, 80, 17, 100000);
INSERT INTO Laptop VALUES ('LP114', 2, 128, 40, 17, 45000);
SELECT * FROM Laptop;

-- 2.4 Insert the following tuples in Printer
ALTER TABLE Printer DROP COLUMN PrinterCode;
INSERT INTO Printer VALUES ('PR114', 'TRUE', 'INK', 17000);
INSERT INTO Printer VALUES ('PR124', 'FALSE', 'DOT', 12000);
INSERT INTO Printer VALUES ('PR134', 'TRUE', 'LASER', 17000);
SELECT * FROM Printer;

-- 2.5 Insert a tuple such that the model value is PC100, it is manufactured by
-- HCL and has a speed of 3 GHz, RAM of 256 MB, HD of 40 GB and
-- CD of speed 52x. The price is 50000.
INSERT INTO Product_Info VALUES ('HCL', 'PC100', 'PC');
INSERT INTO PC VALUES ('PC100', 3, 256, 40, 52, 50000);
SELECT * FROM Product_Info WHERE Model_No = 'PC100';
SELECT * FROM PC WHERE Model_No = 'PC100';

-- 2.6 Display all the records from the Product_Info table.
SELECT * FROM Product_Info;

-- 2.7 Delete all PCs with less than 50 CD speed.
DELETE FROM Product_Info WHERE
  Model_No IN (SELECT Model_No FROM PC WHERE CD < 50);
SELECT Model_No FROM PC WHERE CD < 50;
-- due to on delete cascade

-- 2.8 Update all the rows of the printer table, such that the price is
-- increased by 12% for Ink Jet Printers, 14% for Dot Matrix Printers, 10%
-- for Laser Printers. (using separate Update as well as
-- single update statements)
SELECT * FROM Printer;
-- 2.8a Multiple update statements
UPDATE Printer SET Price = 1.12*Price WHERE Print_Type = 'INK';
UPDATE Printer SET Price = 1.14*Price WHERE Print_Type = 'DOT';
UPDATE Printer SET Price = 1.1*Price WHERE Print_Type = 'LASER';
-- 2.8b Single update statements
UPDATE Printer SET Price = DECODE(
  Print_Type,
  'INK', 1.12 * Price,
  'DOT', 1.14 * Price,
  'LASER', 1.1 * Price
);

-- 2.9 Update the Laptop table to increase the price by 12.33% for only those
-- laptops with a speed of >= 2 and manufactured by HCL or IBM.
UPDATE Laptop SET Price = 1.1233 * Price
  WHERE Speed >= 2
  AND Model_No IN (
    SELECT Model_No FROM Product_Info
      WHERE Maker IN ('HCL', 'IBM')
      AND Product_Type = 'LP'
  );

-- 2.10 Insert into Laptop table, all the rows from the PC table with the
-- following considerations:
-- a. If the model number for the PC row is PCxxx, the model number in the
-- Laptop table should be LPxxx. ( Hint : Omit the CD column )
-- b. Keep the screen size as a constant value of 17.
-- c. Price should be greater than 15,000. 
INSERT INTO Product_Info
  SELECT
    Maker,
    REPLACE(Model_No, 'PC', 'LP'),
    REPLACE(Product_Type, 'PC', 'LP')
  FROM Product_Info WHERE Product_Type = 'PC';
INSERT INTO Laptop
  SELECT REPLACE(Model_No, 'PC', 'LP'), Speed, RAM, HD, 17, Price From PC
  WHERE Price > 15000;
SELECT * FROM Laptop;
SELECT * FROM PC;

-- Misc: Row ids of a table data
SELECT ROWID FROM Printer;
SELECT 17 FROM PC;
