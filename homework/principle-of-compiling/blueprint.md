
基本SQL语句及功能：  
CREATE DATABASE   	创建数据库  
USE DATABASE 		选择数据库  
CREATE   TABLE		创建表  
SHOW  TABLES  		显示表名  
INSERT		 	插入元组  
SELECT 		 	查询元组  
UPDATE			更新元组  
DELETE			删除元组  
DROP	TABLE 		删除表  
DROP	DATABASE		删除数据库  
EXIT	 			退出系统  
注：支持数据类型有INT、CHAR(N) 等  

Syntax
```sql
CREATE DATABASE database_name;
DRROP  DATABASE database_name;

CREATE TABLE table_name (
    column1 datatype,
    column2 datatype,
    column3 datatype,
    ...
);
DROP   TABLE table_name;

ALTER TABLE table_name
    ADD column_name datatype;

SHOW DATABASES;
SHOW TABLES;

USE database_name;

EXIT;

SELECT column1, column2, ...
    FROM table_name
    [WHERE condition];
SELECT * FROM table_name
    [WHERE condition];

INSERT INTO table_name (column1, column2, column3, ...)
    VALUES (values1, values2, values3, ...);
INSERT INTO table_name
    VALUES (values1, values2, values3, ...);

UPDATE table_name
    SET column1 = value1, column2 = value2, ...
    WHERE condition;

DELETE FROM table_name
    WHERE condition;
``
