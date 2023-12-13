-- Exercise 4 Built-in functions and nested queries

-- 4.1 Find the difference between the highest and lowest price from laptop
SELECT MAX(Price) - MIN(Price) Difference FROM Laptop;

-- 4.2 Find the Standard deviation and Variance of price in PC table.
SELECT STDDEV(Price), VARIANCE(Price) FROM PC;

-- 4.3 Use a specific command to get the data in the following manner:
-- WORKER_NAME AGE
-- JACK ADAMS --31
SELECT Worker_Name, CONCAT('--', Age) Age FROM WORKER;

-- 4.4a Update the PC table such that, the price for all PC models is
-- increased by 12.33%.
UPDATE PC SET Price = Price * 1.1233;
-- 4.4b Display the PC model in lowercase and price rounded to the
-- hundredths for all the PCs.
SELECT LOWER(Model_No), ROUND(Price, 2) FROM PC;

-- 4.5 List the names in the ascending order of the length of names
-- from WORKER table.
SELECT Worker_Name FROM WORKER ORDER BY LENGTH(Worker_Name) ASC;

-- 4.6 List the phone number (eliminate area code like 91-0437)
-- of all employees from WORKERSKILL table.
SELECT * FROM WORKERSKILL;
SELECT Worker_Name, SUBSTR(Phone, 9) "PHONE NO" FROM WORKERSKILL;

-- 4.7 Find the location of letter ‘A’ in the employee name of
-- WORKERSKILL table. (Hint: Use INSTR())
SELECT Worker_Name, INSTR(Worker_Name, 'A') "LOCATION OF A" FROM WORKERSKILL;

-- 4.8 Use SOUNDEX() function on WORKERSKILL table to find a record with column
-- city sounding like 'Sidney'
SELECT * FROM WORKERSKILL WHERE SOUNDEX(City) = SOUNDEX('Sidney');

-- 4.9 Display the current date/time in the following formats:
-- a. Sep-2006
-- b. September 12 2006
-- c. 12-09-06 12:11:10
SELECT TO_CHAR(SYSDATE, 'MON-YYYY') "9a" FROM DUAL;
SELECT TO_CHAR(SYSDATE, 'MONTH DD YYYY') "9b" FROM DUAL;
SELECT TO_CHAR(SYSDATE, 'DD-MM-YY HH:MI:SS') "9c" FROM DUAL;

-- 4.10 Give examples for replace, decode and translate functions.
SELECT REPLACE('DID', 'DI', 'MI') FROM DUAL;
SELECT TRANSLATE('DID', 'DI', 'MI') FROM DUAL;
CREATE TABLE Words(Word VARCHAR2(10));
INSERT INTO Words VALUES (&Word);
SELECT
  Word,
  DECODE(Word, 'MAN', 'PAN', 'MEN', 'PEN', 'MIN', 'PIN', 'IDK') DECODED
  FROM Words;

-- 4.11 Display the printer information whose price is equal to any one of the
-- printer manufactured by ‘IBM’.
CREATE VIEW PrinterMaker AS
  SELECT Printer.Model_No, Color, Price, Print_Type, Maker
    FROM Printer
    JOIN Product_Info
    ON Product_Info.Model_No = Printer.Model_No;
SELECT P1.Model_No, P1.Color, P1.Print_Type, P1.Price
  FROM PrinterMaker P1
  CROSS JOIN PrinterMaker P2
  WHERE P2.Maker = 'IBM' AND P1.Price = P2.Price;
UPDATE Printer SET Price = 18700 WHERE Model_No = 'PR114';
SELECT P1.Model_No, P1.Color, P1.Print_Type, P1.Price
  FROM PrinterMaker P1
  CROSS JOIN PrinterMaker P2
  WHERE P2.Maker = 'IBM' AND P1.Price = P2.Price;
UPDATE Printer SET Price = 19040 WHERE Model_No = 'PR114';

-- 4.12 List the laptop details whose screen size is equal to the screen size
-- of ‘lp114’.
SELECT L1.Model_No, L1.Speed, L1.RAM, L1.HD, L1.Screensize, L1.Price
  FROM Laptop L1
  CROSS JOIN Laptop L2
  WHERE L2.Model_No = 'LP114' AND L1.Screensize = L2.Screensize;