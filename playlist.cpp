/*
 Name: Tendo Chen
 Course: COP 3330
 Section: 6
 Project number: 4
 Function definition for PlayList Class:
 1. Insert: insert new entry into playlist
 2. Lookup: look up an entry based on title or artisit, if title: frist entry, if artist: all
 3. Remove: remove an entry based on title
 4. PlayListShow: Show all the entries in playlist in table with individual row and a summary info of #songs and size in MB with 2 decimal
 5. CatSum: same as above with based on category specified by user
 6. PlayListSize: show the total size of playlist in KB
 7. PlayListSort: sort the play list based on artist or title (ascending)
*/

 
//headers
#include "playlist.h"
#include <iomanip>
#include <iostream>
#include <cstring>
#include <cctype>

using namespace std; //namespace std so i do not need to type std;

Playlist::Playlist() //default constructor
{
	maxSize = 5; // 5 slots initially
	currentSize = 0; //0 entries
	songList = new Song[maxSize]; //dynamic allocation ofr songList 
}

Playlist::~Playlist()
{
	delete [] songList; //de-constrcutor to de-allocate the memeory 
}

void Playlist::Insert(const char* t, const char* a, Style st, int sz)
{
	if (currentSize == maxSize) //if we reach the size of five, we are going to grow or dynamic arrary by an increment of 5
		Grow(); //function call to increase the size of the array
	songList[currentSize++].Set(t, a, st, sz); //insert a new song;
}

void Playlist::Lookup(const char* t) const
{
	int i; //for loop initialization
	int count = 0; //counter for Not Found;
	int thisSong = FindSong(t); //call find song function to see if we have a match if we are searching based on title
	if (thisSong != -1)
	{
		cout<<"\nSoung Found:\n";
		cout<<songList[thisSong]<<endl; //print the first song that we found if we are searching based on title
		count++; //counter increment means we have a match
	}
	else
	{	
		cout<<endl;
		for(i = 0; i<currentSize;i++) //for loop to loop through the list if we are looking for artist
		{
		if ((strcmp(songList[i].GetArtist(),t) == 0))
		{// return all the match entries if we are searching based on artist
			cout<<songList[i];
			count++;
		}
		}

	}

	if (count == 0) // if counter is 0, we tell user we retrieved nothing
		cout<<t<<": Not Found"<<endl;
}

void Playlist::Remove(const char* t)
{
	
	int empty_slots = maxSize - currentSize; //check if current we more than 5 empty slots
	if (empty_slots == 5) //if we have 5 empty slots, we decrease the size
		Shrink(); //call shrink function to decrease current size of array
	int thisSong = FindSong(t); //Locate the name in the directory.
	if (thisSong == -1) // if we did not find the song, we print a message
		cout<<'\n'<<t<<" not found in the playlist\n"<<"* No deletion performed *"<<endl;
	else
	{ // if we found the song, we are going shift the songs come after this song
		for (int j = thisSong + 1; j <currentSize; j++)
			songList[j-1] = songList[j];
		currentSize--; 		//Decrement the current number of entries.
		cout<< "Song removed!\n";
	}

}

void Playlist::PlayListShow() const
{
	int i; //for loop int initilization
	if(currentSize == 0) // if no entries in playlist
	{
		cout<<"No songs currently in playlist"<<endl;
		cout<<endl;
		cout<<"Numer of songs = 0"<<endl;
		cout<<"Total playlist size = 0.00 MB"<<endl;
		cout<<endl;
	}
	
	else  // if we have songs
	{
		// put blank spaces to make it into a table
		cout<<"\n*Title*";
		for(i = 8; i< 36;i++)  
			cout<<" ";
		cout<<'\t'<<"*Artist*";
		for(i = 9; i < 21; i++)
			cout<<" ";
		cout<<'\t'<<"*Style*";
		for(i = 8; i < 11; i++)
			cout<<" ";
		cout<<'\t'<<"*Size (MB)*\n\n";
		for(i = 0; i < currentSize; i++)
			cout<<songList[i]; //print all the songs
		cout<<endl;
		cout<<"Number of songs = "<<currentSize<<endl; // #of songs
		double totalsize = 0;
		for(i = 0; i < currentSize; i++) //loop to calculate the total size of our playlist
			totalsize += (static_cast<double>(songList[i].GetSize())/1000);
		cout<<"Total playlist size = "<<fixed<<setprecision(2)<<totalsize<<" MB"<<endl; //print out 2 decimal places
	}
}

void Playlist::CatSum(Style st) const
{	/*
	 * initialize parameters for size, #songs and loop
	 */
	int totalsize = 0; 
	int numSong = 0;
	int i;
	cout<<endl;
	
	for(i = 0; i < currentSize; i++)
	{
		if(songList[i].GetCategory() == st) // if the category matches the category specified by user, then we add up size
		{
			cout<<songList[i];	//print out the song if matches the category
			totalsize += songList[i].GetSize(); //increaes size counter
			numSong++;	//increase #songs counter
		}
	}
		cout<<endl;
		// print out the #songs and total sizes in two decial places in terms of MB
		cout<<"Total songs in this category = "<<numSong<<endl;
		cout<<"Total file size = "<<fixed<<setprecision(2)<<(static_cast<double>(totalsize)/1000)<<" MB"<<endl;
	
}

void Playlist::PlayListSize() const
{	
	/*
	 * calculate total sizes in terms of kilobytes
	 */
	int totalsize = 0;
	int i;
	for(i=0; i< currentSize; i++)
		totalsize += songList[i].GetSize();
	cout<<"Total size of playlist = "<<totalsize<<" kilobytes"<<endl;
}


void Playlist::Grow()
{
	maxSize = currentSize + 5; //increase size of 5
	Song* newList = new Song[maxSize]; // dynamically array for our new array
	int i; //loop integer initialization
	for (i = 0;i < currentSize; i++)	//loop to deep copy the array
		newList[i] = songList[i];	//now our new list have all the entries from old song list
	delete [] songList; //de-allocate the old song list
	songList = newList; // deep copy the new list
	
	//print out the statement that we have resized the array
	cout<<"\n** Array being resized to "<<maxSize<<" allocated slots."<<endl;
}

void Playlist::Shrink()
{
	/*
	 * this chunk of the code is the same logic as the Grow, only the first line is different
	 */
	maxSize = currentSize; // now we set the maxSize to current since we are going to shrink the holding size to the current size based on specficiation.
	Song* newList = new Song[maxSize];
	int i;
	for (i = 0; i <currentSize; i++)
		newList[i] = songList[i];
	delete [] songList;
	songList = newList;

	cout<<"\n** Array being resized to "<<maxSize<<" allocated slots."<<endl;
}

void Playlist::PlayListSort(char SortType)
{
	/*
	 * sort based on A or T, lowercase letter 'a' and 't' is not need here cuz in the menu.cpp there is a function to covert the letter to uppercase
	 */
	for (int i = 0; i < currentSize - 1; i++) //loop through the entries from beginning and the 2nd last one
	{
		for (int j = 0; j < currentSize - i - 1; j++) // putting the larger one in the last position, hence, j=0 as i increases, we only need to check previous postion and throw the largest into the last possible position
		{
			int c_result = 0;
			if (SortType == 'A')
			{ //sort based on Artist
				c_result = strcmp(songList[j].GetArtist(),songList[j+1].GetArtist());
			}
			else
			{	// srot based on Title
				c_result = strcmp(songList[j].GetTitle(), songList[j+1].GetTitle());
			}

			if (c_result > 0) //if the c_result is larger than 0, that means the current j is bigger than the next j, hence, we throw current j into next j
			{	
				//mini swap function
				Song temp;  //temp song
				temp = songList[j]; //put the current j into temp 
				songList[j] = songList[j+1]; //put j+1 into j, since j+1 is smaller than j
				songList[j+1] = temp; // now j+1 psotion has the larger one
			}
		}
	}
}

int Playlist::FindSong(const char* aSong) const
{
	/*
	 * function returns the first postion that we want, 
	 * if we did not find the song, we return -1;
	 */
	int i;
	for (i = 0; i < currentSize; i++) // loop through the whole song list. 
		if (strcmp(songList[i].GetTitle(), aSong) == 0)
			return i;
	return -1;
}
