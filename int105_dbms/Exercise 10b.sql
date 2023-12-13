SET SERVEROUTPUT ON;

DECLARE
  v_name varchar2(30);
  cursor cur_v1 is select emp_name from emp;
begin
  open cur_v1;
  loop
    fetch cur_v1 into v_name;
    exit when cur_v1%notfound;
    dbms_output.put_line(v_name);
  end loop;
  close cur_v1;
end;
/

declare
  rec_sal emp%rowtype;
  cursor cur_sal is select * from emp where salary > 15000 for update;
begin
  open cur_sal;
  loop
    fetch cur_sal into rec_sal;
    exit when cur_sal%notfound;
    delete from emp where current of cur_sal;
  end loop;
  close cur_sal;
end;
/

SELECT * FROM emp;