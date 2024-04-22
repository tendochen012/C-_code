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
#include "mixed.h"
#include <iomanip>

//friend functions

// input stream function for user to enter mixed number;
istream& operator>>(istream& is, Mixed& m)
{
	char sep2; //space holder for "/"
	//assume the format will be a b/c	
	is >> m.i_part>>m.numerator>>sep2>>m.denominator;
	if((m.denominator == 0) || (m.denominator < 0))  
	{
		//if denominator entered is smaller than 0 or 0, then we set the mixed number to 0
		m.denominator = 1;
		m.numerator = 0;
		m.i_part = 0;
	}
	else if ((m.i_part != 0) && (m.numerator < 0))
	{
		// if the mixed number has integer part, the numerator cannot be negative
		// if it is negative, we set the mixed number to 0
		m.i_part = 0;
		m.denominator = 1;
		m.numerator = 0;
	}
	
	return is;
	
	/*
	is >>i>>sep1>>n>>sep2>>d;
	if(((d==0) || d <0) || ((i != 0) && (n < 0)))
	{
		m.i_part = 0;
		m.numerator = 0;
		m.denominator = 1;
	}

	else
	{
		m.i_part = i;
		m.numerator = n;
		m.denominator = d;
	}
	
	return is;
	*/
}

ostream& operator<<(ostream& os, const Mixed& m)
{
	if (m.i_part != 0) // 1st case: when integer is not 0
	{
		if(m.i_part < 0)
		{	//if intger part is small than 0
			if(m.numerator == 0)
			{
				return os<<"-"<<-m.i_part; //we only print out the integer part since numerator is 0.
			}

			else
			{
				return os<<"-"<<-m.i_part<<" "<<m.numerator<<"/"<<m.denominator;
				//if numerator is not 0, we print all the numbers
				// formart: "a b/c".
			}
		}
		else
		{	//if integer is part is bigger than 0
			if(m.numerator == 0)
			{	
				return os<<m.i_part; // we only prin out the integer part
			}
			
			else
			{	// else we print out all the numers.
				// format: "a b/c"
				return os<<m.i_part<<" "<<m.numerator<<"/"<<m.denominator;
			}
		}
	}

	else // if interger part is 0, we only print out the fraction part if numerator is not 0, otherwise, we only print 0.
	{
		if(m.numerator == 0)
		{
			// print 0
			return os<<m.i_part;
		}

		else
		{
			//print out only fraction part and handle the negative numberator
			if(m.numerator < 0)
				return os<<"-"<<-m.numerator<<"/"<<m.denominator;
			else
				return os<<m.numerator<<"/"<<m.denominator;
		}
	}

}

Mixed operator+ (const Mixed& m1, const Mixed& m2)
{
	Mixed result; // Mixed type result to hold the result of plus
    	Mixed m1_cp = m1; // make a m1 copy since do not want to change original state
    	Mixed m2_cp = m2;
	// convert to improper fractions for easy calculations
	m1_cp.ToFraction();
	m2_cp.ToFraction();
	// perform addition: a/b + c/d
	// 1st step: conver denominator to common denominator: b*d
	// 2nd step: convert and add numerator: a*d + c*b
	// find step: simplify to lowest terms and convert improper part to proper
	result.denominator = m1_cp.denominator * m2_cp.denominator;
	result.numerator = m1_cp.numerator * m2_cp.denominator + m2_cp.numerator * m1_cp.denominator;
    	result.Simplify();
    	return result; // return our result
}

Mixed operator- (const Mixed& m1, const Mixed& m2)
{
    	/*
	 * this is the same logic as Addition, we change + to -
	 */
	Mixed result;
    	Mixed m1_cp = m1;
    	Mixed m2_cp = m2;
    	m1_cp.ToFraction();
    	m2_cp.ToFraction();
    	result.denominator = m1_cp.denominator * m2_cp.denominator;
    	result.numerator = m1_cp.numerator * m2_cp.denominator - m2_cp.numerator * m1_cp.denominator;
    	result.Simplify();
    	return result;
}

Mixed operator* (const Mixed& m1, const Mixed& m2)
{
    	Mixed result;
    	Mixed m1_cp = m1;
    	Mixed m2_cp = m2;
    	m1_cp.ToFraction();
    	m2_cp.ToFraction();
	// perform multiplication: a/b * c/d = a*c/b*d
	// numertor multiply numerator and denominator multiply denominator
    	result.denominator = m1_cp.denominator * m2_cp.denominator;
    	result.numerator = m1_cp.numerator * m2_cp.numerator;
    	result.Simplify();
    	return result;
}

Mixed operator/ (const Mixed& m1, const Mixed& m2)
{
    Mixed result; 
    Mixed m1_cp = m1;
    Mixed m2_cp = m2;
    if ((m2_cp.i_part ==0) && (m2_cp.numerator == 0))
	// if we are dividing a 0, we just return 0,
	// to qualfy as 0, both integer and numertor are 0
        return result; // return default constructor
    else
    {
        m1_cp.ToFraction(); // turn into improper fraction 
        m2_cp.ToFraction(); // turn into improper fraction
        
	// the following are checking if the division invloves negative sign
	// since denomintor cannot be used as a check point, the code is quite lengthy
	// because we convert this into improper fractions already, we do not need to check integer part
        if ((m1_cp.numerator < 0) && (m2_cp.numerator > 0))
        { // if m1 is negative, m2 is postive, the result should be negaive
	  // division is like a/b / c/d = a*d/b*c
            result.numerator = -m1_cp.numerator * m2_cp.denominator; // ignore negative sign since it does not affect calculation
            result.denominator = m1_cp.denominator * m2_cp.numerator; 
            result = result * -1; // utilize the * operator that we defined before to turn into negative
            return result;
            
        }
        else if ((m1_cp.numerator > 0 ) && (m2_cp.numerator <0))
        {
	/*
	 * same logic as above
	 */
            result.numerator = m1_cp.numerator * m2_cp.denominator;
            result.denominator = m1_cp.denominator * -m2_cp.numerator;
            result = result * -1; 
	    // no need to simplify since the * operator simplfiy our result already.
            return result;
        }
        else if ((m1_cp.numerator <0) && (m2_cp.numerator <0))
        {
	// two negative will yield a psotive result
            result.numerator = -m1_cp.numerator * m2_cp.denominator;
            result.denominator = m1_cp.denominator * -m2_cp.numerator;
            result.Simplify(); // simplify function cuz we haven't used * operator, hence we need to simplfiy our result
            return result;
        }
        
        else
        {
	// same logic as above without the neagative sign
            result.numerator = m1_cp.numerator * m2_cp.denominator;
            result.denominator = m1_cp.denominator * m2_cp.numerator;
            result.Simplify();
            return result;
        }
        
    }
}

/*
 * the following comparison operator is using Evaluate function to compare values
 * between them
 */

bool operator> (const Mixed& m1, const Mixed& m2)
{
	if (m1.Evaluate() > m2.Evaluate())
		return true;
	else
		return false;
}

bool operator< (const Mixed& m1, const Mixed& m2)
{
	if (m1.Evaluate() < m2.Evaluate())
		return true;
	else
		return false;
}

bool operator<= (const Mixed& m1, const Mixed& m2)
{
	if (m1.Evaluate() <= m2.Evaluate())
		return true;
	else
		return false;
}

bool operator>= (const Mixed& m1, const Mixed& m2)
{
	if (m1.Evaluate() >= m2.Evaluate())
		return true;
	else
		return false;
}

bool operator== (const Mixed& m1, const Mixed& m2)
{
	if (m1.Evaluate() == m2.Evaluate())
		return true;
	else
		return false;
}

bool operator!= (const Mixed& m1, const Mixed& m2)
{
	if (m1.Evaluate() != m2.Evaluate())
		return true;
	else
		return false;
}


//constructor for Mixed
Mixed::Mixed(int i, int n, int d)
{
	/*
	 * if d is 0 or negative, we will initlize our mixed number to 0
	 * if i is not 0 but numerator is negative, this is also invalid, so we also initilize the number to 0
	 */
	if(((d==0) || (d <0)) || ((i !=0) && ( n<0)))
	{
		i_part = 0;
		numerator = 0;
		denominator = 1;
	}
	else
	{
		i_part = i;
		numerator = n;
		denominator = d;
	}
}

Mixed::Mixed(int i)
{
	/*
	 * acted as default constructor for mixed number,
	 * if no value is specified, we initalize to 0
	 * otherwise, the mixed number only contains integer part
	 */
	i_part = i;
	numerator = 0;
	denominator = 1;
}

double Mixed::Evaluate() const
{
	double result; 		// result variable to store the result
	double d_numerator; 	// double format of the numerator
	double d_i_part; 	// double format of the integer
	double d_denominator;	// double format of the denominator
	double div_part;	// div_part variable to store the fraction double format
	if (numerator == 0)
	{
		result = static_cast<double>(i_part);	// if numerator is 0, it means it only has the integer part,
							// static case the integer part to double
		return result;	
	}
	else 
	{	/*
		 * the following logic checks if the number being evaluated is a negative number
		 * if negative is spotted, we are going to change it to a positve number to evaluate 
		 * to make sure we get the correct value, if we carry negative sign, it will cause a wrong value
		 */
		if (numerator < 0)
		{
			d_numerator = static_cast<double>(-numerator); 
			d_i_part = static_cast<double>(i_part);
		}
		else if (i_part < 0)
		{
			d_i_part = static_cast<double>(-i_part);
			d_numerator =static_cast<double>(numerator); 
		}
		else
		{
			d_i_part = static_cast<double>(i_part);
			d_numerator = static_cast<double>(numerator);
		}
			
		d_denominator = static_cast<double>(denominator); // denomintor will always be positive
		div_part = d_numerator/d_denominator; // get the fraction in decimal
		result = d_i_part + div_part; // add together to get the true decimal number
		

		if ((numerator < 0) || (i_part < 0 ))	// if it is negative, we will return the -result
			return -result;
		else
			return result;			//otherwise, we return the result
	}

}	

void Mixed::Simplify()
{

	//find the biggest common divisor using Euclidean algorithm
	int hold_n;
	int hold_i;

	hold_n = numerator; 	// a variable to hold the numerator
	hold_i = i_part;	// a variable to hold the integer

	if (hold_n < 0)
		numerator = -numerator;	//same convert the negative number to positive for evaluation purpose
	if (hold_i < 0)
		i_part = -i_part;
	/*
	 * the following code is using Euclidean algorithm to find the greatest common divisor to simplify
	 */

	int a = numerator;
	int b = denominator;
	int c;
	while (b != 0)
	{
		int hold = b;
		b = a%b;
		a = hold; 
	}
       	// right now a is the greatest common divisor for both numrator and denominator
	numerator = numerator / a;
	denominator = denominator / a;
	// now numerator and denominator are in lowest terms
	
	if (numerator >= denominator) // check if it is improper
	{
		c = numerator/denominator; // the whole number to be added to integer part
		numerator = numerator - (c * denominator); // non-proper numerator
		i_part = i_part + c; // final integer value after simplify

		if ((hold_n < 0 ) || (hold_i < 0))
			i_part = - i_part; // if it is negitve, we change it back to negative

	}

	else
	{ // case where is already in the proper format of the fraction part.
		/*
		 * we don't need to do anything further other than change the format. 
		 */
		if(hold_i == 0)
		{	if(hold_n < 0)
				numerator = - numerator;
		}
		else
		{
			if(hold_i < 0)
				i_part = -i_part;
		}
	}

	
}

void Mixed::ToFraction()
{
	//we only need to convert if the mixed number has an integer part, otherwise 
	//the function does not need to do anything
	if (i_part != 0) // check if mixed number has an integer part
	{
		if(i_part < 0) // if smaller than 0, we need to convert the numerator to negative
		{
			i_part = -i_part; // change to positive for easy evaluation
			numerator = -(i_part * denominator + numerator); // get the final numerator part
			i_part = 0; // set integer part of mixed to 0 after we called ToFraction.
		}
		else
		{
			//same logic as above without negative part.
			numerator = (i_part * denominator + numerator); 
			i_part = 0;
		}
	}
}

Mixed& Mixed::operator++() // pre-fix
{
	i_part = i_part + 1;	//increment 
	return *this;		//return the increased
}

Mixed Mixed::operator++(int) //post-fix
{
	Mixed temp = *this;	// placed holder before increment
	i_part = i_part + 1;	// still increase
	return temp;		// return the holer
}

Mixed& Mixed::operator--() //pre-fix
{
	i_part = i_part - 1;	//same logic as pre-fix increment but decrement
	return *this;
}

Mixed Mixed::operator--(int) //post-fix
{
	Mixed temp = *this;	//same logic as post-fix increment but decrement
	i_part = i_part - 1;
	return temp;
}
