#include <iostream>
#include "Patron.h"
using namespace std;

//Default Constructor
Patron::Patron()
{
    name = "none";
    id = 0;
    balance = 0.0;
    numItems = 0;
}

//Overloaded Constructor
Patron::Patron(string name, int id, float balance, int numItems)
{
    this->name = name;
    this->id = id;
    this->balance = balance;
    this->numItems = numItems;
}

//Get Functions
string Patron::getName()
{
    return name;
}

int Patron::getId()
{
    return id;
}

float Patron::getBalance()
{
    return balance;
}

int Patron::getNumberOfItems()
{
    return numItems;
}

//Set Functions
void Patron::setName(string name)
{
    this->name = name;
}

void Patron::setId(int id)
{
    this->id = id;
}

void Patron::setBalance(float balance)
{
    this->balance = balance;
}

void Patron::setNumberOfItems(int numItems)
{
    this->numItems = numItems;
}
