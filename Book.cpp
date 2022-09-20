#include <iostream>
#include "Book.h"
using namespace std;

//Default constructor
Book::Book():LibraryItem()
{
    author = "none";
    title = "none";
    isbn = 0;
    category = "none";
}

//Overloaded Constructor
Book::Book(int id, float cost, string currentStatus, int loanPeriod, string author, string title, int isbn, string category):LibraryItem(id, cost, currentStatus, loanPeriod)
{
    this->author = author;
    this->title = title;
    this->isbn = isbn;
    this->category = category;
}

//Get Functions
string Book::getAuthor()
{
    return author;
}

string Book::getTitle()
{
    return title;
}

int Book::getIsbn()
{
    return isbn;
}

string Book::getCategory()
{
    return category;
}

//Set Functions
void Book::setAuthor(string author)
{
    this->author = author;
}

void Book::setTitle(string title)
{
    this->title = title;
}

void Book::setIsbn(int isbn)
{
    this->isbn = isbn;
}

void Book::setCategory(string category)
{
    this->category = category;
}

//Print book info
void Book::print()
{
    LibraryItem::print();
    cout << "Author: " << getAuthor() << endl;
    cout << "Title: " << getTitle() << endl;
    cout << "ISBN: " << getIsbn() << endl;
    cout << "Category: " << getCategory() << endl << endl;
}

//Output book info to file
void Book::fileprint(ofstream &fout)
{
    LibraryItem::fileprint(fout);
    fout << "1" << endl;
    fout << getTitle() << endl;
    fout << getAuthor() << endl;
    fout << getIsbn() << " " << getCategory() << endl;
}
