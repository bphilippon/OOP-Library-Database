#include "Loans.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <iterator>
using namespace std;

//Loads loan data
void Loans::loadLoanData()
{
    ifstream fin;
    fin.open("loans.dat");

    fin >> currentLoanId;

    int tempLoanId;
    int tempItemId;
    int tempPatronId;

    int tempTimeInt;
    string tempTimeString;
    char dummy;

    string tempStatus;
    bool tempRecheck;
    while(fin >> tempLoanId)	//scans from loan data file
    {
        tm *tempDueDate;
        tempDueDate = new tm();

        fin >> tempItemId;
        fin >> tempPatronId;

        fin >> tempTimeString;
        if(tempTimeString == "Sun")		//Determines what day of the week
            tempDueDate->tm_wday = 0;
        else if(tempTimeString == "Mon")
            tempDueDate->tm_wday = 1;
        else if(tempTimeString == "Tue")
            tempDueDate->tm_wday = 2;
        else if(tempTimeString == "Wed")
            tempDueDate->tm_wday = 3;
        else if(tempTimeString == "Thu")
            tempDueDate->tm_wday = 4;
        else if(tempTimeString == "Fri")
            tempDueDate->tm_wday = 5;
        else
            tempDueDate->tm_wday = 6;

        fin >> tempTimeString;
        if(tempTimeString == "Jan")		//Determines which month
            tempDueDate->tm_mon = 0;
        else if(tempTimeString == "Feb")
            tempDueDate->tm_mon = 1;
        else if(tempTimeString == "Mar")
            tempDueDate->tm_mon = 2;
        else if(tempTimeString == "Apr")
            tempDueDate->tm_mon = 3;
        else if(tempTimeString == "May")
            tempDueDate->tm_mon = 4;
        else if(tempTimeString == "Jun")
            tempDueDate->tm_mon = 5;
        else if(tempTimeString == "Jul")
            tempDueDate->tm_mon = 6;
        else if(tempTimeString == "Aug")
            tempDueDate->tm_mon = 7;
        else if(tempTimeString == "Sep")
            tempDueDate->tm_mon = 8;
        else if(tempTimeString == "Oct")
            tempDueDate->tm_mon = 9;
        else if(tempTimeString == "Nov")
            tempDueDate->tm_mon = 10;
        else
            tempDueDate->tm_mon = 11;

        fin >> tempTimeInt;
        tempDueDate->tm_mday = tempTimeInt;

        fin >> tempTimeInt;
        tempDueDate->tm_hour = tempTimeInt;
        fin >> dummy;
        fin >> tempTimeInt;
        tempDueDate->tm_min = tempTimeInt;
        fin >> dummy;
        fin >> tempTimeInt;
        tempDueDate->tm_sec = tempTimeInt;

        fin >> tempTimeInt;
        tempDueDate->tm_year = tempTimeInt - 1900;	//Makes year 2021

        fin >> tempStatus;
        fin >> tempRecheck;

        //Allocates memory for a new loan item
        loanVec.push_back(new Loan(tempLoanId, tempItemId, tempPatronId, tempDueDate, tempStatus, tempRecheck));
        loanCount++;
    }
    fin.close();
}

//Stores loan data
void Loans::storeLoanData()
{
    ofstream fout;
    fout.open("loans.dat");
    fout << currentLoanId << endl;

    for(auto iter = loanVec.begin(); iter != loanVec.end(); iter++)
    {
        fout << (*iter)->getLoanId() << " " << (*iter)->getItemId() << " " << (*iter)->getPatronId() << endl;
        fout << asctime((*iter)->getDueDate());
        fout << (*iter)->getCurrentStatus() << " " << (*iter)->wasRechecked() << endl;
    }
    fout.close();
}

//Prints all loans
void Loans::printAllLoans()
{
    int loansIndex = 1;

    for(auto iter = loanVec.begin(); iter != loanVec.end(); iter++)
    {
        cout << "[Loan " << loansIndex << "]" << endl;
        cout << "Loan ID: " << (*iter)->getLoanId() << endl;
        cout << "Item ID: " << (*iter)->getItemId() << endl;
        cout << "Patron ID: " << (*iter)->getPatronId() << endl;
        cout << "Due Date: " << asctime((*iter)->getDueDate());
        cout << "Current Status: " << (*iter)->getCurrentStatus() << endl;
        cout << "Was rechecked: ";
        if((*iter)->wasRechecked() == 1)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
        cout << endl;

        loansIndex++;
    }
}

//Deallocates all memory for each loan
void Loans::cleanupLoans()
{
    for(auto iter = loanVec.begin(); iter != loanVec.end(); iter++)
    {
        delete *iter;
    }
    loanVec.clear();
}

//Returns number of loans
int Loans::getLoanCount()
{
    return loanVec.size();
}

//Adds a loan
void Loans::checkOutBook(vector<Patron*> patronVec, vector<LibraryItem*> itemVec)
{
    int patId;
    int itemId;
    Loan *tempLoan;
    tempLoan = new Loan();

    cout << "Enter patron's ID: ";
    cin >> patId;

    //checks for patron
    for(auto patronIter = patronVec.begin(); patronIter != patronVec.end(); patronIter++)
    {
        if((*patronIter)->getId() == patId)
        {
            //checks if number of books exceeds 6 or more
            if((*patronIter)->getNumberOfItems() >= 6)
            {
                cout << "Patron already has 6 items checked-out. Loan cannot be provided." << endl;
                return;
            }
            //checks if patron owns any overdue books
            for(auto loanIter = loanVec.begin(); loanIter != loanVec.end(); loanIter++)
            {
                if((*loanIter)->getPatronId() == (*patronIter)->getId())
                {
                    if((*loanIter)->getCurrentStatus() == "Overdue")
                    {
                        cout << "Patron has item(s) past due. Loan cannot be provided." << endl;
                        return;
                    }
                }
            }
            tempLoan->setPatronId(patId);
            (*patronIter)->setNumberOfItems((*patronIter)->getNumberOfItems() + 1);
            break;
        }
    }
    //if patron does not exist
    if(tempLoan->getPatronId() == 0)
    {
        cout << "Patron could not be found." << endl;
        return;
    }

    cout << "Enter Library ID of the item being checked-out: ";
    cin >> itemId;
    //checks for book
    LibraryItem *tempItem;
    for(auto itemIter = itemVec.begin(); itemIter != itemVec.end(); itemIter++)
    {
        if((*itemIter)->getId() == itemId)
        {
            //makes sure book is available
            if((*itemIter)->getCurrentStatus() == "In")
            {
                tempLoan->setItemId(itemId);
                (*itemIter)->setCurrentStatus("Out");
                tempItem = *itemIter;
                break;
            }
            else
            {
                cout << "Item is currently checked-out." << endl;
                return;
            }
        }
    }
    //if book does not exist
    if(tempLoan->getItemId() == 0)
    {
        cout << "Item could not be found." << endl;
        return;
    }

    tempLoan->setLoanId(currentLoanId);
    currentLoanId++;

    time_t currentTime;
    time(&currentTime);
    currentTime += (86400 * (*tempItem).getLoanPeriod());	//sets due date 10 or 2 days from the current time, depending on item type


    tempLoan->setDueDate(localtime(&currentTime));
    tempLoan->setCurrentStatus("Normal");
    loanVec.push_back(tempLoan);
    loanCount++;
    cout << "Item has been checked-out. New loan successfully created." << endl;
}

//Deletes a loan object
void Loans::checkInBook(vector<Patron*> patronVec, vector<LibraryItem*> itemVec)
{
    int loanId;
    cout << "Enter loan ID: ";
    cin >> loanId;

    time_t currentTime;
    time(&currentTime);
    Loan *tempLoan;

    //checks for loan
    for(auto iter = loanVec.begin(); iter != loanVec.end(); iter++)
    {
        if((*iter)->getLoanId() == loanId)
        {
            tempLoan = *iter;
            updateStatus(tempLoan, patronVec, itemVec);	//checks if loan is overdue
            for(auto patronIter = patronVec.begin(); patronIter != patronVec.end(); patronIter++)
            {
                //subtracts number of books from patron
                if((*patronIter)->getId() == (*iter)->getPatronId())
                {
                    (*patronIter)->setNumberOfItems((*patronIter)->getNumberOfItems() - 1);
                    break;
                }
            }
            for(auto itemIter = itemVec.begin(); itemIter != itemVec.end(); itemIter++)
            {
                //set status of book back to being available
                if((*itemIter)->getId() == (*iter)->getItemId())
                {
                    (*itemIter)->setCurrentStatus("In");
                    break;
                }
            }
            loanVec.erase(iter);
            loanCount--;
            cout << "Item has been checked-in. Loan was successfully returned." << endl;
            return;
        }
    }
    cout << "Loan could not be found." << endl;
}

//Updates the status of a loan, checks if overdue
void Loans::updateStatus(Loan *loan, vector<Patron*> patronVec, vector<LibraryItem*> itemVec)
{
    time_t currentTime;
    time(&currentTime);

    //gets the difference between the due date and current time, in days
    int days = (currentTime - mktime(loan->getDueDate())) / 86400;
    if(days > 0)	//if negative, book is on time
    {
        for(auto patronIter = patronVec.begin(); patronIter != patronVec.end(); patronIter++)
        {
            //fee is added to the user balance compounded by time overdue
            if(loan->getPatronId() == (*patronIter)->getId())
            {
                (*patronIter)->setBalance((*patronIter)->getBalance() + (days * 0.25));
                break;
            }
        }
        loan->setCurrentStatus("Overdue");
        cout << "Your loan is " << days << " days overdue. Your balance has been updated." << endl;
    }
    else
    {
        cout << "Your loan is on schedule." << endl;
    }
}

//Update status function overloaded
void Loans::updateStatus(vector<Patron*> patronVec, vector<LibraryItem*> itemVec)
{
    time_t currentTime;
    time(&currentTime);

    int loanId;
    cout << "Enter loan ID: ";
    cin >> loanId;
    Loan *tempLoan = nullptr;

    for(auto iter = loanVec.begin(); iter != loanVec.end(); iter++)
    {
        if((*iter)->getLoanId() == loanId)
        {
            tempLoan = *iter;
            break;
        }
    }
    if(tempLoan == nullptr)
    {
        cout << "Loan could not be found." << endl;
        return;
    }

    int days = (currentTime - mktime((*tempLoan).getDueDate())) / 86400;
    if(days > 0)
    {
        for(auto patronIter = patronVec.begin(); patronIter != patronVec.end(); patronIter++)
        {
            if((*tempLoan).getPatronId() == (*patronIter)->getId())
            {
                (*patronIter)->setBalance((*patronIter)->getBalance() + (days * 0.25));
                break;
            }
        }
        (*tempLoan).setCurrentStatus("Overdue");
        cout << "Your loan is " << days << " days overdue. Your balance has been updated." << endl;
    }
    else
    {
        cout << "Your loan is on schedule." << endl;
    }
}

//Edits data members of a loan object
void Loans::editLoan()
{
    int loanId;
    cout << "Enter loan ID: ";
    cin >> loanId;

    Loan *tempLoan = nullptr;
    for(auto iter = loanVec.begin(); iter != loanVec.end(); iter++)	//checks for loan
    {
        if((*iter)->getLoanId() == loanId)
        {
            tempLoan = *iter;
            break;
        }
    }
    //if loan does not exist
    if(tempLoan == nullptr)
    {
        cout << "Loan could not be found." << endl;
        return;
    }

    char tempOption = '0';
    cout << "What would you like to edit?" << endl;
    cout << "1 - Due Date" << endl;
    cout << "2 - Current Status" << endl;
    cout << "3 - Recheck Status" << endl;

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

    switch(tempOption)	//edits loan based on user input
    {
        case '1':
        {
            int tempDays;
            cout << "How long would you like to extend the due date (in days)? ";
            cin >> tempDays;
            time_t tempTime = mktime((*tempLoan).getDueDate());
            tempTime += (tempDays * 86400);
            (*tempLoan).setDueDate(localtime(&tempTime));
            cout << "Due date extended." << endl;
            break;
        }
        case '2':
        {
            string tempStatus;
            cout << "Enter new loan status (Overdue/Normal): ";
            cin >> tempStatus;
            (*tempLoan).setCurrentStatus(tempStatus);
            cout << "Status updated." << endl;
            break;
        }
        case '3':
        {
            char recheck;
            cout << "Would you like the loan to be rechecked (yes/no)? ";
            cin >> recheck;
            tolower(recheck);
            if(recheck == 'y')
            {
                (*tempLoan).setRecheck(true);
                cout << "Loan was rechecked." << endl;
            }
            else
            {
                (*tempLoan).setRecheck(false);
                cout << "Loan was not rechecked." << endl;
            }
            break;
        }
        default:
            break;
    }
}

//Prints all overdue loans
void Loans::listAllOverdue()
{
    bool overdueCheck = false;
    int loanCount = 1;
    for(auto iter = loanVec.begin(); iter != loanVec.end(); iter++)
    {
        if((*iter)->getCurrentStatus() == "Overdue")	//if loan is overdue
        {
            cout << "[Loan " << loanCount << "]" << endl;
            cout << "Loan ID: " << (*iter)->getLoanId() << endl;
            cout << "Item ID: " << (*iter)->getItemId() << endl;
            cout << "Patron ID: " << (*iter)->getPatronId() << endl;
            cout << "Due Date: " << asctime((*iter)->getDueDate());
            cout << "Current Status: " << (*iter)->getCurrentStatus() << endl;
            cout << "Was rechecked: ";
            if((*iter)->wasRechecked() == 1)
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
            cout << endl;
            if(overdueCheck == false)	//makes sure at least one loan is overdue
                overdueCheck = true;
        }
        loanCount++;
    }
    if(!overdueCheck)
        cout << "No loans are overdue." << endl;
}

//Prints all books on loan from a particular patron
void Loans::listAllItems(vector<Patron*> patronVec, vector<LibraryItem*> itemVec)
{
    int patronId;
    cout << "Enter patron's ID: ";
    cin >> patronId;

    Patron *tempPatron = nullptr;
    for(auto iter = patronVec.begin(); iter != patronVec.end(); iter++)	//checks for patron
    {
        if(patronId == (*iter)->getId())
        {
            tempPatron = *iter;
            break;
        }
    }
    //if patron does not exist
    if(tempPatron == nullptr)
    {
        cout << "Patron could not be found." << endl;
        return;
    }

    cout << "[Patron - " << (*tempPatron).getName()<< "]" << endl;
    //checks if patron has any loans
    if((*tempPatron).getNumberOfItems() == 0)
    {
        cout << "Patron currently has no items on loan." << endl << endl;
        return;
    }

    LibraryItem *tempItem = nullptr;
    for(auto iter = loanVec.begin(); iter != loanVec.end(); iter++)	//displays each book a patron has checked-out
    {
        if((*tempPatron).getId() == (*iter)->getPatronId())
        {
            for(auto itemIter = itemVec.begin(); itemIter != itemVec.end(); itemIter++)
            {
                if((*itemIter)->getId() == (*iter)->getItemId())
                {
                    tempItem = *itemIter;
                    //TEST THIS
                    tempItem->print();  //displays item info, POSSIBLY dynamic cast
                    cout << endl;
                    break;
                }
            }
        }
    }
}

//Rechecks a loan
void Loans::recheckLoan(vector<LibraryItem*> itemVec)
{
    int loanId;
    cout << "Enter loan ID: ";
    cin >> loanId;

    Loan *tempLoan = nullptr;
    time_t tempTime;
    for(auto iter = loanVec.begin(); iter != loanVec.end(); iter++)	//checks for loan
    {
        if((*iter)->getLoanId() == loanId)
        {
            tempLoan = *iter;
            if((*tempLoan).wasRechecked() == false) //checks if loan was already rechecked once
            {
                (*tempLoan).setRecheck(true);
                tempTime = time(0);

                LibraryItem *tempItem = nullptr;
                for(auto itemIter = itemVec.begin(); itemIter != itemVec.end(); itemIter++)
                {
                    if((*itemIter)->getId() == (*tempLoan).getItemId())
                    {
                        tempItem = *itemIter;
                        break;
                    }
                }

                tempTime += (86400 * (*tempItem).getLoanPeriod());	//adds 10 days to the due date of the CURRENT time
                (*tempLoan).setDueDate(localtime(&tempTime));
                (*tempLoan).setCurrentStatus("Normal");
                (*tempLoan).setRecheck(true);
                cout << "Loan was rechecked." << endl;
            }
            else
                cout << "Loan cannot be rechecked." << endl;
            return;
        }
    }
    cout << "Loan could not be found." << endl;
}

//Reports a book as lost
void Loans::reportLost(vector<Patron*> patronVec, vector<LibraryItem*> itemVec)
{
    bool check = false; 	//check if loan exists
    int loanId = 0;
    cout << "Enter loan ID: ";
    cin >> loanId;

    //checks for loan
    for(auto iter = loanVec.begin(); iter != loanVec.end(); iter++)
    {
        if((*iter)->getLoanId() == loanId)
        {
            check = true;
            //checks for book of loan
            for(auto itemIter = itemVec.begin(); itemIter != itemVec.end(); itemIter++)
            {
                if((*iter)->getItemId() == (*itemIter)->getId())
                {
                    (*itemIter)->setCurrentStatus("Lost");	//updates book status
                    //checks for patron of loan
                    for(auto patIter = patronVec.begin(); patIter != patronVec.end(); patIter++)
                    {
                        if((*patIter)->getId() == (*iter)->getPatronId()) //charges patron balance
                        {
                            (*patIter)->setBalance((*patIter)->getBalance() + (*itemIter)->getCost());
                            break;
                        }
                    }
                    break;
                }
            }
            break;
        }
    }
    //if loan does not exist
    if(!check)
        cout << "Loan could not be found." << endl;
    else
        cout << "Loan reported lost." << endl;
}

//Prints all overdue books for a patron
void Loans::printAllOverdueForPatron()
{
    bool overdueCheck = false;
    int loanIndex = 1;
    int patId = 0;
    cout << "Enter patron's ID: ";
    cin >> patId;

    //checks for overdue loan, printing each one
    for(auto iter = loanVec.begin(); iter != loanVec.end(); iter++)
    {
        if((*iter)->getPatronId() == patId && (*iter)->getCurrentStatus() == "Overdue")
        {
            overdueCheck = true;
            cout << "[Loan " << loanIndex << "]" << endl;
            cout << "Loan ID: " << (*iter)->getLoanId() << endl;
            cout << "Item ID: " << (*iter)->getItemId() << endl;
            cout << "Patron ID: " << (*iter)->getPatronId() << endl;
            cout << "Due Date: " << asctime((*iter)->getDueDate());
            cout << "Current Status: " << (*iter)->getCurrentStatus() << endl;
            cout << "Was rechecked: ";
            if((*iter)->wasRechecked() == 1)
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
            cout << endl;
        }
        loanIndex++;
    }
    //if patrons has no overdue loans or does not exist
    if(!overdueCheck)
    {
        cout << "Patron has no overdue loans or does not exist." << endl;
        return;
    }
}
