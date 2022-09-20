#include <iostream>
#include "Loan.h"
using namespace std;

//Default Constructor
Loan::Loan()
{
    loanId = 0;
    itemId = 0;
    patronId = 0;
    dueDate = nullptr;
    currentStatus = "none";
    recheck = false;
}

//Overloaded Constructor
Loan::Loan(int loanId, int itemId, int patronId, tm *dueDate, string currentStatus, bool recheck)
{
    this->loanId = loanId;
    this->itemId = itemId;
    this->patronId = patronId;
    this->dueDate = dueDate;
    this->currentStatus = currentStatus;
    this->recheck = recheck;
}

//Get Functions
int Loan::getLoanId()
{
    return loanId;
}

int Loan::getItemId()
{
    return itemId;
}

int Loan::getPatronId()
{
    return patronId;
}

tm* Loan::getDueDate()
{
    return dueDate;
}

string Loan::getCurrentStatus()
{
    return currentStatus;
}

bool Loan::wasRechecked()
{
    return recheck;
}

//Set Functions
void Loan::setLoanId(int loanId)
{
    this->loanId = loanId;
}

void Loan::setItemId(int itemId)
{
    this->itemId = itemId;
}

void Loan::setPatronId(int patronId)
{
    this->patronId = patronId;
}

void Loan::setDueDate(tm *dueDate)
{
    this->dueDate = dueDate;
}

void Loan::setCurrentStatus(string currentStatus)
{
    this->currentStatus = currentStatus;
}

/*void Loan::recheckLoan()
{
	if(!recheck)
		recheck = true;
	else
		cout << "Loan cannot be rechecked." << endl;
}*/

void Loan::setRecheck(bool recheck)
{
    this->recheck = recheck;
}