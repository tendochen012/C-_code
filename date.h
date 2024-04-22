/*
 Name: Tendo Chen
 Course: COP 3330
 Section: 6
 Project number: 2
 This is the header for Date object
 Function for date projects:
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
class Date
{
public:
    Date(); // default constructor for date class 'January 1, 2000'
    Date(int m, int d, int y); //constructor with paramters

    void Input(); //mutator
    bool Set(int m, int d, int y); //mutator
    bool SetFormat(char f); //mutator
    void Increment(int numDays = 1); //mutator

    void Show() const; //accessor
    int GetMonth() const; //accessor
    int GetDay() const; //accessor
    int GetYear() const; //accessor
    int Compare(const Date& d) const; //accessor
    
private:
    int year;
    int month;
    int day;
    char d_format;
};
