/*
 Name: Tendo Chen
 Course: COP 3330
 Section: 6
 Project number: 6
 Function definition for studentlist projects:
 
 StudentList is using Student class
 
 Student is an abstract class. English, History, Math are based on Student class.
 
 1. course_l_grade() - get the course grade: A 90 - 100, B 80 - 89, C 70 - 79, D 60 - 69, F below 60.
 2. course_avg() - calculate the coruse average based on schema:
    English -- Attendance = 10%, Project = 30%, Midterm = 30%, Final Exam = 30%
 
    History -- Term Paper = 25%, Midterm = 35%, Final Exam = 40%

    Math -- There are 5 quizzes, to be averaged into one Quiz Average (which can be a decimal number). Final grade computed as follows:
        * Quiz Average = 15%, Test 1 = 25%, Test 2 = 25%, Final Exam = 35%
 3. get_final_score() - retrieve the final exam score
 4. get_f_name() - get the student's firstname
 5. get_l_name() - get the student's lastname
 6. get_c_name() - get the student's course
 7. Protected Data:
    char s_f_name[20]; student's first name for sub class to access
    char s_last_name[20];  student's last name for sub class to access
    char course_name[20];  student's course name for sub class to access
 
 Student List:
 1. ImportFile(filename)
    retrieve the data from the filename
 2. CreateReportFile(filename)
    export the student's grade summary to a filename
 3. Sort()
    Bonus
    Allows to sort the list based on last name, (if last name is the same, it will be sorted based on first name). This is Alphabetical Order
 4. ShowList()
    print a brief summary that contains lastname, firstname, coursename.
    
    private:
        int currentSize; //record the size of the list
        int oldSize;    //for resize and grow purpose,,
        Student ** studentList; // list of students pointers
        void resize(int a); // grow the size of studentlist
 
 1. Standard Con and de - structors
    Student()
    Student(const char* l_name, const char* f_name, const char* c_name)
    StudentList()
    ~StudentList()
    English()
    English(const char* l_name, const char* f_name, const char* c_name, int att, int proj, int m_term, int f_exam)
    History()
    History(const char* l_name, const char* f_name, const char* c_name, int t_paper, int m_term, int f_exam)
    Math()
    Math(const char* l_name, const char* f_name, const char* c_name, int q_1, int q_2, int q_3, int q_4, int q_5, int t_1, int t_2, int f_exam)

    we have various grades private data for English, Math, History


*/
#include <iostream>
#include <cstring>
using namespace std;

class Student
{
public:
	virtual char course_l_grade()=0; // pure virtual function
	virtual double course_avg()=0;
	virtual int get_final_score() = 0;
	Student(); 	//defualt constructor;
	Student(const char* l_name, const char* f_name, const char* c_name);
	const char* get_f_name() const; //access first name
	const char* get_l_name() const; //access last name
	const char* get_c_name() const; //access course name
protected:
	char s_f_name[20];      //first name
	char s_last_name[20];   //last name
    char course_name[20];   //course name
};

class English : public Student
{
public:
	English(); 	//default constructor
	English(const char* l_name, const char* f_name, const char* c_name, int att, int proj, int m_term, int f_exam); 	//constructor, last name, first name, attendance, project, mid term, final exam
									
	double course_avg(); // calculate course average
	char course_l_grade(); // calcuate course grade
	int get_final_score();  //retrieve final exam score

private:
	int attendance, project, mid_term, final_exam; 
};

class History : public Student
{
public:
    History();     //default constructor
    History(const char* l_name, const char* f_name, const char* c_name, int t_paper, int m_term, int f_exam);     //constructor, last name, first name, attendance, project, mid term, final exam
                                    
    double course_avg(); // calculate course average
    char course_l_grade(); // calcuate course grade
    int get_final_score();  //retrieve final exam score

private:
    int term_paper, mid_term, final_exam;
};

class Math : public Student
{
public:
    Math();     //default constructor
    Math(const char* l_name, const char* f_name, const char* c_name, int q_1, int q_2, int q_3, int q_4, int q_5, int t_1, int t_2, int f_exam);     //constructor, last name, first name, attendance, project, mid term, final exam
                                    
    double course_avg(); // calculate course average
    char course_l_grade(); // calcuate course grade
    int get_final_score();	//retrieve final exam score

private:
    int quiz1, quiz2, quiz3, quiz4, quiz5, test_1, test_2, final_exam;
};



class StudentList
{
public:
        StudentList();          // starts out empty
        ~StudentList();         // cleanup (destructor)
        bool ImportFile(const char* filename);
        bool CreateReportFile(const char* filename);
        void Sort(); // sort studentlist
        void ShowList() const;  // print basic list data

private:
    int currentSize;
    int oldSize;
    Student ** studentList; // list of students pointers
    void resize(int a); // grow the size of studentlist
};



