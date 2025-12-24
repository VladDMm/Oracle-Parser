Example of entering a string containing multiple queries <br />
select * from;<br />
CREATE OR REPLACE TRIGGER %s.%s_SERIAL_TRG<br />
BEFORE INSERT ON %s<br />
FOR EACH ROW<br />
BEGIN<br />
SELECT %s_SERIAL_SEQ.nextval INTO :new.%s FROM dual;<br />
END;/<br />
select * from; <br /> 

Output:<br />
-----------[SQL]----------<br />
select * from<br />
-----------[PLSQL]----------<br />
CREATE OR REPLACE TRIGGER %s.%s_SERIAL_TRG<br />
BEFORE INSERT ON %s<br />
FOR EACH ROW<br />
BEGIN<br />
SELECT %s_SERIAL_SEQ.nextval INTO :new.%s FROM dual;<br />
END;<br />
-----------[SQL]----------<br />
select * from<br />
