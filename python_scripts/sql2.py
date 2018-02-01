import sqlite3 as sql
import csv
import pandas as pd

def prob1():
    """
    Specify relationships between columns in given sql tables.
    """
    print "One-to-one relationships:"
    # Put print statements specifying one-to-one relationships between table
    # columns.
    print "Student ID and Student Name"
    print "Course ID and Course Name"
    print "Major Code and Major Name"

    print "**************************"
    print "One-to-many relationships:"
    # Put print statements specifying one-to-many relationships between table
    # columns.
    print "Student Name and Major Code"
    print "Student Name and Minor Code"
    print "Student ID and Major Code"
    print "Student ID and Minor Code"

    print "***************************"
    print "Many-to-Many relationships:"
    # Put print statements specifying many-to-many relationships between table
    # columns.
    print "Student ID and Class ID"
    print "Class ID and Grade"

def prob2():
    """
    Write a SQL query that will output how many students belong to each major,
    including students who don't have a major.

    Return: A table indicating how many students belong to each major.
    """
    #Build your tables and/or query here
    db=sql.connect("sql1")
    cur=db.cursor()
    try:
        cur.execute('DROP TABLE IF EXISTS students')
        cur.execute('CREATE TABLE students(StudentID INTEGER NOT NULL, Name TEXT, MajorCode INT, MinorCode INT);')
        with open('students.csv','rb') as file:
            rows=[row for row in csv.reader(file, delimiter=',')]
        cur.executemany('INSERT INTO students VALUES (?,?,?,?);', rows)
        
        cur.execute('DROP TABLE IF EXISTS fields')
        cur.execute('CREATE TABLE fields(ID INTEGER NOT NULL, Name TEXT);')
        cur.execute('INSERT INTO fields VALUES(1, "Math");')
        cur.execute('INSERT INTO fields VALUES(2, "Science");')
        cur.execute('INSERT INTO fields VALUES(3, "Writing");')
        cur.execute('INSERT INTO fields VALUES(4, "Art");')
        
        cur.execute('DROP TABLE IF EXISTS grades')
        cur.execute('CREATE TABLE grades(StudentID INTEGER NOT NULL, ClassID INTEGER NOT NULL, Grade TEXT);')
        with open ('grades.csv', 'rb') as file:
            rows=[row for row in csv.reader(file, delimiter=',')]
        cur.executemany('INSERT INTO grades VALUES (?,?,?);', rows)
        
        cur.execute('DROP TABLE IF EXISTS classes')
        cur.execute('CREATE TABLE classes(ClassID INTEGER NOT NULL, Name TEXT);')
        
        db.commit()
    except sql.Error:
        db.rollback()
    query='SELECT fields.Name, COUNT(students.StudentID) FROM students LEFT JOIN fields ON students.MajorCode=fields.ID GROUP BY fields.Name;'
    
    # This line will make a pretty table with the results of your query.
        ### query is a string containing your sql query
        ### db is a sql database connection
    result =  pd.read_sql_query(query, db)
    db.close()
    return result


def prob3():
    """
    Select students who received two or more non-Null grades in their classes.

    Return: A table of the students' names and the grades each received.
    """
    #Build your tables and/or query here
    db=sql.connect('sql1')
    cur=db.cursor()
    query='SELECT students.Name, count(grades.Grade) FROM students JOIN grades ON students.StudentID=grades.StudentID WHERE grades.Grade IS NOT "NULL" GROUP BY students.Name HAVING COUNT(*)>2;'
    # This line will make a pretty table with the results of your query.
        ### query is a string containing your sql query
        ### db is a sql database connection
    result =  pd.read_sql_query(query, db)
    db.close()
    return result


def prob4():
    """
    Get the average GPA at the school using the given tables.

    Return: A float representing the average GPA, rounded to 2 decimal places.
    """
    #use like command from the next section?
    db=sql.connect('sql1')
    cur=db.cursor()
    query='SELECT ROUND(AVG(CASE WHEN grades.Grade LIKE "A%" THEN 4 WHEN grades.Grade LIKE "B%" THEN 3 WHEN grades.Grade LIKE "C%" THEN 2 WHEN grades.Grade LIKE "D%" THEN 1 END),2) as GPA FROM grades WHERE grades.Grade IS NOT "NULL"'
    result=cur.execute(query).fetchone()
    result=result[0]
    db.close()
    return result


def prob5():
    """
    Find all students whose last name begins with 'C' and their majors.

    Return: A table containing the names of the students and their majors.
    """
    #Build your tables and/or query here
    db=sql.connect('sql1')
    cur=db.cursor()
    query='SELECT Name, CASE MajorCode WHEN 2 THEN "Science" WHEN 3 THEN "Writing" ELSE "None" END AS major FROM students WHERE Name LIKE "% C%";'
    # This line will make a pretty table with the results of your query.
        ### query is a string containing your sql query
        ### db is a sql database connection
    result =  pd.read_sql_query(query, db)

    return result

"""if __name__=="__main__":
    print prob4()"""