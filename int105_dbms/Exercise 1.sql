-- Exercise 1 Table manipulation commands
-- 1.1 Create tables

-- creates a table of given schema
CREATE TABLE Product_Info(
  Maker VARCHAR2(10),
  Model_No CHAR(5),
  Product_Type CHAR(2)
);

-- schema of the table
DESC Product_Info;

CREATE TABLE PC(
  Model_No CHAR(5),
  Speed NUMBER(3, 2),
  RAM NUMBER(5, 0),
  HD NUMBER(3, 0),
  CD NUMBER(3, 0),
  Price NUMBER(8, 2)
);

DESC PC;

CREATE TABLE Laptop(
  Model_No CHAR(5),
  Speed NUMBER(3, 2),
  RAM NUMBER(5, 0),
  HD NUMBER(3, 0),
  Screensize NUMBER(3, 0),
  Price NUMBER(8, 2)
);

DESC Laptop;

CREATE TABLE Printer(
  Model_No CHAR(5),
  Color VARCHAR2(5),
  Print_Type VARCHAR2(5),
  Price NUMBER(8, 2)
);

DESC Printer;

-- 1.1a Check if the tables are created
SELECT * FROM tab; -- displays all the tables

-- 1.2 Alter product info to make Product_Type non null
ALTER TABLE Product_Info MODIFY (Product_Type NOT NULL);
DESC Product_Info;

-- 1.3 Alter the table pc to have a default speed of 2.
ALTER TABLE PC MODIFY (Speed DEFAULT 2);
Select DATA_DEFAULT From USER_TAB_COLUMNS
  where TABLE_NAME = 'PC' AND COLUMN_NAME = 'SPEED';

-- 1.4 Create suitable primary keys for the tables.
ALTER TABLE Product_Info MODIFY (Model_No PRIMARY KEY);
ALTER TABLE PC MODIFY (Model_No PRIMARY KEY);
ALTER TABLE Laptop MODIFY (Model_No PRIMARY KEY);
ALTER TABLE Printer MODIFY (Model_No PRIMARY KEY);
-- 1.4a Check if the primary keys are created.
SELECT CONSTRAINT_NAME, TABLE_NAME FROM User_Constraints
  WHERE CONSTRAINT_TYPE = 'P';

-- 1.5 Create suitable foreign keys for the tables.
ALTER TABLE PC ADD CONSTRAINT fk_pc_model_no
  FOREIGN KEY (Model_No) REFERENCES Product_Info(Model_No);
ALTER TABLE Laptop ADD CONSTRAINT fk_laptop_model_no
  FOREIGN KEY (Model_No) REFERENCES Product_Info(Model_No);
ALTER TABLE Printer ADD CONSTRAINT fk_printer_model_no
  FOREIGN KEY (Model_No) REFERENCES Product_Info(Model_No);
-- 1.5a Check if the foreign keys are created.
SELECT CONSTRAINT_NAME, TABLE_NAME FROM User_Constraints
  WHERE CONSTRAINT_TYPE = 'R';

-- 1.5b Demonstrate the use of on delete cascade
-- dropping old constraint as it doesn't have on delete cascade
ALTER TABLE PC DROP CONSTRAINT fk_pc_model_no;
SELECT CONSTRAINT_NAME FROM User_Constraints;
-- now adding foreign key with on delete cascade
ALTER TABLE PC ADD CONSTRAINT fk_pc_model_no
  FOREIGN KEY (Model_No) REFERENCES Product_Info(Model_No)
  ON DELETE CASCADE;
INSERT INTO Product_Info VALUES ('HCL', 'PC111', 'PC');
INSERT INTO PC VALUES ('PC111', 2, 256, 60, 52, 40000);
SELECT * FROM Product_Info;
SELECT * FROM PC;
DELETE FROM Product_Info WHERE Model_No = 'PC111';
SELECT * FROM Product_Info;
SELECT * FROM PC;
-- the reference cascaded and deleted the child table's values as well

-- 1.6 Add check constraints
-- 1.6a Product type should be pc, lp and pr only
ALTER TABLE Product_Info ADD CONSTRAINT prod_type_ip_val
  CHECK (Product_Type in ('PC', 'LP', 'PR'));
-- 1.6b Price should be positive
ALTER TABLE PC ADD CONSTRAINT pc_price_pos
  CHECK (Price >= 0);
ALTER TABLE Laptop ADD CONSTRAINT laptop_price_pos
  CHECK (Price >= 0);
ALTER TABLE Printer ADD CONSTRAINT printer_price_pos
  CHECK (Price >= 0);
-- 1.6c Check if the constraints are created
SELECT CONSTRAINT_NAME, SEARCH_CONDITION
  FROM User_Constraints WHERE CONSTRAINT_TYPE = 'C';

/* 1.7 Constraint types
 * R - foreign key (reference)
 * P  - primary key
 * C - check
*/

-- 1.8 Modify the table printer by adding a column printercode of type
-- varchar2(10) to identify the printer uniquely in the world.
ALTER TABLE Printer ADD (Printercode VARCHAR2(10) UNIQUE);
DESC Printer;

-- 1.9 Check if unique constraint was applied
SELECT CONSTRAINT_NAME, CONSTRAINT_TYPE, TABLE_NAME FROM User_Constraints;

-- 1.10 Increase the width of the column printercode by 2
ALTER TABLE Printer MODIFY (Printercode VARCHAR2(12));

-- 1.11 Without removing the table definition from the database remove
-- all the rows from the table 'PC'.
INSERT INTO Product_Info VALUES ('HCL', 'PC111', 'PC');
INSERT INTO PC VALUES ('PC111', 2, 256, 60, 52, 40000);
DELETE FROM PC;

-- 1.12 Drop the table 'PC'.
DROP TABLE PC;
SELECT TNAME FROM tab;

-- Misc: Multiple insert in Oracle DB
INSERT INTO Product_Info VALUES (&Maker, &Model_No, &Product_Type);

-- Misc: Save file (doesn't work? :thinking:)
-- spool d:/commands.txt;