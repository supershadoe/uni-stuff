-- Create a procedure to display the printer details by accepting the
-- Model_No as an input
SET SERVEROUTPUT ON;

CREATE OR REPLACE PROCEDURE printer_details (ModelNo IN CHAR) IS
  Color VARCHAR2(5);
  Print_Type VARCHAR2(5);
  Price NUMBER(8, 2);
  BEGIN
    SELECT Color, Print_Type, Price
      INTO Color, Print_Type, Price
      FROM Printer
      WHERE Model_No = ModelNo;
    DBMS_OUTPUT.PUT_LINE(
      'The data for this model no ' || ModelNo || ' is as follows.'
    );
    DBMS_OUTPUT.PUT_LINE('Color: ' || Color);
    DBMS_OUTPUT.PUT_LINE('Printer type: ' || Print_Type);
    DBMS_OUTPUT.PUT_LINE('Price: ' || Price);
  END;
/

BEGIN
  printer_details('PR114');
END;
/

-- Create a function to return the price of a printer by accepting the
-- Model_No as an input

CREATE OR REPLACE FUNCTION printer_price(ModelNo IN CHAR) RETURN NUMBER AS
  Price NUMBER(8, 2);
  BEGIN
   SELECT Price INTO Price FROM Printer WHERE Model_No = ModelNo;
   RETURN Price;
  END;
/

DECLARE
  Model_No CHAR(5) := '&Model_No';
BEGIN
  DBMS_OUTPUT.PUT_LINE(
    'The price of printer ' || Model_No || ' is ' || printer_price(Model_No)
  );
END;
/