SET SERVEROUTPUT ON;

DECLARE
  r INTEGER := &radius;
  area NUMBER;
BEGIN
  area := 3.14 * r * r;
  DBMS_OUTPUT.PUT_LINE('The radius of the circle is ' || area);
END;
/