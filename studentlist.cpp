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
#include "studentlist.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cstring>
#include <cctype>
#include <string>

using namespace std;


StudentList::StudentList()
{
    currentSize = 0; // initialize the size to 0 no students
    oldSize = 0;    //old size is 0 as well, no students
    studentList = new Student*[currentSize];    //initialize a list student of pointers by using dynamic memory
}

StudentList::~StudentList()
{
    for (int i = 0; i < currentSize; i++) //first we need deallocate each pointer
        delete studentList[i];
    delete [] studentList; //then we deallocate the pointer list
}

bool StudentList::ImportFile(const char* filename)
{
    int x;  //holder for integer
    char f_name[20];        //holder for student's first name
    char last_name[20];     //holder for student's last name
    char course_name[20];   //holder for student's course
    int g1, g2, g3, g4, g5, g6, g7, g8; // maximum to receive 8 grades
    
    ifstream in1; // create inputfile
    in1.open(filename); //open the file
    if (!in1)           // check if the file exists
        return false;   //if not, we terminate the program
    else
    {
        in1>>x;         //as indicated by the file we are reading, first will be integer, and cin>>terminated with space, and we press newline to go to next line
        resize(x);      //resize our student list to the intger size
        for(int i = oldSize; i < currentSize; i++)
        {
            /*
             for loop starts from the oldsize, since we need to grow and not wipe our previous data
             */
            in1.ignore();//ignore the newline
            in1.getline(last_name,20, ',');//up to ','
            in1.ignore();//ignore the whilte space
            in1.getline(f_name,20);// up to'/n'
            in1.getline(course_name, 20, ' '); //up to white space
            if (strcmp(course_name, "Math") == 0)  //if student's course name is math
            {
                /*
                 we read in 8 differet grades, first 5 will be quizz, the other 3, will be two mid terms and final
                 */
                in1>>g1; // read in grade
                in1.ignore(); // ignore a white space, the following ignore() are all whitespaces
                in1>>g2;
                in1.ignore();
                in1>>g3;
                in1.ignore();
                in1>>g4;
                in1.ignore();
                in1>>g5;
                in1.ignore();
                in1>>g6;
                in1.ignore();
                in1>>g7;
                in1.ignore();
                in1>>g8;
                // initilize our Math students with Math constructor
                studentList[i] = new Math(last_name, f_name, course_name,  g1,g2,g3,g4,g5,g6,g7,g8);
            }
            
            else if (strcmp(course_name,"History") == 0)
            {
                /*
                 same logic as previous but with less grades
                 */
                in1>>g1;
                in1.ignore();
                in1>>g2;
                in1.ignore();
                in1>>g3;
                studentList[i] = new History(last_name, f_name, course_name, g1, g2, g3);
                
            }
            else
            {
                /*
                 same logic for English students but 4 different grades
                 */
                in1>>g1;
                in1.ignore();
                in1>>g2;
                in1.ignore();
                in1>>g3;
                in1.ignore();
                in1>>g4;
                studentList[i] = new English(last_name,f_name,course_name, g1,g2,g3,g4);
                
            }
        }
        in1.close(); // close the file
        return true;
    }
    
}

bool StudentList::CreateReportFile(const char* filename)
{
	/*
     export a file
     */
    ofstream out1;
    out1.open(filename);
    if(out1) // if out1 can be opened, we write, otherwise, we do nothing
    {
    	int count_a = 0;    // counter for A students
    	int count_b = 0;    // counter for B students
    	int count_c = 0;    // counter for C students
    	int count_d = 0;    // counter for D stundets
    	int count_f = 0;    // counter for F students
    	/*
         the following is just printing the proper format
         */
        out1<<"Student Grade Summary"<<endl;
    	out1<<"---------------------"<<endl;
    	out1<<endl;
    	out1<<"ENGLISH CLASS"<<endl;
    	out1<<endl;
    	out1<<"Student";
    	for(int i = 7; i<50;i++)
        	out1<<" ";
    	out1<<"Final";
    	for(int i = 5; i<6; i++)
        	out1<<" ";
    	out1<<"Final";
    	for(int i = 5; i < 10; i++)
        	out1<<" ";
    	out1<<"Letter"<<endl;
    	out1<<"Name";
    	for(int i = 4; i<50;i++)
        	out1<<" ";
    	out1<<"Exam";
    	for(int i = 4; i<6; i++)
        	out1<<" ";
    	out1<<"Avg";
    	for(int i = 3; i < 10; i++)
        	out1<<" ";
    	out1<<"Grade"<<endl;
    
    	out1<<"---------------------------------------------------------------------------"<<endl;
    	for (int i = 0; i<currentSize; i++) //for loop going through all student's list
    	{
        	if(strcmp(studentList[i]->get_c_name(),"English") == 0)
        	{
                /*
                 if student is English, we print the following
                 */
                
                //the following code is just trying to get the correc format
            		out1<<studentList[i]->get_f_name()<<" "<<studentList[i]->get_l_name();
            		for(int k = strlen(studentList[i]->get_f_name()) + strlen(studentList[i]->get_l_name()) + 1; k< 50;k++)
                		out1<<" ";
            		out1<<studentList[i]->get_final_score();
                //final score can be *,**,***, if *, we start from 1, **, 2, ***3, to print the space to align the report
            		if(studentList[i]->get_final_score() < 10)
            		{
                		for(int a = 1; a<6;a++)
                    			out1<<" ";
            		}
            		else if(studentList[i]->get_final_score() < 100)
            		{
                		for(int b = 2; b<6; b++)
                    			out1<<" ";
           		 }
            		else
            		{
                		for(int c = 3; c<6; c++)
                    			out1<<" ";
            		}
            		out1<<fixed<<setprecision(2)<<studentList[i]->course_avg();
            		
                    //same logic before, we since we are showing 2 decimal points, *, are 4, **, 5, *** 6
                    if(studentList[i]->course_avg() < 10)
            		{
                		for(int d = 4; d<10;d++)
                    			out1<<" ";
           		 }
            		else if(studentList[i]->get_final_score() < 100)
           		 {
               			 for(int e = 5; e<10; e++)
                   			 out1<<" ";
           		 }
            		else
           		 {
                		for(int f = 6; f<10; f++)
                   			 out1<<" ";
           		 }
            
           		 out1<<studentList[i]->course_l_grade();
			 out1<<endl;
           		// we increase our counter for the grade by using switch statement
                switch(studentList[i]->course_l_grade()){
               			case 'A':
                   		 	count_a++;
                   		 	break;
               		 	case 'B':
                    			count_b++;
                    			break;
                		case 'C':
                    			count_c++;
                    			break;
                		case 'D':
                    			count_d++;
                    			break;
                		case 'F':
                    			count_f++;
                    			break;
           	 						}
        
    		}
	}
    	out1<<endl;
   	out1<<endl;
    	out1<<"HISTORY CLASS"<<endl;
    	out1<<endl;
    	out1<<"Student";
    	for(int i = 7; i<50;i++)
        	out1<<" ";
    	out1<<"Final";
    	for(int i = 5; i<6; i++)
        	out1<<" ";
    	out1<<"Final";
    	for(int i = 5; i < 10; i++)
        	out1<<" ";
    	out1<<"Letter"<<endl;
    	out1<<"Name";
    	for(int i = 4; i<50;i++)
        out1<<" ";
    	out1<<"Exam";
    	for(int i = 4; i<6; i++)
        	out1<<" ";
    	out1<<"Avg";
    	for(int i = 3; i < 10; i++)
        	out1<<" ";
    	out1<<"Grade"<<endl;
    
    	out1<<"---------------------------------------------------------------------------"<<endl;
    	for (int i = 0; i<currentSize; i++)
    	{
            /*
          if student is History, we print the following
          */
        	if(strcmp(studentList[i]->get_c_name(),"History") == 0)
        	{
                //the following code is just trying to get the correc format
            		out1<<studentList[i]->get_f_name()<<" "<<studentList[i]->get_l_name();
            		for(int k = strlen(studentList[i]->get_f_name()) + strlen(studentList[i]->get_l_name()) + 1; k< 50;k++)
                		out1<<" ";
            		out1<<studentList[i]->get_final_score();
                //final score can be *,**,***, if *, we start from 1, **, 2, ***3, to print the space to align the report
            		if(studentList[i]->get_final_score()< 10)
            		{
                		for(int a = 1; a<6;a++)
                    			out1<<" ";
           		}
            		else if(studentList[i]->get_final_score()< 100)
           		{
                		for(int b = 2; b<6; b++)
                    			out1<<" ";
           		}
           		else
            		{
                		for(int c = 3; c<6; c++)
                    			out1<<" ";
            		}
            		out1<<fixed<<setprecision(2)<<studentList[i]->course_avg();
                //same logic before, we since we are showing 2 decimal points, *, are 4, **, 5, *** 6
                    if(studentList[i]->course_avg() < 10)
            		{
                		for(int d = 4; d<10;d++)
                    			out1<<" ";
            		}
            		else if(studentList[i]->course_avg() < 100)
            		{
                		for(int e = 5; e<10; e++)
                    			out1<<" ";
           		}
            		else
            		{
                		for(int f = 6; f<10; f++)
                    			out1<<" ";
            		}
            
            		out1<<studentList[i]->course_l_grade();
            		out1<<endl;
                // we increase our counter for the grade by using switch statement
                    switch(studentList[i]->course_l_grade()){
                			case 'A':
                    				count_a++;
                    				break;
                			case 'B':
                    				count_b++;
                    				break;
                			case 'C':
                    				count_c++;
                    				break;
                			case 'D':
                    				count_d++;
                    				break;
                			case 'F':
                    				count_f++;
                    			break;
           						}
       	 	}
	}
        out1<<endl;
        out1<<endl;
        out1<<"MATH CLASS"<<endl;
        out1<<endl;
        out1<<"Student";
        for(int i = 7; i<50;i++)
            out1<<" ";
        out1<<"Final";
        for(int i = 5; i<6; i++)
            out1<<" ";
        out1<<"Final";
        for(int i = 5; i < 10; i++)
            out1<<" ";
        out1<<"Letter"<<endl;
        out1<<"Name";
        for(int i = 4; i<50;i++)
            out1<<" ";
        out1<<"Exam";
        for(int i = 4; i<6; i++)
            out1<<" ";
        out1<<"Avg";
        for(int i = 3; i < 10; i++)
            out1<<" ";
        out1<<"Grade"<<endl;
        
        out1<<"---------------------------------------------------------------------------"<<endl;
        for (int i = 0; i<currentSize; i++)
        {   /*
             if student is Math, we print the following
             */
            	if(strcmp(studentList[i]->get_c_name(),"Math") == 0)
            	{
                    //the following code is just trying to get the correc format
                	out1<<studentList[i]->get_f_name()<<" "<<studentList[i]->get_l_name();
                	for(int k = strlen(studentList[i]->get_f_name()) + strlen(studentList[i]->get_l_name()) + 1; k< 50;k++)
                    		out1<<" ";
                	out1<<studentList[i]->get_final_score();
                    //final score can be *,**,***, if *, we start from 1, **, 2, ***3, to print the space to align the report
                	if(studentList[i]->get_final_score() < 10)
                	{
                    		for(int a = 1; a<6;a++)
                        		out1<<" ";
               	 	}
                	else if(studentList[i]->get_final_score() < 100)
                	{
                    		for(int b = 2; b<6; b++)
                        		out1<<" ";
               	 	}
                	else
                	{
                    		for(int c = 3; c<6; c++)
                        		out1<<" ";
                	}
                	out1<<fixed<<setprecision(2)<<studentList[i]->course_avg();
                    //same logic before, we since we are showing 2 decimal points, *, are 4, **, 5, *** 6
                    if(studentList[i]->course_avg() < 10)
                	{
                    		for(int d = 4; d<10;d++)
                        		out1<<" ";
                	}
                	else if(studentList[i]->course_avg() < 100)
                	{
                    		for(int e = 5; e<10; e++)
                        		out1<<" ";
                	}
                	else
                	{
                    		for(int f = 6; f<10; f++)
                        		out1<<" ";
                	}
                
                	out1<<studentList[i]->course_l_grade();
             		out1<<endl;
                    // we increase our counter for the grade by using switch statement
                	switch(studentList[i]->course_l_grade())
               		 {
                    		case 'A':
                        		count_a++;
                        		break;
                    		case 'B':
                        		count_b++;
                        		break;
                    		case 'C':
                        		count_c++;
                        		break;
                    		case 'D':
                        		count_d++;
                        		break;
                    		case 'F':
                        		count_f++;
                        		break;
               		 }
       	 	}
	}
        out1<<endl;
        out1<<endl;
        out1<<"OVERALL GRADE DISTRIBUTION"<<endl;
	out1<<endl;
        /*
         printing the proper grading distribution, setw(3) used to look pretty
         */
        out1<<"A:"<<setw(3)<<count_a<<endl;
        out1<<"B:"<<setw(3)<<count_b<<endl;
        out1<<"C:"<<setw(3)<<count_c<<endl;
        out1<<"D:"<<setw(3)<<count_d<<endl;
        out1<<"F:"<<setw(3)<<count_f<<endl;
        out1.close();
        return true;
    	}
   else
	return false;

}

void StudentList::ShowList() const
{
    /*
     *
        The following code is trying to get last, first, course and show
     */
    cout<<"Last";
    cout<<setw(20)<<"First";
    cout<<setw(20)<<"Course";
    cout<<endl;
    cout<<endl;
    for(int i = 0; i< currentSize; i++)
    {
        //the loop is tring to print correct format
        cout<<studentList[i]->get_l_name();
        //depnds on the size of the last name and first name, we print up to 20 spaces to align out report
	for(int j = strlen(studentList[i]->get_l_name()); j<20; j++)
		cout<<" ";
        cout<<studentList[i]->get_f_name();
	for(int k = strlen(studentList[i]->get_f_name()); k<20; k++)
		cout<<" ";
        cout<<studentList[i]->get_c_name();
        cout<<endl;
    }
    cout<<endl;
}

void StudentList::Sort()
{
    // sort function to sort last name, if last name is the same, we sort based on first name.
    // this is alphabetical order, Aa, Bb, Cc, Dd, Ee, Ff, ........ (I think Aa should not be a difference)
	
	for (int i = 0; i <currentSize; i++) // outer loop to go thourgh each enty
	{
		for (int j = 0; j <currentSize -i - 1; j++) // inner loop to compare current entry with rest of the entry
		{
			int l_result = 0;   // compare result for last name
			int f_result = 0;   // compare result for first name
			string s_l(studentList[j]->get_l_name());   //string object conversion, I think it would be easier
			string s_f(studentList[j]->get_f_name());
			string s_l_1(studentList[j+1]->get_l_name());   //convert the object we want to comare to string
			string s_f_1(studentList[j+1]->get_f_name());
			for (int k = 0; k <s_l.length(); k++)   //convert each letter to upper case in our string object, this would not change the source, which is the student list object
				toupper(s_l[k]);
			for (int k = 0; k< s_l_1.length();k++)
				toupper(s_l_1[k]);
			for (int k = 0; k< s_f.length();k++)
				toupper(s_f[k]);
			for (int k = 0; k< s_f_1.length();k++)
				toupper(s_f_1[k]);

			l_result = s_l.compare(s_l_1);  //last name compare result
			f_result = s_f.compare(s_f_1);  //first name compare result

			if (l_result > 0)   //if is bigger than 0, that means the previous value is bigger
			{
                //mini swap fcuntion, to throw the current one into next position, hence, it is in the
                // correct alphabetical order
				Student *temp;
				temp = studentList[j];
				studentList[j] = studentList[j+1];
				studentList[j+1] = temp;
			}

			else if (l_result == 0) //if last name is the same
			{
				if (f_result > 0)   //we compare first name, same logic as the last name moving alogrithm
				{
					Student *temp;
					temp = studentList[j];
					studentList[j] = studentList[j+1];
					studentList[j+1] = temp;
				}
			}
			
		}
	}
}

void StudentList::resize(int a) //resize function, paramets means how much we want to increase
{
    oldSize = currentSize;  //old size is current currentSize
    currentSize += a; // increase the current size to a
    Student** newList = new Student*[currentSize];  // a temp newlist to hold the list of pointers
    int i;
    for (i = 0; i<oldSize; i++)
        newList[i] = studentList[i];    //assign the old list to new list
    for (i = oldSize; i < currentSize; i++)
        newList[i] = nullptr;   //for the spaces that are null, we assign to null pointer
    delete [] studentList;      // now we deallocate original student list
    studentList = newList;      //now new list address is assigned to student list, done
}


/*
 ////////////////////////////
 */

Student::Student()  //student default constructor, we assign everything to blank;
{
    strcpy(s_f_name," ");
    strcpy(s_last_name," ");
    strcpy(course_name, " ");
}
Student::Student(const char* l_name, const char* f_name, const char* c_name)
{
    //assign parameters values into protected data
    strcpy(s_f_name,f_name);
    strcpy(s_last_name, l_name);
    strcpy(course_name, c_name);
}

const char* Student::get_f_name() const
{
	return s_f_name;    //get the first name
}

const char* Student::get_l_name() const
{
	return s_last_name; //get the last name
}

const char* Student::get_c_name() const
{
	return course_name; //get the course name
}

English::English()  //english default constructor
{
    //assign all grades to 0
    attendance = 0;
    project = 0;
    mid_term = 0;
    final_exam = 0;
}

English::English(const char* l_name, const char* f_name, const char* c_name, int att, int proj, int m_term, int f_exam): Student(l_name,f_name, c_name)
{
    //first name, last name, course name is being contrcutor from the base constructor,
    // rest of the data get from paramters
    attendance = att;
    project = proj;
    mid_term = m_term;
    final_exam = f_exam;
}

double English::course_avg()
{
    //calculate the average score based on alog
    double result = attendance*0.1 + project * 0.3 + mid_term * 0.3 + final_exam * 0.3;
    return result;
}

char English::course_l_grade()
{
    // calculate letter grade based on course_avg that we got
    char a;
    double avg = course_avg();
    if (avg >= 90)
        a = 'A';
    else if (avg >= 80)
        a = 'B';
    else if (avg >= 70)
        a = 'C';
    else if (avg >= 60)
        a = 'D';
    else
        a = 'F';
    return a;
}

int English::get_final_score()
{
	return final_exam;  //retrieve final exam score
}

History::History() //default constructor:
{
    //assign all grades to 0
    term_paper = 0;
    mid_term = 0;
    final_exam = 0;
}

History::History(const char* l_name, const char* f_name, const char* c_name, int t_paper, int m_term, int f_exam): Student(l_name,f_name, c_name)
{
    //first name, last name, course name is being contrcutor from the base constructor,
    // rest of the data get from paramters
    term_paper = t_paper;
    mid_term = m_term;
    final_exam = f_exam;
}

char History::course_l_grade()
{
    // calculate letter grade based on course_avg that we got
    char a;
    double avg = course_avg();
    if (avg >= 90)
        a = 'A';
    else if (avg >= 80)
        a = 'B';
    else if (avg >= 70)
        a = 'C';
    else if (avg >= 60)
        a = 'D';
    else
        a = 'F';
    return a;
}

double History::course_avg()
{
    //calculate the average score based on alog
    double result = term_paper*0.25 +  mid_term * 0.35 + final_exam * 0.4;
    return result;
}

int History::get_final_score()
{
	return final_exam; //retrieve final exam score
}


Math::Math() //default constructor
{
    //assign all grades to 0
    quiz1 = 0;
    quiz2 = 0;
    quiz3 = 0;
    quiz4 = 0;
    quiz5 = 0;
    test_1 = 0;
    test_2 = 0;
    final_exam = 0;
}

Math::Math(const char* l_name, const char* f_name, const char* c_name, int q_1, int q_2, int q_3, int q_4, int q_5, int t_1, int t_2, int f_exam): Student(l_name, f_name, c_name)
{
    //first name, last name, course name is being contrcutor from the base constructor,
    // rest of the data get from paramters
    quiz1 = q_1;
    quiz2 = q_2;
    quiz3 = q_3;
    quiz4 = q_4;
    quiz5 = q_5;
    test_1 = t_1;
    test_2 = t_2;
    final_exam = f_exam;
}

double Math::course_avg()
{
    //calculate the average score based on alog
    int q_s =  quiz1 + quiz2 + quiz3 + quiz4 + quiz5;
    double q_avg = static_cast<double>(q_s)/5.0;
    double result = q_avg * 0.15 + test_1 * 0.25 + test_2 * 0.25 + final_exam * 0.35;
    return result;
}

char Math::course_l_grade()
{
    // calculate letter grade based on course_avg that we got
    char a;
    double avg = course_avg();
    if (avg >= 90)
        a = 'A';
    else if (avg >= 80)
        a = 'B';
    else if (avg >= 70)
        a = 'C';
    else if (avg >= 60)
        a = 'D';
    else
        a = 'F';
    return a;
}

int Math::get_final_score()
{
	return final_exam; //retrieve final exam score
}
