Example of entering a string containing multiple queries
select * from;
CREATE OR REPLACE TRIGGER %s.%s_SERIAL_TRG
BEFORE INSERT ON %s
FOR EACH ROW
BEGIN
SELECT %s_SERIAL_SEQ.nextval INTO :new.%s FROM dual;
END;/
select * from;  

Output:
-----------[SQL]----------
select * from
-----------[PLSQL]----------
CREATE OR REPLACE TRIGGER %s.%s_SERIAL_TRG
BEFORE INSERT ON %s
FOR EACH ROW
BEGIN
SELECT %s_SERIAL_SEQ.nextval INTO :new.%s FROM dual;
END;
-----------[SQL]----------
select * from
