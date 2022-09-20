/* Author:	Bruno Philippon
*  Instructor:	David Keathly
*  Date:	3/19/20
*  Description:	This program allows a user to manipulate the system admin of a Library with class such as Patrons, Library Items,
*		and Loans. They can add or delete these objects, and they can maintain the data of the objects through
*		each run of the program. There are numerous way to manipulate each object in each of the classes.
*/

#include <iostream>
#include <fstream>
#include "Loans.h"
using namespace std;

//prints each menu and sub-menu
void printMainMenu();
void printPatronMenu();
void printItemMenu();
void printLoanMenu();

//executes every method chose by the user
void accessPatronMenu(Patrons &patronList);
void accessItemMenu(LibraryItems &itemList);
void accessLoanMenu(Patrons &patronList, LibraryItems &itemList, Loans &loanList);

int main()
{
    Patrons patronList;
    LibraryItems itemList;
    Loans loanList;

    patronList.loadPatronData();
    itemList.loadItemData();
    loanList.loadLoanData();
    cout << "Loading complete." << endl;

    cout << endl << "Welcome." << endl << endl;
    char menuChar = '0';

    while(menuChar != 'q')	//while the user has not chosen to quit the menu
    {
        printMainMenu();
        cout << "Option: ";
        cin >> menuChar;

        switch(menuChar)
        {
            case '1':
            {
                cout << endl;
                printPatronMenu();
                accessPatronMenu(patronList);
                break;
            }
            case '2':
            {
                cout << endl;
                printItemMenu();
                accessItemMenu(itemList);
                break;
            }
            case '3':
            {
                cout << endl;
                printLoanMenu();
                accessLoanMenu(patronList, itemList, loanList);
                break;
            }
            case 'q':
                break;
            default:
            {
                cout << "Input invalid. Please try again." << endl << endl;
                break;
            }
        }
        cout << endl;
    }

    cout << "Shutting down." << endl << endl;

    patronList.storePatronData();
    itemList.storeItemData();
    loanList.storeLoanData();
    cout << "Storing complete." << endl;

    patronList.cleanupPatrons();
    itemList.cleanupItems();
    loanList.cleanupLoans();
    cout << "Cleanup complete." << endl;

    return 0;
}

//Prints main menu
void printMainMenu()
{
    cout << "-----MAIN MENU-----" << endl;
    cout << "What would you like to access?" << endl;
    cout << "1 - Patrons" << endl;
    cout << "2 - Items" << endl;
    cout << "3 - Loans" << endl;
    cout << "q - Save and quit" << endl << endl;
}

//Prints patron menu
void printPatronMenu()
{
    cout << "-----PATRON MENU-----" << endl;
    cout << "Choose an option:" << endl;
    cout << "1 - Add Patron" << endl;
    cout << "2 - Edit Patron" << endl;
    cout << "3 - Delete Patron" << endl;
    cout << "4 - Search Patron" << endl;
    cout << "5 - Print All Patrons" << endl;
    cout << "6 - Print Patron Info" << endl;
    cout << "7 - Pay Fines" << endl;
    cout << "b - Back" << endl << endl;
}

//Prints item menu
void printItemMenu()
{
    cout << "-----ITEM MENU-----" << endl;
    cout << "Choose an option:" << endl;
    cout << "1 - Add Item" << endl;
    cout << "2 - Edit Item" << endl;
    cout << "3 - Delete Item" << endl;
    cout << "4 - Search Item" << endl;
    cout << "5 - Print All Items" << endl;
    cout << "6 - Print Item Info" << endl;
    cout << "b - Back" << endl << endl;
}

//Prints loan menu
void printLoanMenu()
{
    cout << "-----LOAN MENU-----" << endl;
    cout << "Choose an option:" << endl;
    cout << "0 - Check Out Item" << endl;
    cout << "1 - Check In Item" << endl;
    cout << "2 - List All Overdue Items" << endl;
    cout << "3 - List All Items for Patron" << endl;
    cout << "4 - Update Loan Status" << endl;
    cout << "5 - Recheck Item" << endl;
    cout << "6 - Edit Loan" << endl;
    cout << "7 - Report Lost" << endl;
    cout << "8 - Print All Overdue Items for Patron" << endl;
    cout << "9 - Print All Loans" << endl;
    cout << "b - Back" << endl << endl;
}

//Executes functions from patron menu
void accessPatronMenu(Patrons &patronList)
{
    char menuChar;
    cout << "Option: ";
    cin >> menuChar;
    cin.ignore();

    switch(menuChar)
    {
        case '1':
            patronList.addPatron();
            cout << endl;
            break;
        case '2':
            patronList.editPatron();
            cout << endl;
            break;
        case '3':
            patronList.deletePatron();
            cout << endl;
            break;
        case '4':
            patronList.searchPatron(true);
            cout << endl;
            break;
        case '5':
            patronList.printAllPatrons();
            break;
        case '6':
            patronList.searchPatron(false);
            cout << endl;
            break;
        case '7':
            patronList.payFines();
            cout << endl;
            break;
        case 'b':
            break;
        default:
            cout << "Invalid Input." << endl;
            break;
    }
}

//Executes functions from item menu
void accessItemMenu(LibraryItems &itemList)
{
    char menuChar;
    cout << "Option: ";
    cin >> menuChar;
    cin.ignore();

    switch(menuChar)
    {
        case '1':
            itemList.addItem();
            cout << endl;
            break;
        case '2':
            itemList.editItem();
            cout << endl;
            break;
        case '3':
            itemList.deleteItem();
            cout << endl;
            break;
        case '4':
            itemList.searchItem(true);
            cout << endl;
            break;
        case '5':
            itemList.printAllItems();
            break;
        case '6':
            itemList.searchItem(false);
            break;
        case 'b':
            break;
        default:
            cout << "Invalid Input." << endl;
            break;
    }
}

//Executes functions from loan menu
void accessLoanMenu(Patrons &patronList, LibraryItems &itemList, Loans &loanList)
{
    char menuChar;
    cout << "Option: ";
    cin >> menuChar;

    switch(menuChar)
    {
        case '0':
            loanList.checkOutBook(patronList.getPatronVector(), itemList.getItemVector());
            cout << endl;
            break;
        case '1':
            loanList.checkInBook(patronList.getPatronVector(), itemList.getItemVector());
            cout << endl;
            break;
        case '2':
            loanList.listAllOverdue();
            break;
        case '3':
            loanList.listAllItems(patronList.getPatronVector(), itemList.getItemVector());
            break;
        case '4':
            loanList.updateStatus(patronList.getPatronVector(), itemList.getItemVector());
            cout << endl;
            break;
        case '5':
            loanList.recheckLoan(itemList.getItemVector());
            cout << endl;
            break;
        case '6':
            loanList.editLoan();
            cout << endl;
            break;
        case '7':
            loanList.reportLost(patronList.getPatronVector(), itemList.getItemVector());
            cout << endl;
            break;
        case '8':
            loanList.printAllOverdueForPatron();
            break;
        case '9':
            loanList.printAllLoans();
            break;
        case 'b':
            break;
        default:
            cout << "Invalid input." << endl;
            break;
    }
}
