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

#include "song.h"

class Playlist
{
public:
	Playlist();
	~Playlist();
	void Insert(const char* t, const char* a, Style st, int sz);	//Insert new entry to playlist
	void Lookup(const char* t) const;	//Look up in playlist based on a song name or artist
						//if based on song name: this will return the first item
						//if based on artist name: this will return all items
	void Remove(const char* t);	//remove an entry based on song name
	void PlayListShow() const;	//show all the songs in playlist
	void CatSum(Style st) const;	//display songs based on style, will show summary info: #songs and #size
	void PlayListSize() const;	//display #size of current playlist
	void PlayListSort(char SortType); //sort based on user's choice of letter, it can be A - Artists or T - Title

private:
	int maxSize, // the maximum allowable number of entries
	    currentSize; //the current number of entries
	Song* songList; //pointer to the list of songs
	void Grow(); 	//increase maximum size, when required
	void Shrink();  //decrease maximum size, when required
	int FindSong(const char* aSong) const; //Return index of an entry, given a name.
} ;
