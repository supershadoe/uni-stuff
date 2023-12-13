SET SERVEROUTPUT ON;

CREATE TABLE Sales_Transaction(
  Prod_Code CHAR(4) CHECK (Prod_Code LIKE 'P___'),
  Date_Of_Sale DATE,
  Qty NUMBER CHECK (Qty > 0),
  Price NUMBER CHECK (Price > 0)
);

CREATE TABLE GST_Calculation(
  Date_Of_Sale DATE,
  Prod_Code CHAR(4) CHECK (Prod_Code LIKE 'P___'),
  GST NUMBER
);

CREATE OR REPLACE TRIGGER gst_on_add
  BEFORE INSERT ON Sales_Transaction
  REFERENCING NEW AS n
  FOR EACH ROW
  BEGIN
    INSERT INTO GST_Calculation VALUES(:n.Date_Of_Sale, :n.Prod_Code, :n.Price * 0.1);
    DBMS_OUTPUT.PUT_LINE('Stored GST for the purchase of ' || :n.Prod_Code || '.');
  END;
/

CREATE OR REPLACE TRIGGER gst_on_update
  BEFORE UPDATE ON Sales_Transaction
  REFERENCING NEW AS n
  FOR EACH ROW
  BEGIN
    UPDATE GST_Calculation SET GST = :n.Price * 0.1
      WHERE Prod_Code = :n.Prod_Code AND Date_Of_Sale = :n.Date_Of_Sale;
    DBMS_OUTPUT.PUT_LINE('Updated GST for the purchase of ' || :n.Prod_Code || '.');
  END;
/

CREATE OR REPLACE TRIGGER gst_on_del
  BEFORE DELETE ON Sales_Transaction
  REFERENCING OLD AS o
  FOR EACH ROW
  BEGIN
    DELETE FROM GST_Calculation
      WHERE Prod_Code = :o.Prod_Code AND Date_Of_Sale = :o.Date_Of_Sale;
    DBMS_OUTPUT.PUT_LINE('Deleted GST for the purchase of ' || :o.Prod_Code || '.');
  END;
/

CREATE OR REPLACE TRIGGER calc_gst
  BEFORE INSERT OR UPDATE OR DELETE
  ON Sales_Transaction
  REFERENCING OLD as o NEW AS n
  FOR EACH ROW
  BEGIN
    IF INSERTING THEN
      INSERT INTO GST_Calculation VALUES
        (:n.Date_Of_Sale, :n.Prod_Code, :n.Price * 0.1);
      DBMS_OUTPUT.PUT_LINE(
        'Stored GST for the purchase of ' || :n.Prod_Code || '.'
      );
    ELSIF UPDATING THEN
      UPDATE GST_Calculation SET GST = :n.Price * 0.1
        WHERE Prod_Code = :n.Prod_Code AND Date_Of_Sale = :n.Date_Of_Sale;
      DBMS_OUTPUT.PUT_LINE(
        'Updated GST for the purchase of ' || :n.Prod_Code || '.'
      );
    ELSE
      DELETE FROM GST_Calculation
        WHERE Prod_Code = :o.Prod_Code AND Date_Of_Sale = :o.Date_Of_Sale;
      DBMS_OUTPUT.PUT_LINE(
        'Deleted GST for the purchase of ' || :o.Prod_Code || '.'
      );
    END IF;
  END;
/

INSERT INTO Sales_Transaction VALUES
  ('&Prod_Code', '&Date_Of_Sale', &Qty, &Price);
UPDATE Sales_Transaction SET Price = 2000
  WHERE Prod_Code = 'P004' AND Date_Of_Sale = '02-Jan-2007';
DELETE FROM Sales_Transaction
  WHERE Prod_Code = 'P002' AND Date_Of_Sale = '01-Jan-2007';

SELECT * FROM Sales_Transaction;
SELECT * FROM GST_Calculation;
