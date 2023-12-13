set serveroutput on;

-- 1. Write a program to print the numbers from 1 to 100
begin
    for i in 1..100
        loop
            DBMS_OUTPUT.PUT_LINE(i);
        end loop;
end;
/

-- 2. write a program to print the even numbers from 1 to 100
declare
    i integer := 2;
begin
    while i <= 100
        loop
            DBMS_OUTPUT.PUT_LINE(i);
            i := i + 2;
        end loop;
end;
/

-- 3. Write a program to print the odd numbers from 1 to 100
declare
    i integer := 1;
begin
    while i <= 100
        loop
            DBMS_OUTPUT.PUT_LINE(i);
            i := i + 2;
        end loop;
end;
/

-- 4. write a program for multiplication table
declare
    n integer := &n;
begin
    for i in 1..12
        loop
            DBMS_OUTPUT.PUT_LINE(n || ' * ' || i || ' = ' || i * n);
        end loop;
end;
/

-- 5. write a program to find the sum of numbers from 1 to 100
declare
    s integer := 0;
begin
    for i in 1..100
        loop
            s := s + i;
        end loop;
    DBMS_OUTPUT.PUT_LINE('The sum of 1..100 is ' || s);
end;
/

-- 6. Write a program to find the sum of all odd numbers from 1 to 100
declare
    i integer := 1;
    s integer := 0;
begin
    while i <= 100
        loop
            s := s + i;
            i := i + 2;
        end loop;
    DBMS_OUTPUT.PUT_LINE('The sum of odd numbers 1..100 is ' || s);
end;
/

-- 7. Write a program to find the sum of all even numbers from 1 to 100
declare
    i integer := 2;
    s integer := 0;
begin
    while i <= 100
        loop
            s := s + i;
            i := i + 2;
        end loop;
    DBMS_OUTPUT.PUT_LINE('The sum of even numbers 1..100 is ' || s);
end;
/

-- 8. Write a program to accept a number and find how many digits it contain
declare
    n integer := &n;
begin
    DBMS_OUTPUT.PUT_LINE(
      'The number of digits in ' || n || ' is ' || (FLOOR(LOG(10, n)) + 1)
    );
end;
/

-- 9. Write a program to accept a number and find the sum of the digits
declare
    n integer := &n;
    s integer := 0;
    temp integer;
begin
    temp := n;
    while temp > 0
        loop
            s := s + MOD(temp, 10);
            temp := FLOOR(temp / 10);
        end loop;
    DBMS_OUTPUT.PUT_LINE('The number of digits in ' || n || ' is ' || s);
end;
/

-- 10. Write a program to accept a number and print it in reverse order
declare
    n integer := &n;
    r integer := 0;
    temp integer;
begin
    temp := n;
    while temp > 0
        loop
            r := (r * 10) + MOD(temp, 10);
            temp := FLOOR(temp / 10);
        end loop;
    DBMS_OUTPUT.PUT_LINE('The reverse of ' || n || ' is ' || r);
end;
/

-- 11. Write a program to accept a no and check whether it is Armstrong
-- number or not
declare
    n integer := &n;
    d integer := 0;
    s integer := 0;
    temp integer;
begin
    d := FLOOR(LOG(10, n)) + 1;
    -- do digit ** no of digits and sum them up
    temp := n;
    while temp > 0
        loop
            s := s + POWER(MOD(temp, 10), d);
            temp := FLOOR(temp / 10);
        end loop;
    if s = n
        then
          DBMS_OUTPUT.PUT_LINE('The given number is an armstrong number.');
        else
          DBMS_OUTPUT.PUT_LINE('The given number is not an armstrong number.');
        end if;
end;
/

-- 12. Write a porgram to generate all the Armstrong numbers from 1 to 1000
declare
    d integer := 0;
    s integer := 0;
    temp integer;
begin
    DBMS_OUTPUT.PUT_LINE('The armstrong numbers from 1 to 1000 are as follows.');
    for i in 1..1000
        loop
            d := FLOOR(LOG(10, i)) + 1;
            temp := i;
            -- do digit ** no of digits and sum them up
            s := 0;
            while temp > 0
                loop
                    s := s + POWER(MOD(temp, 10), d);
                    temp := FLOOR(temp / 10);
                end loop;
            if s = i
                then
                    DBMS_OUTPUT.PUT_LINE(i);
                end if;
        end loop;
end;
/

-- 13. Write a program to generate all prime numbers between 1 to 100
declare
    is_prime boolean;
begin
    DBMS_OUTPUT.PUT_LINE('The prime numbers from 1 to 100 are as follows.');
    for i in 2..100
        loop
            is_prime := TRUE;
            for j in 2..ABS(i/2)
                loop
                    if MOD(i, j) = 0
                        then
                            is_prime := FALSE;
                            exit;
                        end if;
                end loop;
            if is_prime
                then
                    DBMS_OUTPUT.PUT_LINE(i);
                end if;
        end loop;
end;
/

-- 14. Write a program to aceept a number and check whether it is prime number
-- or not
declare
    n integer := &n;
    is_prime boolean;
begin
    is_prime := TRUE;
    for i in 2..ABS(n/2)
        loop
            if MOD(n, i) = 0
                then
                    is_prime := FALSE;
                    DBMS_OUTPUT.PUT_LINE(n || ' is non-prime.');
                    exit;
                end if;
        end loop;
    if is_prime
        then
            DBMS_OUTPUT.PUT_LINE(n || ' is prime.');
        end if;
end;
/

-- 15. Write a program to display the fibonacci series from 1 to 10
declare
    n1 integer := 1;
    n2 integer := 1;
    f integer;
begin
    DBMS_OUTPUT.PUT_LINE('The fibonacci series from 1 to 10 is as follows.');
    DBMS_OUTPUT.PUT_LINE(n1);
    DBMS_OUTPUT.PUT_LINE(n2);
    f := n1 + n2;
    while f <= 10
        loop
            DBMS_OUTPUT.PUT_LINE(f);
            n1 := n2;
            n2 := f;
            f := n1 + n2;
        end loop;
end;
/

-- 16. Write a program to aceept a number and print it in binary format
declare
    n integer := &n;
    bin varchar2(32) := '';
    temp integer;
begin
    temp := n;
    while temp > 0
        loop
            bin := MOD(temp, 2) || bin;
            temp := FLOOR(temp / 2);
        end loop;
    DBMS_OUTPUT.PUT_LINE(n || ' in binary format is ' || bin);
end;
/

-- 17. Write a program to accept a number and find the factorial of the number
declare
    n integer := &n;
    f integer := 1;
begin
    for i in 1..n
        loop
            f := f * i;
        end loop;
    DBMS_OUTPUT.PUT_LINE('The factorial of ' || n || ' is ' || f);
end;
/

-- Lab exercise: Area of circle
declare
  r integer := &radius;
  area number;
begin
  area := 3.14 * r * r;
  DBMS_OUTPUT.PUT_LINE('The radius of the circle is ' || area);
end;
/