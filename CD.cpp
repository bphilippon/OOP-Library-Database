#include "CD.h"
#include <iostream>
using namespace std;

//Default constructor
CD::CD():LibraryItem()
{
    artist = "none";
    title = "none";
    numTracks = 0;
    releaseDate = "none";
    genre = "none";
}

//Overloaded constructor
CD::CD(int id, float cost, string currentStatus, int loanPeriod, string artist, string title, int numTracks, string releaseDate, string genre):LibraryItem(id, cost, currentStatus, loanPeriod)
{
    this->artist = artist;
    this->title = title;
    this->numTracks = numTracks;
    this->releaseDate = releaseDate;
    this->genre = genre;
}

//Accessor methods
string CD::getArtist()
{
    return artist;
}

string CD::getTitle()
{
    return title;
}

int CD::getNumTracks()
{
    return numTracks;
}

string CD::getReleaseDate()
{
    return releaseDate;
}

string CD::getGenre()
{
    return genre;
}

//Mutator methods
void CD::setArtist(string artist)
{
    this->artist = artist;
}

void CD::setTitle(string title)
{
    this->title = title;
}

void CD::setNumTracks(int numTracks)
{
    this->numTracks = numTracks;
}

void CD::setReleaseDate(string releaseDate)
{
    this->releaseDate = releaseDate;
}

void CD::setGenre(string genre)
{
    this->genre = genre;
}

//Print cd info
void CD::print()
{
    LibraryItem::print();
    cout << "Artist: " << getArtist() << endl;
    cout << "Title: " << getTitle() << endl;
    cout << "Number of Tracks: " << getNumTracks() << endl;
    cout << "Release Date: " << getReleaseDate() << endl;
    cout << "Genre: " << getGenre() << endl << endl;
}

//Output cd info to file
void CD::fileprint(ofstream &fout)
{
    LibraryItem::fileprint(fout);
    fout << "2" << endl;
    fout << getArtist() << endl;
    fout << getTitle() << endl;
    fout << getNumTracks() << endl;
    fout << getReleaseDate() << endl;
    fout << getGenre() << endl;
}