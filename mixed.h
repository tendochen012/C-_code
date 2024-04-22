/*
 Name: Tendo Chen
 Course: COP 3330
 Section: 6
 Project number: 3
 Function definition for Mixed Number projects:
    1. >>: for user to enter mixed number in the formart of a b/c
    2. <<: prin the mixed number on the screen
    3. +, -, *, /, normal operations for mixed numbers
    4. ++, --, both prefix and postfix increment and decrement
    5. >, <, >=, <=, !=, ==, comparison operators for mixed numbers
    6. Evalute: This function evaluates the mixed into decimal format
    7. Simplify: This function simplify the mixed number into lowerst terms, if it is an improper fraction, it will turn into proper fraction
    8. ToFraction: This function turns mixed number into fraction format.
    9. Mixed(i, n, d) constructor for mixed number
    10. Mixed(i = 0), acted as default constructor, and integer part mixed number default constrcutor.
*/
#include <iostream>
using namespace std;

class Mixed
{
//Operator Overloadings
	friend istream& operator>>(istream& is, Mixed&m);	//operator overloading for >> to enter mixed number
	friend ostream& operator<<(ostream& os, const Mixed&m);	//operator overloading for << to print mixed number
	friend bool operator> (const Mixed& m1, const Mixed& m2); // > definition
	friend bool operator< (const Mixed& m1, const Mixed& m2); // < definition
	friend bool operator<= (const Mixed& m1, const Mixed& m2);// <= definition
	friend bool operator>= (const Mixed& m1, const Mixed& m2);// >= definition
	friend bool operator== (const Mixed& m1, const Mixed& m2);// == definition
	friend bool operator!= (const Mixed& m1, const Mixed& m2);// != definition
	friend Mixed operator+ (const Mixed& m1, const Mixed& m2);// + definition
	friend Mixed operator- (const Mixed& m1, const Mixed& m2);// - definition
	friend Mixed operator* (const Mixed& m1, const Mixed& m2);// * definition
	friend Mixed operator/ (const Mixed& m1, const Mixed& m2);// / definition
	
public:
	Mixed(int i, int n, int d); //constructor with three parameter to initialize a mixed number.
	Mixed(int i = 0); //constrcutor with one parameter to initialize whole numer as mixed number.
	//accessors
	double Evaluate() const; // evaluate the mixed number in decimal format
	//mutators
	void Simplify(); //Simplify fraction part into lowest terms, any improper fraction will turn into proper
	void ToFraction(); // change mixed number into improper or proper
     	Mixed& operator++(); //prefix increment
	Mixed operator++(int); //postfix increment
	Mixed& operator--(); //prefix decrement
	Mixed operator--(int); //postfix decrement	


private:
	int i_part; // integer part of mixed number
	int numerator;  //numerator part of mixed number
	int denominator;  //denominator part of mixed number
};
