#include "DVD.h"
#include <iostream>
using namespace std;

//Default constructor
DVD::DVD():LibraryItem()
{
    title = "none";
    category = "none";
    runTime = 0;
    studio = "none";
    releaseDate = "none";
}

//Overloaded constructor
DVD::DVD(int id, float cost, string currentStatus, int loanPeriod, string title, string category, int runTime, string studio, string releaseDate):LibraryItem(id, cost, currentStatus, loanPeriod)
{
    this->title = title;
    this->category = category;
    this->runTime = runTime;
    this->studio = studio;
    this->releaseDate = releaseDate;
}

//Accessor methods
string DVD::getTitle()
{
    return title;
}

string DVD::getCategory()
{
    return category;
}

int DVD::getRunTime()
{
    return runTime;
}

string DVD::getStudio()
{
    return studio;
}

string DVD::getReleaseDate()
{
    return releaseDate;
}

//Mutator methods
void DVD::setTitle(string title)
{
    this->title = title;
}

void DVD::setCategory(string category)
{
    this->category = category;
}

void DVD::setRunTime(int runTime)
{
    this->runTime = runTime;
}

void DVD::setStudio(string studio)
{
    this->studio = studio;
}

void DVD::setReleaseDate(string releaseDate)
{
    this->releaseDate = releaseDate;
}

//Print dvd info
void DVD::print()
{
    LibraryItem::print();
    cout << "Title: " << getTitle() << endl;
    cout << "Category: " << getCategory() << endl;
    cout << "Run Time: " << getRunTime() / 60 << "h " << getRunTime() % 60 << "min" << endl;
    cout << "Studio: " << getStudio() << endl;
    cout << "Release Date: " << getReleaseDate() << endl << endl;
}

//Output dvd info to file
void DVD::fileprint(ofstream &fout)
{
    LibraryItem::fileprint(fout);
    fout << "3" << endl;
    fout << getTitle() << endl;
    fout << getCategory() << " " << getRunTime() << endl;
    fout << getStudio() << endl;
    fout << getReleaseDate() << endl;
}
