-- 6 SQL queries for creating views, sequences and synonyms

-- 6.1 Create a view Price_info to include the columns model, maker
-- and price for the PCs.
CREATE VIEW Price_Info AS
  SELECT P.Model_No, Maker, PC.Price
  FROM Product_Info P JOIN PC
  ON P.Model_No = PC.Model_No;

SELECT * FROM Price_Info;

-- 6.2 Create a view Price6000 on the table Printer to include only rows
-- with price > 6000.
CREATE VIEW Price6000 AS
  SELECT * FROM Printer
  WHERE Price > 6000;

SELECT * FROM Price6000;

-- 6.3 Modify one row in both the views and check
-- whether it is reflected in the table and vice versa.
UPDATE PC SET Price = 44932 WHERE Model_No = 'PC112';
SELECT * FROM Price_Info;
SELECT * FROM PC;

UPDATE Printer SET Price = 19040 WHERE Model_No = 'PR114';
SELECT * FROM Price6000;
SELECT * FROM Printer;

-- 6.4 Delete one row from the views. Record the observations.
DELETE FROM PC WHERE Model_No = 'PC112';
SELECT * FROM Price_Info;
SELECT * FROM PC;

DELETE FROM Price6000 WHERE Model_No = 'PR114';
SELECT * FROM Price6000;
SELECT * FROM Printer;

-- 6.5 Create a unique index on the worker name column of the worker table.
CREATE UNIQUE INDEX WorkerName ON Worker(Worker_Name);

-- 6.6 Create a function based index on the city column of the
-- worker table (Use upper, lower or initcap function and test)
INSERT INTO WorkerSkill VALUES
  ('asfhuash', 'saffas', 'chennai', '91-1212-121212');
SELECT UPPER(CITY) FROM WorkerSkill;
CREATE INDEX CityUpper ON WorkerSkill(UPPER(City));
SELECT UPPER(CITY) FROM WOrkerSkill;

-- 6.7 Create a sequence object in ascending order start with 100.
CREATE SEQUENCE UP100 START WITH 100;

-- 6.8 Create a sequence object in descending order start with 100.
CREATE SEQUENCE DOWN100 START WITH 100 INCREMENT BY -1 MAXVALUE 100;

-- 6.9 Use the system variables currval, nextval to pick values from these
-- sequences and demonstrate their usage in insert, update, delete
-- and select statements
INSERT INTO Product_Info VALUES('HCL', CONCAT('PC', UP100.nextval), 'PC');
SELECT * FROM Product_Info;

ALTER TABLE Product_Info ADD (Product_No NUMBER);
UPDATE Product_Info SET Product_No = DOWN100.nextval;
SELECT * FROM Product_Info;
SELECT CONCAT('PC', UP100.currval) "LAST INSERT MODEL" FROM DUAL;

-- 6.10 Create a synonym object for worker skill with the name ‘G20K’.
CREATE SYNONYM G20K FOR WorkerSkill;
SELECT * FROM G20K;