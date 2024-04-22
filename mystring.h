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

#include <iostream>
using namespace std;

class MyString
{
  friend ostream& operator<< (ostream& os, const MyString& s);
  friend istream& operator>> (istream& is, MyString& s);
  friend istream& getline (istream& is, MyString& s);
  friend istream& getline (istream& is, MyString& s, char delim);

  friend MyString operator+ (const MyString& s1, const MyString& s2);
  friend MyString operator- (const MyString& s1, const MyString& s2);

  friend bool operator< (const MyString& s1, const MyString& s2);
  friend bool operator> (const MyString& s1, const MyString& s2);
  friend bool operator<=(const MyString& s1, const MyString& s2);
  friend bool operator>=(const MyString& s1, const MyString& s2);
  friend bool operator==(const MyString& s1, const MyString& s2);
  friend bool operator!=(const MyString& s1, const MyString& s2);

public:
  MyString();				// empty string
  MyString(const char* s);		// conversion from c-string
  MyString(int a);			// conversion from int
  ~MyString();				// destructor
  MyString(const MyString& s);		// copy constructor
  MyString& operator=(const MyString& s);   // assignment operator

  MyString& operator+=(const MyString& s);  // concatenation/assignment

  // bracket operators to access char positions
  char& operator[] (unsigned int index);
  const char& operator[] (unsigned int index) const;

  // insert s into the string at position "index"
  MyString& insert(unsigned int index, const MyString& s);

  // find index of the first occurrence of s inside the string
  //  return the index, or -1 if not found
  int indexOf(const MyString& s) const;
  
  int getLength() const;		// return string length
  const char* getCString() const;	// return c-string equiv

  MyString substring(unsigned int , unsigned int ) const;
  MyString substring(unsigned int ) const;

private:

  // declare your member data here
  int size; // size of my string
  char * str; //c-string array
  void resize(int newsize); // resize the string to new size
};
