#include "LibraryItem.h"
#include <iostream>
#include <iomanip>
using namespace std;

//Default constructor
LibraryItem::LibraryItem()
{
    id = 0;
    cost = 0.0;
    currentStatus = "none";
    loanPeriod = 0;
}

//Overloaded constructor
LibraryItem::LibraryItem(int id, float cost, string currentStatus, int loanPeriod)
{
    this->id = id;
    this->cost = cost;
    this->currentStatus = currentStatus;
    this->loanPeriod = loanPeriod;
}

//Accessor methods
int LibraryItem::getId()
{
    return id;
}

float LibraryItem::getCost()
{
    return cost;
}

string LibraryItem::getCurrentStatus()
{
    return currentStatus;
}

int LibraryItem::getLoanPeriod()
{
    return loanPeriod;
}


//Mutator methods
void LibraryItem::setId(int id)
{
    this->id = id;
}

void LibraryItem::setCost(float cost)
{
    this->cost = cost;
}

void LibraryItem::setCurrentStatus(string currentStatus)
{
    this->currentStatus = currentStatus;
}

void LibraryItem::setLoanPeriod(int loanPeriod)
{
    this->loanPeriod = loanPeriod;
}

//Prints library item info
void LibraryItem::print()
{
    cout << "Library ID: " << getId() << endl;
    cout << "Cost: $" << fixed << setprecision(2) << getCost() << endl;
    cout << "Current Status: " << getCurrentStatus() << endl;
    cout << "Loan Period (in days): " << getLoanPeriod() << endl;
}

//Outputs library item info to file
void LibraryItem::fileprint(ofstream &fout)
{
    fout << getId() << " " << getCost() << " ";
    fout << getCurrentStatus() << " " << getLoanPeriod() << " ";
}

//Operator overload for file output
ofstream& operator<<(ofstream &fout, LibraryItem &item)
{
    item.fileprint(fout);
    return fout;
}
