/*
*	Code from the OEVector Example Code was used as reference when creating this class
*/

#include "Patrons.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <iterator>
using namespace std;

//Return amount of patrons
int Patrons::getPatronCount()
{
    return patronCount;
}

//Return the vector
vector<Patron*> Patrons::getPatronVector()
{
    return patronVec;
}

//Load in Patron data
void Patrons::loadPatronData()
{
    ifstream fin;
    fin.open("patrons.dat");

    fin >> currentPatronId;		//stores current patron ID
    fin.ignore();

    string tempPatName;
    int tempPatId;
    float tempPatBal;
    int tempNumItems;
    while(getline(fin, tempPatName))	//scan in patron data
    {
        fin >> tempPatId;
        fin >> tempPatBal;
        fin >> tempNumItems;
        fin.ignore();

        patronVec.push_back(new Patron(tempPatName, tempPatId, tempPatBal, tempNumItems));	//allocates memory
        patronCount++;
    }
    fin.close();
}

//Store patron data
void Patrons::storePatronData()
{
    ofstream fout;
    fout.open("patrons.dat");

    fout << currentPatronId << endl;

    for(auto iter = patronVec.begin(); iter != patronVec.end(); iter++) //prints patrons as loaded
    {
        fout << (*iter)->getName() << endl;
        fout << (*iter)->getId() << " " << (*iter)->getBalance() << " ";
        fout << (*iter)->getNumberOfItems() << endl;
    }
    fout.close();
}

//Prints all patrons
void Patrons::printAllPatrons()
{
    int tempPatronCount = 1;
    for(auto iter = patronVec.begin(); iter != patronVec.end(); iter++)
    {
        cout << "[Patron " << tempPatronCount << "]" << endl;
        cout << "Name: " << (*iter)->getName() << endl;
        cout << "ID: " << (*iter)->getId() << endl;
        cout << "Balance: $" << fixed << setprecision(2) << (*iter)->getBalance() << endl;
        cout << "Number of Items Checked-Out: " << (*iter)->getNumberOfItems() << endl;
        cout << endl;

        tempPatronCount++;
    }
}

//Deallocates memory for all patrons
void Patrons::cleanupPatrons()
{
    for(auto iter = patronVec.begin(); iter != patronVec.end(); iter++)
    {
        delete *iter;
    }
    patronVec.clear();
}

//Add patron to vector
void Patrons::addPatron()
{
    Patron *tempPat;
    tempPat = new Patron();
    string patName;

    cout << "Enter patron's name: ";
    getline(cin, patName);

    tempPat->setName(patName);
    tempPat->setId(currentPatronId);
    patronVec.push_back(tempPat);
    currentPatronId++;
    patronCount++;
    cout << "Patron added." << endl;
}

//Delete patron from vector
void Patrons::deletePatron()
{
    int patId;
    cout << "Enter patron's ID: ";
    cin >> patId;

    //checks for patron
    for(auto iter = patronVec.begin(); iter != patronVec.end(); iter++)
    {
        if(patId == (*iter)->getId())
        {
            patronVec.erase(iter);
            patronCount--;
            cout << "Patron deleted." << endl;
            return;
        }
    }
    cout << "Patron could not be found." << endl;
}

//Edit a paticular patron
void Patrons::editPatron()
{
    int patId;
    cout << "Enter patron's ID: ";
    cin >> patId;

    Patron *tempPat = nullptr;

    //searches for patron
    for(auto iter = patronVec.begin(); iter != patronVec.end(); iter++)
    {
        if(patId == (*iter)->getId())
        {
            tempPat = *iter;
            break;
        }
    }

    if(tempPat == nullptr)
    {
        cout << "Patron could not be found." << endl;
        return;
    }

    char tempOption = '0';
    cout << "What would you like to edit?" << endl;
    cout << "1 - Patron Name" << endl;
    cout << "2 - Patron Balance" << endl;
    cout << "3 - Number of Items Checked-Out" << endl;

    //while input is valid
    while(tempOption != '1' || tempOption != '2' || tempOption != '3')
    {
        cout << "Choose an option: ";
        cin >> tempOption;
        if(tempOption == '1' || tempOption == '2' || tempOption == '3')
            break;
        else
            cout << "Invalid input." << endl;
    }

    string tempName;
    float tempBal;
    int tempNumItems;
    switch(tempOption)	//edits patron based on user input
    {
        case '1':
        {
            cin.ignore();
            cout << "Enter patron's new name: ";
            getline(cin, tempName);
            (*tempPat).setName(tempName);
            cout << "Patron name changed." << endl;
            break;
        }
        case '2':
        {
            cout << "Enter patron's new balance: ";
            cin >> tempBal;
            (*tempPat).setBalance(tempBal);
            cout << "Patron balance changed." << endl;
            break;
        }
        case '3':
        {
            cout << "Enter patron's number of items checked out: ";
            cin >> tempNumItems;
            (*tempPat).setNumberOfItems(tempNumItems);
            cout << "Patron number of items changed." << endl;
            break;
        }
        default :
            break;
    }
}

//Searches for patron in vector
void Patrons::searchPatron(bool searchCheck) //boolean determines whether searchPatron or printPatronInfo
{
    int patId;
    cout << "Enter patron's ID: ";
    cin >> patId;

    Patron *tempPat = nullptr;

    //checks if patron exists
    for(auto iter = patronVec.begin(); iter != patronVec.end(); iter++)
    {
        if(patId == (*iter)->getId())
        {
            tempPat = *iter;
            break;
        }
    }
    //if patron does not exist
    if(tempPat == nullptr)
        cout << "Patron could not be found." << endl;
    else if(searchCheck == false)
        printPatronInfo(tempPat);
    else
        cout << "Patron " << (*tempPat).getId() << " (" << (*tempPat).getName() << ") exists in our database." << endl;
}

//Prints info of individual patron
void Patrons::printPatronInfo(Patron *patron)
{
    cout << "Name: " << (*patron).getName() << endl;
    cout << "ID: " << (*patron).getId() << endl;
    cout << "Balance: $" << (*patron).getBalance() << endl;
    cout << "Number of Items Checked-Out: " << (*patron).getNumberOfItems() << endl;
}

//Pays fines of balance, sets it equal to 0
void Patrons::payFines()
{
    int patId;
    cout << "Enter patron's ID: ";
    cin >> patId;

    Patron *tempPat = nullptr;

    //checks for patron
    for(auto iter = patronVec.begin(); iter != patronVec.end(); iter++)
    {
        if(patId == (*iter)->getId())
        {
            tempPat = *iter;
            break;
        }
    }
    //if patron does not exist
    if(tempPat == nullptr)
    {
        cout << "Patron could not be found." << endl;
        return;
    }
    else if((*tempPat).getBalance() == 0)	//checks if patron actually owes money
    {
        cout << "Patron does not owe any money." << endl;
        return;
    }
    else	//set patron balance to zero
    {
        (*tempPat).setBalance(0);
        cout << "Patron's balance is now $" << fixed << setprecision(2) << (*tempPat).getBalance() << endl;
    }
}
