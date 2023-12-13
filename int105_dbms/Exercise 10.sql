DECLARE
    modelNo CHAR(5);
    price NUMBER(8, 2);
    screen_size NUMBER;
    CURSOR laptop_cur IS (SELECT MODEL_NO, PRICE, SCREENSIZE FROM LAPTOP);
BEGIN
    OPEN laptop_cur;
    LOOP
        FETCH laptop_cur INTO modelNo, price, screen_size;
        EXIT WHEN laptop_cur%notfound;

        DBMS_OUTPUT.PUT_LINE('Old price: ' || price);
        DBMS_OUTPUT.PUT('New price: ');
        IF (screen_size > 15) THEN
            UPDATE LAPTOP SET PRICE = price * 1.1 WHERE MODEL_NO = modelNo;
            DBMS_OUTPUT.PUT_LINE(price * 1.1);
        ELSE
            DBMS_OUTPUT.PUT_LINE(price);
        END IF;
    END LOOP;
    CLOSE laptop_cur;
END;
/