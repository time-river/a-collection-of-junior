create database test;
use test;
create table test(i int);
drop table test;
drop database test;
create database data;
use data;
create table tb(i int, f float, s string);
insert into tb values (1, 2.0);
insert into tb values(2, 2.0, "st");
insert into tb values(3, 3, "str");
insert into tb values(4.0, 4.0, "stri");
insert into tb values('s', 2, 'strin');
insert into tb (i) values (5);
insert into tb (i) values (5+1);
insert into tb (i) values (1.0+6);
insert into tb (i) values (6+1.0);
insert into tb (f) values (7-1.0);
insert into tb (f) values (8*1.0);
insert into tb (f) values (9/1.0);
insert into tb (f) values (2^4);
select * from tb;
select i, f from tb;
