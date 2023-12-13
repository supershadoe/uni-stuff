-- Exercise 3 Arithmetic, Logical, Set Operations, Sorting and
-- grouping Operations

-- 3.1 List those rows of the table PC where RAM sizes are either ‘128’ or ‘256’
-- and the capacity of HD is greater than or equal to 50.
SELECT * FROM PC WHERE RAM IN (128, 256) AND HD >= 50;

-- 3.2 List all the rows from PRINTER except the printers ‘PR112’ or ‘PR124’.
SELECT * FROM Printer WHERE Model_No NOT IN ('PR112', 'PR124');

-- 3.3 List all the rows from LAPTOP in ascending and descending order
-- of the screen size.
SELECT * FROM Laptop ORDER BY Screensize ASC;
SELECT * FROM Laptop ORDER BY Screensize DESC;

-- 3.4 List the makers of PC’s. Use ‘like’ operator in the model field
-- (don’t use type).
SELECT MAKER FROM Product_Info WHERE Model_No LIKE 'PC%';

-- 3.5 List the laptop details where the screen size is not 17.
SELECT * FROM Laptop WHERE Screensize != 17;

-- 3.6 List the printers whose price is between 5000 and 10000. (Use between).
SELECT * FROM Printer WHERE Price BETWEEN 5000 AND 10000;

-- 3.7 Display the PC details if we double the ram capacity. (Don’t update).
SELECT Model_No, Speed, RAM*2 DRAM, HD, CD, Price FROM PC;

-- 3.8 Display the printer details with the following columnname as heading.
-- "PRINTER MODEL" COLORINFO PRINTERTYPE PRICE
SELECT
  Model_No "PRINTER MODEL",
  Color "COLORINFO",
  Print_Type "PRINTERTYPE",
  Price
  FROM Printer;

-- 3.9 create 2 tables and then perform union, union all, intersect,
-- minus
CREATE TABLE WORKER(
  Worker_Name VARCHAR2(30),
  Age NUMBER(3, 0)
);
CREATE TABLE WORKERSKILL(
  Worker_Name VARCHAR2(30),
  Skill VARCHAR2(15),
  City VARCHAR2(10),
  Phone VARCHAR2(15)
);
INSERT INTO WORKER VALUES (&Worker_Name, &Age);
INSERT INTO WORKERSKILL VALUES (&Worker_Name, &Skill, &City, &Phone);

SELECT Worker_Name FROM WORKER UNION SELECT Worker_Name FROM WORKERSKILL;
SELECT Worker_Name FROM WORKER UNION ALL SELECT Worker_Name FROM WORKERSKILL;
SELECT Worker_Name FROM WORKER INTERSECT SELECT Worker_Name FROM WORKERSKILL;
SELECT Worker_Name FROM WORKER MINUS SELECT Worker_Name FROM WORKERSKILL;

-- 3.10 For each value of RAM, list the number of PCs (use group by function).
SELECT RAM, COUNT(*) FROM PC GROUP BY RAM;

-- 3.11 For each value of HD, list the number of PCs (use group by function).
SELECT HD, COUNT(*) FROM PC GROUP BY HD;

-- 3.12 List the HD values for which the number of PCs is more than 2.
-- (Use group by and having clause).
SELECT HD, COUNT(*) FROM PC GROUP BY HD HAVING COUNT(*) > 2;
