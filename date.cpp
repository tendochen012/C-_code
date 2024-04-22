/*
 Name: Tendo Chen
 Course: COP 3330
 Section: 6
 Project number: 2
 Function definition for date projects:
	1. Date - default constructor to set the date to January 1st, 2000
	2. Date with Paramters - constuctor to set the date based on user but if an invalid date is given, it set the date to January 1st, 2000 
	3. Set - Set function to allower user to set a date based on their wish, and check if the date specified by user is a valid date (it will also check leap years)
		it will return true or false
	4. SetFormat - Set the display format of the date. D - Default M/D/Y, T - Two-Digit mm/dd/yy, L - Long month D, Y, J - Julian yy-xxx (xxx total days in the date)
		if the user enters no the letters above, it will keep the current format.
	5. GetYear - Return the year of the date
	6. GetMonth - Return the month of the date
	7. GetDay- Return the day of the date
	8. Input - ask the user to input a date, if the date is invalid, the users will be asked to put a date until is valid
	9. Show - Display the date format on screen based on the Format (D, T, L, J)
	10. Increment - Increase the number of days based on current date (defualt is increase 1 day)
	11. Compare - This function should compare two Date objects (the calling object and the parameter), and 
	    should return: -1 if the calling object comes first chronologically, 
	    0 if the objects are the same date, and 
	    1 if the parameter object comes first chronologically. The function should not change either object.
 */
#include <iostream>
#include "date.h"
#include <iomanip>
#include <string>

using namespace std;

Date::Date()
// Default constructor, initialize memebr data to January, 1st, 2000 with proper print format
{
    year = 2000;  
    day = 1;
    month = 1;
    d_format = 'D'; // 'D' format is the default format and will set the the date to be shown as 1/1/2000
}

Date::Date(int m, int d, int y) 
// Constructor for Date class
{
	
	if (Set(m,d,y) == false)
	 	Set(1,1,2000);    // if the date input by user is invalid, we set to 1/1/2000
	d_format = 'D';  //set the format to 'D', which stands for default, the Show function will print out (1/1/2000 as an example)
	       
}

/*
 * Set function to check if the users if setting the date in a valid range
 * the function will return a false if the range is not good
*/
bool Date::Set(int m, int d, int y) 
{

	if (y<=0)   // check if the year is bigger than 0, if less than 0, then return false and set the date to 1/1/2000
		return false;
	else
	{
		if ((m<1) || (m>12)) // check if the month is in a valid range
			return false;
		else  
	    	{
			// check if the year is a leap year
	    		if (((y % 100 == 0) && (y % 400 == 0)) || ((y % 100 != 0) && (y % 4 == 0)))
                	{/*the follwoing code check if the days match with specific month, Feb should have 29 days if it is a leap year
			* if the the checks are passed, we will set the month, day and year to the paramters specificed by user.
			*/
				if ((m == 1) || (m==3) || (m==5) || (m==7) ||(m==8) || (m==10) || (m==12))
				{
					if ((d>= 1) && (d <= 31))
					{ 
						month = m;
						day = d;
						year = y;
						return true;
					}
					else
						return false;
				}

				else if (m==2)
				{
					if ((d>=1) && (d<=29))
					{
						month = m;
						day = d;
						year = y;
						return true;
					}
					else
						return false;
				}
				else
				{
					if ((d>=1) && (d<=30))
					{
						month = m;
						day = d;
						year = y;
						return true;
					}
					else
						return false;
				}
                	}

			else
			{ // non-leap year case days check.
			  // if the checks are passed, we will set month, day, year to parameters specified by user
				if ((m == 1) || (m==3) || (m==5) || (m==7) ||(m==8) || (m==10) || (m==12))
				{
					if ((d>= 1) && (d <= 31))
					{
						month = m;
						day = d;
						year = y;
						return true;
					}
					else
						return false;
				}

				else if (m==2)
				{
					if ((d>=1) && (d<=28))
					{
						month = m;
						day = d;
						year = y;
						return true;
					}
					else
						return false;
				}
				else
				{
					if ((d>=1) && (d<=30))
					{
						month = m;
						day = d;
						year = y;
						return true;
					}
					else
						return false;
				}	
			}	
	    	}
	}
}

bool Date:: SetFormat(char f) 
/* this function sets the display format that user wants
 * D stands for default: Month/Day/Year: 10/4/1998
 * T stands for "Two-Digit": mm/dd/yy: 10/04/98
 * L stands for "Long": Oct 4, 1998. Jan, Feb, Mar, Apr, May, June, July, Aug, Sept, Oct, Nov, and Dec.
 * J stands for "Julian": For example Feb 1, 1998 : 98-032
 * if users enters any letter above in the argument, we change the display format, otherwise we don't.
 */
{
    if ((f == 'D') || (f == 'T') || (f == 'L') || (f == 'J'))
    {
        d_format = f;
        return true;
    }
    else
        return false;

}

// return the month of the date 
int Date::GetMonth() const
{
	return month;
}
// return the year of the date
int Date::GetYear() const
{
	return year;
}
// return the day of the date
int Date::GetDay() const
{
	return day;
}
// allow the user to input a date from prompt
// if the month or day or year entered by used is invalid, we will ask again until user puts a valid date
// this function assume the user would always entere mm/dd/yyyy in this format with the "/".
void Date::Input()
{
	char sep; // variable to hold '/'
	do
	{
		cin>>month>>sep>>day>>sep>>year;
		if(Set(month,day,year) == false)
			cout<<"Invalid date, Try again"<<endl;
	} while (Set(month,day, year) == false);
}

/* Show function display format that user wants
 * D stands for default: Month/Day/Year: 10/4/1998
 * T stands for "Two-Digit": mm/dd/yy: 10/04/98
 * L stands for "Long": Oct 4, 1998. Jan, Feb, Mar, Apr, May, June, July, Aug, Sept, Oct, Nov, and Dec.
 * J stands for "Julian": For example Feb 1, 1998 : 98-032
 * if users enters any letter above in the argument, we change the display format, otherwise we don't.
 */

void Date::Show() const
{
    if (d_format == 'D')
        cout<<month<<"/"<<day<<"/"<<year<<endl;
    else if (d_format == 'T')
    {
        int last_two = year - (year/100)*100; // calculated the numbers of the remain year after we get the century year.
        /*
	the following are the logic statement to figure out if i need to put a 0 in front of the day or month or year,
	if it's smaller or equal 9, we will put a 0 in the front
	*/
	if ((month > 9) && (day > 9) && (last_two > 9))
            cout<<month<<"/"<<day<<"/"<<last_two;
        else if ((month > 9) && (day >9) && (last_two <=9))
            cout<<month<<"/"<<day<<"/"<<"0"<<last_two;
        else if ((month) >9 && (day <= 9) && (last_two > 9))
            cout<<month<<"/"<<"0"<<day<<last_two;
        else if ((month > 9) && (day <=9) && (last_two <= 9))
            cout<<month<<"/"<<"0"<<day<<"0"<<last_two;
        else if ((month <= 9) && (day > 9) && (last_two > 9))
            cout<<"0"<<month<<"/"<<day<<last_two;
        else if ((month <= 9) && (day > 9) && (last_two <=9))
            cout<<"0"<<month<<"/"<<day<<"/"<<"0"<<last_two;
        else if ((month <= 9 ) && (day <=9) && (last_two >9))
            cout<<"0"<<month<<"/"<<"0"<<day<<"/"<<last_two;
        else if ((month <=9) && (day<=9) && (last_two <= 9))
            cout<<"0"<<month<<"/"<<"0"<<day<<"/"<<"0"<<last_two;
	cout<<endl;
    }
    else if (d_format == 'L')
    {
        switch (month)
        { // switch statement to ensure the Month abbr that we get is in correct text format
            case 1:
                cout<<"Jan "<<day<<", "<<year;
                break;
            case 2:
                cout<<"Feb "<<day<<", "<<year;
                break;
            case 3:
                cout<<"Mar "<<day<<", "<<year;
                break;
            case 4:
                cout<<"Apr "<<day<<", "<<year;
                break;
            case 5:
                cout<<"May "<<day<<", "<<year;
                break;
            case 6:
                cout<<"June "<<day<<", "<<year;
                break;
            case 7:
                cout<<"July "<<day<<", "<<year;
                break;
            case 8:
                cout<<"Aug "<<day<<", "<<year;
                break;
            case 9:
                cout<<"Sept "<<day<<", "<<year;
                break;
            case 10:
                cout<<"Oct "<<day<<", "<<year;
                break;
            case 11:
                cout<<"Nov "<<day<<", "<<year;
                break;
            case 12:
                cout<<"Dec "<<day<<", "<<year;
                break;
        }
	cout<<endl;
    }
    else if (d_format == 'J')
    {
        int day_acc= 0; //each day we are adding
        int day_sum = 0;// accrual day that we currently have
        if (((year % 100 == 0) &&(year % 400 == 0)) || ((year % 100 != 0) && (year % 4 == 0)))
        { // logic to figure out the leap year
            for (int i = 1; i < month; i++) // for loop to add up the days, i < month due to that the final month should just be the days add up 
		//any month before the current month should add up all th days in the calendar month.
            {
                if ((i==1) || (i==3) || (i==5) || (i==7) || (i==8) || (i==10) || (i==12))
                    day_acc = 31;
                else if ((i==4) || (i==6) || (i==9) || (i==11))
                    day_acc = 30;
                else
                    day_acc = 29;
                day_sum += day_acc;
            }
        }
        else
        {
            for (int i = 1; i < month; i++)
            {
                if ((i==1) || (i==3) || (i==5) || (i==7) || (i==8) || (i==10) || (i==12))
                    day_acc = 31;
                else if ((i==4) || (i==6) || (i==9) || (i==11))
                    day_acc = 30;
                else
                    day_acc = 28;
                day_sum += day_acc;
            }
        }
	day_sum += day; // final day sum adding the current days in the current month
        int last_two = year - (year/100)*100; // get the last two digits of the year
        // if the day_sum smaller than 10 we add two 0s, if smaller than 100, we add one '0' 
	// if the last two digits is smaller than 10, we add a 0 in font of the year
	if ((last_two >9) && (day_sum>99))
            cout<<last_two<<"-"<<day_sum;
        else if ((last_two > 9) && (day_sum<99) && (day_sum>9))
            cout<<last_two<<"-"<<"0"<<day_sum;
        else if ((last_two > 9) && (day_sum <=9))
            cout<<last_two<<"-"<<"00"<<day;
        else if ((last_two <=9) && (day_sum>99))
            cout<<"0"<<last_two<<"-"<<day_sum;
        else if ((last_two <= 9) && (day_sum<99) && (day_sum>9))
            cout<<"0"<<last_two<<"-"<<"0"<<day_sum;
        else if ((last_two <= 9) && (day_sum <=9))
            cout<<"0"<<last_two<<"-"<<"00"<<day_sum;
	cout<<endl;
    }
}


/*
Increment function to ask the user to put how many days they want to increase for the current date 
if no  arguments are provided by users, the default is 1 day increase of current date.
*/
void Date::Increment(int numDays)
{
	int m_m[12] = {1,2,3,4,5,6,7,8,9,10,11,12};// array to hold for month
	int l_m[12] = {31,29,31,30,31,30,31,31,30,31,30,31};// leap year days
	int r_m[12] = {31,28,31,30,31,30,31,31,30,31,30,31};// non-leap year days
	int t_m[12]; // to hold the current month days 
	
	if (((year % 100 == 0) &&(year % 400 == 0)) || ((year % 100 != 0) && (year % 4 == 0)))
	{ // leap-year check, if this is a leap year
		for (int i =0; i <12; i++)
			t_m[i] = l_m[i]; //we store corresponding days for leap-year months
	}
	else
	{
		for (int i = 0; i<12; i++)
			t_m[i] = r_m[i];//other wise, we store corresponding days for non-leap-year months
	}
	
	day += numDays; // total days we are increasing
	while (day > t_m[month - 1]) // if day vairable is larger than current days in the month , we run the loop
	{
		day -= t_m[month - 1]; // clears the # days in that current month
		month++; //increase the month
		if (month > 12) //if the reach the last month of the year, we will go to next year
		{
			month = 1; // rest month to 1
			year++; // increase year
            		if (((year % 100 == 0) &&(year % 400 == 0)) || ((year % 100 != 0) && (year % 4 == 0)))
            		{ // check again if the it's a leap year, after the increment we might get a leap-year
                		for (int i =0; i <12; i++)
                    		t_m[i] = l_m[i];
            		}
            		else
            		{
                		for (int i = 0; i<12; i++)
                    		t_m[i] = r_m[i];
            		}	
		}
	}  //repeat the loop until we day is no longer bigger than the days in current month.	
}


// compare function to compare two dates,
// d1.compare(d2), if d1 > d2, return 1, if d1 == d2, return 0, if d1 < d2, return -1
int Date::Compare(const Date& d) const
{
	if ((year == d.year) && (month == d.month) && (day == d.day))
		return 0; // check to see if the dates are equal
	else
	{
		if (year > d.year) // compare year, if year of the date is bigger than the year of date in parameter, we return 1 immediatly
			return 1;
		else if (year == d.year) // if years are equal, we go on to check month
		{
			if (month > d.month)
				return 1; // if month of the date is bigger than the month of date in parameter, we return 1 immediately
			else if (month == d.month) // if months are equal, we go on to check days
			{
				if (day > d.day) // if day of the date is bigger than the day of date in paramter, we return 1 immediately
					return 1;
				else             // else implies day < day of parameter, since it's not possible to have equal day at this point
						 // we return -1 immediately
					return -1;
			}
			else
				return -1; // month < paramter month, return -1 immediately
		}
		else
			return -1; // year < paramter year, return -1 immediately
	}
}
