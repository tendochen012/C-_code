/*
 Name: Tendo Chen
 Course: COP 3330
 Section: 6
 Project number: 5
 Function definition for Mixed Number projects:
 1. Standard Constructors
 The default constructor should set the object to represent an empty string.
 MyString(const char* ) -- this is a conversion constructor. A c-string will be passed as a parameter, and this constructor should set up the string object to store that string inside. This will enable type conversions from c-strings to MyString objects.
 MyString(int ) -- this is a conversion constructor that should convert an integer value to a string representation. For example, if the value 1234 is passed in, the MyString object should now store the same string data that would be represented by the c-string "1234"
 
 2. Automatics
 Since dynamic allocation is necessary, you will need to write appropriate definitions of the special functions (the "automatics"):  destructor, copy constructor, assignment operator.  The destructor should clean up any dynamic memory when a MyString object is deallocated.  The copy constructor and assignment operator should both be defined to make a "deep copy" of the object (copying all dynamic data, in addition to regular member data), using appropriate techniques.  Make sure that none of these functions will ever allow memory "leaks" in a program.
 
 3.I /O functions
 operator << -- insertion operator. This should print out the data from the MyString object, using the standard insertion operator syntax. There should be no extra formatting -- only the string stored in the object is printed (no newlines, extra spacing, etc).
 operator >> -- extraction operator. This should read a string from an input stream. This operator should ignore any leading white space before the string data, then read until the next white space is encountered. Prior data in the MyString object is discarded. Note: Just like the operator>> for c-strings, this will only read one word at time.
 getline functions. These should read a string from an input stream. This operator should read everything from the input stream (first parameter) into the MyString object (second parameter) until the specified delimiter character is encountered. In the version of the function with 3 parameters, the third parameter is the delimiter. In the version of the function with 2 parameters, the delimiter should be the newline '\n'. In either case, prior data in the MyString object is discarded.
 
 4. Comparison operators
 Write overloads for all 6 of the comparison operators ( < , > , <= , >= , == , != ).  Each of these operations should test two objects of type MyString and return an indication of true or false. You are testing the MyString objects for order and/or equality based on the usual meaning of order and equality for c-strings, which is lexicographic ordering. Remember that this is based on the order of the ascii characters themselves, so it's not exactly the same as pure "alphabetical" ordering.
 
 5. Concatenation operators
 operator+ -- this should concatenate the two operands together and return a new MyString as a result.
 operator+= -- this should concatenate the second operand onto the first one (i.e. changing the first one)
6. Bracket operators
 The bracket operator overloads have these prototypes:
   char& operator[] (unsigned int index);        // returns L-value
   const char& operator[] (unsigned int index) const;    // read-only return
 Both of these should return the character at the given index position. Note that the first one returns the character by reference, so it allows the slot to be changed. The second returns by const reference and is a const member function and will run in read-only situations -- calls on const objects.
 
 7. Standard accessors
 getLength should return the length of the stored string (i.e. number of characters). For example, "Hello" has 5 characters
 getCString should return the actual stored data as a c-string (i.e. null-terminated char array)
 
 
 8. ubstring functions
 There are two versions of substring -- a 1 parameter version and a 2-parameter version. Both should return a MyString object that consists of a portion (or "substring") of the original string. Neither should change the calling object. The first parameter represents the starting index of the substring. In the 2-parameter version, the second parameter gives the length of the substring to return (if the length is too long, default to the rest of the string ). In the 1-parameter version, the substring consists of the characters from the start index to the end of the string.
 
 9. insert() function
 This function should change the calling object by inserting the data from the second parameter AT the index given by the first parameter. If the index is out of bounds (longer than the string's length), then just insert at the end. This function should also return the calling object.
 
 10. indexOf function
 This function should search through the MyString to find the first occurence of the pattern or substring given in the parameter. The function should return the first index where it was found, or it should return -1 if the pattern is NOT found.
 
 Bonus:::
 
 11. Create an overloaded version of the - operator to "subtract" two MyString objects.  The meaning of - is that it should return a MyString object that is the result of taking the first string and removing all instances of the second string from it.
 Examples:
   MyString s = "The bobcat concatenated the catapult with the catamaran";
   MyString t = "cat";
   MyString result = s - t;

   // result now stores "The bob conenated the apult with the amaran";

*/

#include<cstring>
#include<iostream>
#include<cctype>
#include "mystring.h"

using namespace std;


// -------------- Friend Functions -------------

ostream& operator<< (ostream& os, const MyString& s)
{
	os<<s.str;	//print out the str private data
	return os;
}

istream& operator>> (istream& is, MyString& s)
{
	//assume we alwways will enter something
	//two spaces already
	s.str  = new char[2]; // one for something, one for null-terminator
	char my_char; //place holder for user input
	s.size = 1; // size is 0
	is >> ws; //ignore white spaces
	while(is.get(my_char) && !isspace(my_char))
	{
		char *temp = new char[s.size + 1]; // add a new space
		strcpy(temp, s.str); 	// copy c-string inside s to temp
		delete [] s.str;	// deallocat the space for s.str, we need to reassign it
		s.str = temp;		// put temp into s.str, now temp and s.str share the same address
		s.str[s.size-1] = my_char; // my_char will be insert into the previous space
		s.size++; //increase size since we inserted a character
	}
	s.str[s.size] = '\0';	//last space is the null-terminator
	return is;
	
}
/*
 * The same logic as the previous one but different delimiter and no ignore of white spaces
 */
istream& getline(istream& is, MyString& s)
{
	char my_char;
	s.str = new char[2];
	s.size = 1;
	// here we do not have is>>ws since we do not need to ignore white spaces
	while(is.get(my_char) && my_char != '\n') // here is the only difference compare to previous one
	{
		char *temp = new char[s.size + 1];
		strcpy(temp, s.str);
		delete [] s.str;
		s.str = temp;
		s.str[s.size - 1] = my_char;
		s.size++;
	}
	s.str[s.size] = '\0';
	return is;

}

/*
 * The same logic as the previous one but different delimiter and does not ignore leading white spaces
 */

istream& getline(istream& is, MyString& s, char delim)
{
	char my_char;
	s.str = new char[2];
	s.size = 1;
	while(is.get(my_char) && my_char != delim)
	{
		char *temp = new char[s.size + 1];
		strcpy(temp, s.str);
		delete [] s.str;
		s.str = temp;
		s.str[s.size - 1] = my_char;
		s.size++;
	}
	s.str[s.size] = '\0';
	return is;
}

MyString operator+ (const MyString& s1, const MyString& s2)
{
	//since I cannot alter s1, I need to use copy/assignment consructor
	MyString result = s1; //assignment 
	result += s2;	// using += operator that was built
	return result;

}

MyString operator- (const MyString& s1, const MyString& s2)
{
	//declare temp to hold s1, since we cannot alter s1
	int k = 0;	// loop holder
	char *temp1;
	temp1 = new char[s1.size + 1]; // allocated s1.size + 1, +1 for null-terminator
	strcpy(temp1, s1.str);	// copy s1.str into temp1
	MyString result(temp1); //conversion constructor to initialize result
	delete [] temp1;	// deallocate the memeory for temp1 
	temp1 = nullptr;	// set temp1 to null-ptr for safety
	//find the index of matching string
	while (result.indexOf(s2) != -1)	//use the indexOf function to to find the index of the match string that we want to start subtracting.
	{
		k = result.indexOf(s2); // loop holder, set the index to k
		/*
		 * Here I used shift logic,
		 * basically, depends on the size that we want to minus, we run the outerside loop many times
		 * inner loop, just ship the array one by one.
		 */
		
		
		for(int j = 0; j < s2.size; j++) 
	 	{
			for(int c = k; c < result.size; c++)
			{
				result.str[c] = result.str[c+1];
			}

		}
		result.size = result.size - s2.size;
			
	}
	result.resize(result.size);//resize MyString so it does not have unused space
	return result;
}

bool operator< (const MyString& s1, const MyString& s2)
{
	if (strcmp(s2.str, s1.str) > 0 ) // if s2 > s1, return true
		return true;
	else
		return false;
}

bool operator> (const MyString& s1, const MyString& s2)
{
	if (strcmp(s1.str,s2.str) > 0)	// if s1 > s2, return true
		return true;
	else
		return false;
}

bool operator<= (const MyString& s1, const MyString& s2)
{
	if (strcmp(s2.str,s1.str) >= 0 ) // if s2>= s1 return true
		return true;
	else
		return false;
}

bool operator>= (const MyString& s1, const MyString& s2)
{
	if (strcmp(s1.str,s2.str)>= 0 ) // if s1>=s2 return true
		return true;
	else
		return false;
}

bool operator== (const MyString& s1, const MyString& s2)
{
	if (strcmp(s1.str,s2.str) == 0) // if s1 and s2 are the same, return true
		return true;
	else
		return false;
}

bool operator!= (const MyString& s1, const MyString& s2)
{
	if (strcmp(s1.str, s2.str) != 0) // if s1 and s2 are not the same, return true
		return true;
	else
		return false;
}

//------------------- Membeer Functions ------------------

MyString::MyString()
{
	size = 0;
	str = new char[1]; // dynamic allocation for my str object
	str[0] = '\0'; // null-terminator
}

MyString::MyString(const char* s)  //conversion constructor
{
	size = strlen(s); // equal to the size of the c-string we are passing in
	str = new char[size + 1]; // for null-terminator
	strcpy(str, s); // no need to add null-terminator, strcmp handles it automatically

}


MyString::MyString(const MyString& s) // copy constructor
{
	size = strlen(s.str); // get the size of s
	str = new char[size + 1]; // a room a null-terminaort
	strcpy(str, s.str); //copy of the str object 
			    // no need of null-terminator, strcpy handles it automatically
}

MyString::MyString(int a)
{
	int size = 0;
	int temp = 0;
	int i = 0;
	if (a>= 0)
	{
		size = 1; //at lease size will be one
		temp = a; //set temp variable to determine size
	}
	
	else
	{
		size = 1; // a negative sign
		temp = -a; //now temp is positive
	}
	
	while (temp != 0)
	{
		size++; // increase by
		temp /= 10;
	}

	str = new char[size + 1]; // save a space for null-terminator
	if (a == 0)
		i = size - 1;
	else
		i = size - 2; // insert digit backward
	if (a>=0)
	{
		for (int j = i; j>= 0; j--)
		{
			str[j] = '0' + (a%10);
			a /= 10; // go to next last digit

		}
	}

	else
	{
		for (int j = i+1; j>0; j--)	// loop to index 1 and save index 0 for '-';
		{
			str[j] = '0' + ((-a)%10);
			a /= 10;
		}
		str[0] = '-';
	}

	str[size] = '\0'; // add null-terminator
}

MyString::~MyString()
{
	delete [] str;
}

MyString& MyString:: operator=(const MyString& s)
{
	if(this != &s)
	{
		delete [] str; // release the space first
		size = s.size;
		str = new char[s.size + 1];
		strcpy(str, s.str);
	}

	return *this;
}

MyString& MyString::operator+=(const MyString& s)
{
	//declare a dynamic array with size and s.size + 1 for null terminator
	size = size + s.size;
	char *temp = new char[size + 1];
	//copy str to temp
	strcpy(temp, str);
	//cat s.str to temp
	strcat(temp, s.str);
	// completetion of the new string
	//
	// deallocate the str for new space
	
	delete [] str;
	str = temp; // allocated str to temp address
	
	return *this; // return itself
}

char& MyString::operator[] (unsigned int index)
{
	if (index >= size)   // if we want a index that is bigger or equalto our array size. The last character is '\0'
		resize(index + 1); // we should increase our array size by index + 1
	return str[index];

}

const char& MyString::operator[] (unsigned int index) const 
{
	if (index >= size)
	{
		// if index if equal or larger than the current size
		static char nullChar = '\0'; // we return null character
        return nullChar;

	}

	return str[index];
}


MyString& MyString::insert(unsigned int index, const MyString& s)
{

	resize(size + s.size + 1); //now I have enough space to carry all the chcaracters
	//in order to insert, I need to shift all my characters to the right
	
	char *temp = new char[size+1]; // create  a c-string holder	
	strcpy(temp, str);	//copy my intact c-string to temp
	for(int i = index; i < size + 1; i++)	//shift all the characters base on insertion #
	{
		str[i+s.size] = temp[i];	// doing the shift
	}
	
	delete [] temp;		//after the shift, deallocate temp
	temp = nullptr;		//assign it to nullptr for safety
	

	int j = 0;		// begin to insert our desired array
	for(int k = index; k < index + s.size; k++)
	{
		str[k] = s.str[j];	//insert
		j++;
	}
		
	return *this;
}

int MyString::indexOf(const MyString& s) const
{
	for (int i = 0; i< size - s.size; i++)  //go through the loop
	{
		bool found = true; //set initial found value is true
		for (int j = 0; j<s.size; j++) // go through s
		{
			if(str[i+j] != s.str[j])// if mismatch found
			{
				found = false; // set found to false
				break; // since a mismatch is found, we break inside loop and go to outside. 
			}
		}

		if (found) // only when found is true, we return the index
			return i;
	
	}

	return -1; //return -1 if no match was found
}

int MyString::getLength() const
{
	return size; // return the length
}

const char* MyString::getCString() const
{
	return str; // return the str
}

// a is the starting index and length is how long we want
MyString MyString::substring(unsigned int a, unsigned int length) const
{
	int sublen = 0; // initialize the interval length that I want get from the string
	a = static_cast<int>(a);
	if (a >= size)
		return MyString(); // if the a is bigger or equal to size, we put it as empty string
	if (a + length >= size)
		sublen = size - a; // if a + length go out of bound, we just want size - a
	else
		sublen = length;

	char *temp = new char[sublen + 1]; // allocated a space for temp to hold substr
	for (int i = 0; i<sublen; i++)
	{	
		temp[i] = str[a]; //read in substring
		a++;
	}

	temp[sublen] = '\0'; // null-terminator
	
	MyString sub(temp); // call the conversaion constructor
	delete [] temp; //deallocate the space
	temp = nullptr;	//set to null pointer

	return sub;	//return desired mystring

}

// the following function is the same logic as previous without the length part
MyString MyString::substring(unsigned int a) const
{
	int sublen = 0;
	a = static_cast<int>(a);
	if (a>= size)
		MyString();
	else
		sublen = size - a;

	char *temp = new char[sublen + 1];

	for (int i = 0; i <sublen; i++)
	{
		temp[i] = str[a];
		a++;
	}

	temp[sublen] = '\0';

	MyString sub(temp);
	delete [] temp;
	temp = nullptr;

	return sub;
}

void MyString::resize(int newsize) // resize the string to new size
{
	char *temp = new char[newsize + 1]; //room for null-terminator
	strncpy(temp, str, newsize); // copy the old string into temp, make sure it can handle decrease as well.
	for(int i = size; i < newsize; i ++)
		temp[i] = ' '; //fill the new spots with white space
	temp[newsize] = '\0'; // null-terminator in the end.
	delete [] str; //deallocate the space for str;
	str = temp; //reassign the address
	size = newsize; // set the size to newsize
}

