/*
 Name: Tendo Chen
 Course: COP 3330
 Section: 6
 Project number: 4
 Function definition for Song Class:
//Definition of class Entry for a phone directory.
//<iostream.h> is already included in "SONG.H"

                        /* operator<< function

The operator<< overload should print out a Song object on one line (to
the given ostream) -- use no more than 80 characters per line -- as
follows, in an organized manner. Size should be printed in Megabytes
(use 1000 kilobytes = 1 MB for this calculation), to 1 decimal place.
The category abbreviations used should be: Pop, Rock, Alt, Ctry, HH, Par
 Title                           Artist           Style   Size (MB)

 Examples:
 Pictures of You                    The Cure            Alt       4.4
 Bohemian Rhapsody                  Queen               Rock      5.7
 What Does the Fox Say              Ylvis               Par      12.6
 
 */

                                //Set Function
//  parameters and loaded into the member data of the object.  (i.e.
//  this function "sets" the state of the object to the data passed in).
//  The parameters t, a, st, and sz represent the title, artist, style,
//  and size of the song file, respectively.


//GetTitle() GetArtist() GetSize() GetCategory()
//return title, artist, size, category/style


//Definition of class Song
//<iostream.h> is already included in "SONG.H"

#include <cstring>	//for strlen, strcpy
#include "song.h" 	//for class Song
#include <iomanip>	//for decimal display
#include <cctype>	//not really needed but why not?

using namespace std;

//------------ Operator Overloading Function ---------- 
ostream& operator<<(ostream& os, const Song& s)
{
	int i;	//for loop
	int j;	//for Style abbr. spaces
	
	/*
	 * the follwing for loops are trying to create a well-strcutured table format
	 */
	os<<s.title;
	for (i = strlen(s.title) + 1;i < 36; i++)
		os.put(' ');
	os<<'\t'<<s.artist;
	for (i = strlen(s.artist) + 1; i< 21; i++)
		os.put(' ');
	os<<'\t';
	/*
	 * Swithc statement to get proper abbr. for each category.
	 */
	switch(s.GetCategory())
	{
		case POP:
			os<<"Pop";
			j = 3;
			break;
		case ROCK:
			os<<"Rock";
			j = 4;
			break;
		case ALTERNATIVE:
			os<<"Alt";
			j = 3;
			break;
		case COUNTRY:
			os<<"Ctry";
			j = 4;
			break;
		case HIPHOP:
			os<<"HH";
			j = 2;
			break;
		case PARODY:
			os<<"Par";
			j = 3;
			break;
	}
	for (i = j + 1; i < 11; i++)
		os.put(' ');
	//put size into proper MB format with 1 decimal place based on direction
	os<<'\t'<<fixed<<setprecision(1)<<(static_cast<double>(s.size) / 1000);
	os<<'\n';

	return os;

}



//------------ Member Function ------------

Song::Song()
//Default constructor for title, artist, category and size
{
	strcpy(title, " ");
	strcpy(artist, " ");
	category = POP; //dummy category for initialization
	size = 0;
}

void Song::Set(const char* t, const char* a, Style st, int sz)
{
	//set the song entry based on parameters given by user
	strcpy(title, t); 
	strcpy(artist, a);
	category = st;
	size = sz;
}

const char* Song::GetTitle() const
{
	return title; //return the name of the song
}

const char* Song::GetArtist() const
{
	return artist; //return name of the artist
}

int Song::GetSize() const
{
	return size; //return the size of the song
}

Style Song::GetCategory() const
{
	return category; //return style of the song
}
