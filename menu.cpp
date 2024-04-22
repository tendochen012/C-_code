/*
 Name: Tendo Chen
 Course: COP 3330
 Section: 6
 Project number: 6
 function:
 1. GetAChar: allow the user to enter a letter and automatically convert it to uppercase
 2. Legal/Legal_Category: check to see if the user enter a legal entry of the letter
 3. GetCommand: menu choice for loop to make sure user is going into the correct menu choice
 4. main: our main menu and programs
*/

#include <cctype>
#include <iostream>
#include "studentlist.h"

using namespace std; 

void ShowMenu()
// Display the main program menu.
{
	cout<<"\n\t\t*** Student List menu ***";
	cout<<"\n";
	cout<<"\n\tI \tImport students from a file";
	cout<<"\n\tS \tShow student list (brief)";
	cout<<"\n\tE \tExport a grade report (to file)";
	cout<<"\n\tM \tShow this Menu";
	cout<<"\n\tO \tSort student list";
	cout<<"\n\tQ \tQuit Program";
}

char GetAChar(const char* promptString)
{
	char response;

	cout<<promptString;	//the char to be returned;
	
	cin >> response; 	//Get a char
	response = toupper(response);	//and convert it to uppercase
	cin.get();		//discard newline char from input.
	return response;
}

bool Legal(char c) // check the if the menu option selected by user is valid
{
	return ((c == 'I') || (c == 'S') || (c == 'E') || (c == 'M') || (c == 'O') || (c == 'Q'));
}


char GetCommand() // this is the funtion to use while loop method for menu dsiplayment
{
	char cmd = GetAChar("\n> ");

	while(!Legal(cmd))
	{
		cout<<"\nInvalid menu choice.  Try again.";
		cmd = GetAChar("\n>");
	}
	return cmd;
}



int main()
{
	char in[20]; //initialize a c-string to hold input file name
	char ou[20]; //initialize a c-string to hold output file name
	StudentList sl;   //initialize a Style variable
	ShowMenu();	//display the menu.

	char command;	//menu command entered by user.
	do
	{
		command = GetCommand(); 	//Retrieve a command.
		switch (command)
		{
			case 'I':
				/*
				 * A allows the user to import student's data from a file
				 */
				cout<<"Enter filename: ";
				cin.getline(in, 20); 	// enter filename 
				if (sl.ImportFile(in) == false)
				{
					cout<<"Invalid file. No data imported";
					cout<<endl;
				}
				break;
			case 'S':
				/*
				 * S to show a brief student list, with last name, first name and courses info
				 */	
				sl.ShowList();
				break;
			case 'E':
				/*
				 * E allows the user to export a grade report to a specific file
				 */
				cout<<"Enter filename: ";
				cin.getline(ou,20);
				sl.CreateReportFile(ou);	// export a grade report
				break;
			case 'O':
				/*
				 * Sort Function for sorting the studentlist in alphabetical order
				 */
				sl.Sort();
				cout<<"\nSort complete\n";
				break;
			case 'M':
				/*
				 * Display the menu again
				 */
				ShowMenu();
				break;
			case 'Q':
				/*
				 * Exit the program
				 */
				break;
		}
	} while (command != 'Q');
	cout<<"\nGoodbye!\n";
	return 0;
}

