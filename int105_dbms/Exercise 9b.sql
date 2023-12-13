set serveroutput on;

CREATE TABLE emp (empid char(5), emp_name varchar2(30));

create or replace trigger employee before update on emp
  begin
    DBMS_OUTPUT.PUT_LINE('Record(s) updated.');
  end;
/

create or replace trigger emp_trg_1 before update on emp
  for each row
  begin
    DBMS_OUTPUT.PUT_LINE('Record updated.');
  end;
/

insert into emp values('E1232', 'Krishna');
insert into emp values('E1233', 'Ram');
update emp set emp_name = 'Name';

select * from emp;