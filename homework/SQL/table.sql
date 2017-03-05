USE master;
GO

DROP DATABASE Homework;
GO

CREATE DATABASE Homework
ON
( NAME = Homework_dat,  
    FILENAME = 'C:\Program Files\Microsoft SQL Server\MSSQL12.MSSQLSERVER\MSSQL\DATA\homeworkdat.mdf',  
    SIZE = 10,  
    MAXSIZE = 50,  
    FILEGROWTH = 5 )  
LOG ON  
( NAME = Homework_log,  
    FILENAME = 'C:\Program Files\Microsoft SQL Server\MSSQL12.MSSQLSERVER\MSSQL\DATA\homeworklog.ldf',  
    SIZE = 5MB,  
    MAXSIZE = 25MB,  
    FILEGROWTH = 5MB ) ;  
GO

USE Homework;
GO

-- 学院表
CREATE TABLE Academy
	(
        ID varchar(10) PRIMARY KEY NOT NULL,
	    Name nvarchar(25) NOT NULL
    );
GO

-- 专业表
CREATE TABLE Major
	(
        ID varchar(10) PRIMARY KEY NOT NULL,
	    Name nvarchar(25) NOT NULL,
	    AcademyID varchar(10),
	    FOREIGN KEY (AcademyID) REFERENCES Academy (ID)
    );
GO

-- 教学计划表
CREATE TABLE TeachingProgram
	(
	    Term tinyint NOT NULL,
	    CompulsoryCredit tinyint NOT NULL,
	    OptionalCredit   tinyint NOT NULL,
	    MajorID varchar(10),
	    PRIMARY KEY (MajorID, Term),
	    FOREIGN KEY (MajorID) REFERENCES Major (ID)
    );
GO

-- 方向表
CREATE TABLE Direction
	(
        ID varchar(10) PRIMARY KEY NOT NULL,
	    Name nvarchar(25) NOT NULL,
	    MajorID varchar(10),
	    FOREIGN KEY (MajorID) REFERENCES Major (ID)
    );
GO

-- 班级表
CREATE TABLE Class
	(
        ID varchar(10) PRIMARY KEY NOT NULL,
	    MajorID varchar(10),
	    FOREIGN KEY (MajorID) REFERENCES Major(ID)
    );
GO

-- 学生表
CREATE TABLE Student
	(
        ID varchar(15) PRIMARY KEY NOT NULL,
	    Name nvarchar(25) NOT NULL UNIQUE,
	    Sex  nchar(1) NOT NULL,
	    Birthday date,
	    Enrollment date,
	    Term tinyint NOT NULL,
	    DirectionID varchar(10) DEFAULT NULL,
	    ClassID varchar(10),
	    FOREIGN KEY (DirectionID) REFERENCES Direction (ID),
	    FOREIGN KEY (ClassID) REFERENCES Class (ID),
	    CHECK (Sex IN ('男', '女')),
	    CHECK (((DirectionID IS NULL) AND (Term < 5)) OR (Term > 4))
    );
GO

-- 课程表
CREATE TABLE Course
	(
        ID varchar(15) PRIMARY KEY NOT NULL,
	    Name nvarchar(25) NOT NULL,
	    Kind nvarchar(5),
	    Term tinyint NOT NULL,
	    Credit tinyint,
	    Period tinyint,
	    Previous varchar(15),
	    MajorID varchar(10),
	    FOREIGN KEY (Previous) REFERENCES Course (ID),
	    FOREIGN KEY (MajorID) REFERENCES Major (ID)
    );
GO

-- 成绩表
CREATE TABLE Grade
	 (
        PRIMARY KEY (StudentID, CourseID),
	    Grade tinyint,
	    Makeup bit default 0,
	    StudentID varchar(15),
	    CourseID varchar(15),
	    FOREIGN KEY (StudentID) REFERENCES Student (ID)
            ON DELETE CASCADE,
	    FOREIGN KEY (CourseID) REFERENCES Course (ID),
	    CHECK (Grade >=0 AND Grade <= 100)
    );
GO

-- 教师表
CREATE TABLE Teacher
	(
        ID varchar(15) PRIMARY KEY NOT NULL,
	    Name nvarchar(25) NOT NULL,
	    Sex nchar(1) NOT NULL,
	    Birthday date,
	    MajorID varchar(10),
	    FOREIGN KEY (MajorID) REFERENCES Major (ID),
	    CHECK (Sex IN ('男', '女'))
    );
GO

-- 教室教师课程表
CREATE TABLE ClassTeacherCourse
	(
        PRIMARY KEY (ClassID, TeacherID),
	    ClassID varchar(10),
	    TeacherID varchar(15),
	    CourseID varchar(15),
	    FOREIGN KEY (ClassID) REFERENCES Class (ID),
	    FOREIGN KEY (TeacherID) REFERENCES Teacher (ID),
	    FOREIGN KEY (CourseID) REFERENCES Course (ID)
    );
GO
