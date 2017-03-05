USE Homework;
GO

-- 录入学生信息(Name UNIQE)
   -- 无方向(Term < 5) 
INSERT INTO Student (ID, Name, Sex, Birthday, Enrollment, Term, ClassID)
	VALUES ('0001', 'h', '男', '20000101', '20000101', 1, '1403012');
GO
   -- 有方向(Term > 4)
INSERT INTO Student (ID, Name, Sex, Birthday, Enrollment, Term, DirectionID, ClassID) 
	VALUES ('0002', 's', '女', '20000101', '20000101', 5, '01', '1403012');
GO

-- 查询学生信息
   -- 根据学号查询
SELECT * FROM Student FULL JOIN Direction ON Student.DirectionID = Direction.ID WHERE Student.ID = '0001';
GO
   -- 根据姓名查询
SELECT * FROM Student FULL JOIN Direction ON Student.DirectionID = Direction.ID WHERE Student.Name = 's';
GO
   -- 根据专业查询
SELECT Student.ID, Student.Name, Student.Sex, Student.Birthday, Student.Enrollment, Student.Term, Student.DirectionID
	FROM Student
	JOIN Class ON Student.ClassID = Class.ID
	JOIN Major ON Class.MajorID = Major.ID
	WHERE Major.ID = '01';
GO

-- 成绩
	-- 录入成绩
UPDATE Grade
SET Grade = 65, Makeup = 
		(
			CASE
			WHEN Grade IS NULL THEN 0
			WHEN Grade IS NOT NULL THEN 1
			END
		 )
	WHERE (StudentID = '0000' AND CourseID = 'CS2121003' AND Makeup = 0)
GO
    -- 查询所有科目成绩
SELECT Student.ID, Student.Name, Course.ID, Course.Name, Course.Kind, Course.Credit, Course.Term, Grade.Grade  
	FROM Student
	JOIN Grade ON Student.ID = Grade.StudentID
	JOIN Course ON Course.ID = Grade.CourseID
	WHERE StudentID = '03051001'
GO
	-- 查询必修科目平均成绩
SELECT ROUND(SUM(total)/SUM(creadit),1) FROM (
	SELECT CAST(Grade.Grade AS float)*CAST(Course.Credit AS float) AS total, Course.Credit AS creadit FROM Student
		JOIN Grade ON Student.ID = Grade.StudentID
		JOIN Course ON Course.ID = Grade.CourseID
		WHERE Student.ID = '03051001' AND Course.Kind = '必修'
)TEMP;
GO
	-- 查询所有科目平均成绩
SELECT ROUND(SUM(total)/SUM(creadit),1) FROM (
	SELECT CAST(Grade.Grade AS float)*CAST(Course.Credit AS float) AS total, Course.Credit AS creadit FROM Student
		JOIN Grade ON Student.ID = Grade.StudentID
		JOIN Course ON Course.ID = Grade.CourseID
		WHERE Student.ID = '03051001'
)TEMP;
GO

-- 查询学生教师
SELECT Teacher.ID, Teacher.Name FROM Student 
	JOIN Grade ON Student.ID = Grade.StudentID
	JOIN ClassTeacherCourse ON Grade.CourseID = ClassTeacherCourse.CourseID
	JOIN Teacher ON ClassTeacherCourse.TeacherID = Teacher.ID
	WHERE Student.ID = '03051001'
GO

-- 查询即将开除的学生
SELECT Student.ID, Student.Name FROM Student 
	WHERE EXISTS
(SELECT Grade.StudentID AS Result FROM Grade JOIN Course ON Grade.CourseID = Course.ID
	WHERE (Grade.Grade < 60 AND Course.Kind = '必修') 
		GROUP BY StudentID 
			HAVING 
				(SUM(Course.Credit) > 27 AND SUM(Course.Credit) < 30)
UNION
SELECT Grade.StudentID FROM Grade JOIN Course ON Grade.CourseID = Course.ID
	WHERE (Grade.Grade < 60 AND Course.Kind = '选修')
		GROUP BY StudentID
			HAVING
				(SUM(Course.Credit) > 17 AND SUM(Course.Credit) < 20)
UNION
SELECT Grade.StudentID FROM Grade 
	JOIN Student ON Grade.StudentID = Student.ID
	JOIN Course ON Grade.CourseID = Course.ID
	WHERE (Grade.Grade < 60 AND Student.Term = Course.Term)
		GROUP BY StudentID
			HAVING (SUM(Course.Credit) > 7 AND SUM(Course.Credit) < 10)
)
GO