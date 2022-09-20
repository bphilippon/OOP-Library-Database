#include "LibraryItems.h"
#include "Book.h"
#include "CD.h"
#include "DVD.h"
#include <iostream>
#include <fstream>
#include <iterator>
using namespace std;

//Loads item data
void LibraryItems::loadItemData()
{
    ifstream fin;
    fin.open("items.dat");

    fin >> currentItemId;

    int itemId;		//item elements
    float itemCost;
    string itemStatus;
    int loanPeriod;

    string title;		//book, cd, dvd

    string author;		//book elements
    int isbn;
    string category;//shared with cd

    string artist;		//cd elements
    int numTracks;
    string releaseDate;//shared with dvd
    string genre;

    int runtime;		//dvd elements
    string studio;

    int itemType;	//1 = Book, 2 = CD, 3 = DVD

    while(fin >> itemId)	//scans from book data file
    {
        fin >> itemCost;
        fin >> itemStatus;
        fin >> loanPeriod;
        fin >> itemType;
        fin.ignore();

        if(itemType == 1)
        {
            getline(fin, title);
            getline(fin, author);
            fin >> isbn;
            fin >> category;
            itemVec.push_back(new Book(itemId, itemCost, itemStatus, loanPeriod, author, title, isbn, category));
        }
        if(itemType == 2)
        {
            getline(fin, artist);
            getline(fin, title);
            fin >> numTracks;
            fin.ignore();
            getline(fin, releaseDate);
            getline(fin, genre);
            itemVec.push_back(new CD(itemId, itemCost, itemStatus, loanPeriod, artist, title, numTracks, releaseDate, genre));
        }
        if(itemType == 3)
        {
            getline(fin, title);
            fin >> category;
            fin >> runtime;
            fin.ignore();
            getline(fin, studio);
            getline(fin, releaseDate);
            itemVec.push_back(new DVD(itemId, itemCost, itemStatus, loanPeriod, title, category, runtime, studio, releaseDate));
        }
        itemCount++;
    }
    fin.close();
}

//Stores item data
void LibraryItems::storeItemData()
{
    ofstream fout;
    fout.open("items.dat");

    fout << currentItemId << endl;

    for(auto iter = itemVec.begin(); iter != itemVec.end(); iter++) //stores book data exactly how loaded
    {
        if(typeid(**iter) == typeid(Book))
        {
            Book *tempItem = dynamic_cast<Book*>(*iter);
            tempItem->fileprint(fout);
        }
        if(typeid(**iter) == typeid(CD))
        {
            CD *tempItem = dynamic_cast<CD*>(*iter);
            tempItem->fileprint(fout);
        }
        if(typeid(**iter) == typeid(DVD))
        {
            DVD *tempItem = dynamic_cast<DVD*>(*iter);
            tempItem->fileprint(fout);
        }
    }
    fout.close();
}

//Prints all items
void LibraryItems::printAllItems()
{
    int itemIndex = 1;

    for(auto iter = itemVec.begin(); iter != itemVec.end(); iter++)
    {
        if(typeid(**iter) == typeid(Book))
        {
            Book *temp = dynamic_cast<Book*>(*iter);
            cout << "[Item " << itemIndex << "]" << endl;
            cout << "Type - Book" << endl;
            temp->print();
        }
        if(typeid(**iter) == typeid(CD))
        {
            CD *temp = dynamic_cast<CD*>(*iter);
            cout << "[Item " << itemIndex << "]" << endl;
            cout << "Type - CD" << endl;
            temp->print();
        }
        if(typeid(**iter) == typeid(DVD))
        {
            DVD *temp = dynamic_cast<DVD*>(*iter);
            cout << "[Item " << itemIndex << "]" << endl;
            cout << "Type - DVD" << endl;
            temp->print();
        }
        itemIndex++;
    }
}

//Deallocates memory for all items
void LibraryItems::cleanupItems()
{
    for(auto iter = itemVec.begin(); iter != itemVec.end(); iter++)
    {
        delete *iter;
    }
    itemVec.clear();
}

//Returns the number of items being stored
int LibraryItems::getItemCount()
{
    return itemCount;
}

//Returns the item vector
vector<LibraryItem*> LibraryItems::getItemVector()
{
    return itemVec;
}

//Adds a new item to the vector
void LibraryItems::addItem()
{
    int itemNumType;
    cout << "What type of item would you like to add (1 = Book, 2 = CD, 3 = DVD)? ";
    cin >> itemNumType;

    float cost;
    cout << "Enter item cost: ";
    cin >> cost;
    cin.ignore();

    if(itemNumType == 1)
    {
        string author;
        string title;
        int isbn;
        string category;

        cout << "Enter book's author: ";
        getline(cin, author);
        cout << "Enter book's title: ";
        getline(cin, title);
        cout << "Enter ISBN: ";
        cin >> isbn;
        cout << "Enter book's category: ";
        cin >> category;
        cin.ignore();

        //allocates memory for new book object
        itemVec.push_back(new Book(currentItemId, cost, "In", 10, author, title, isbn, category));
    }
    else if(itemNumType == 2)
    {
        string artist;
        string title;
        int numTracks;
        string releaseDate;
        string genre;

        cout << "Enter CD's artist: ";
        getline(cin, artist);
        cout << "Enter CD's Title: ";
        getline(cin, title);
        cout << "Enter CD's number of tracks: ";
        cin >> numTracks;
        cin.ignore();
        cout << "Enter CD's release date(mm/dd/yyyy): ";
        getline(cin, releaseDate);
        cout << "Enter CD's genre: ";
        getline(cin, genre);

        itemVec.push_back(new CD(currentItemId, cost, "In", 2, artist, title, numTracks, releaseDate, genre));
    }
    else if(itemNumType == 3)
    {
        string title;
        string category;
        int runTime;
        string studio;
        string releaseDate;

        cout << "Enter DVD's title: ";
        getline(cin, title);
        cout << "Enter DVD's category: ";
        cin >> category;
        cout << "Enter DVD's runtime(in seconds): ";
        cin >> runTime;
        cin.ignore();
        cout << "Enter DVD's studio: ";
        getline(cin, studio);
        cout << "Enter DVD's release date(mm/dd/yyyy): ";
        getline(cin, releaseDate);

        itemVec.push_back(new DVD(currentItemId, cost, "In", 2, title, category, runTime, studio, releaseDate));
    }
    else
    {
        cout << "Invalid input." << endl;
        return;
    }

    currentItemId++;
    itemCount++;
    cout << "Item added." << endl;
}

//Deletes item from vector
void LibraryItems::deleteItem()
{
    int tempId;
    cout << "Enter item's library ID: ";
    cin >> tempId;

    //Checks for book
    for(auto iter = itemVec.begin(); iter != itemVec.end(); iter++)
    {
        if((*iter)->getId() == tempId)
        {
            itemVec.erase(iter);
            itemCount--;
            cout << "Item deleted." << endl;
            return;
        }
    }
    cout << "Item could not be found." << endl;
}

//Edits item object
void LibraryItems::editItem()
{
    int tempId;
    cout << "Enter item's library ID: ";
    cin >> tempId;

    LibraryItem *tempItem = nullptr;

    //Checks for book
    for(auto iter = itemVec.begin(); iter != itemVec.end(); iter++)
    {
        if((*iter)->getId() == tempId)
        {
            tempItem = *iter;
            break;
        }
    }
    //if book does not exist
    if(tempItem == nullptr)
    {
        cout << "Item could not be found." << endl;
        return;
    }

    char tempOption = '0';
    cout << "What would you like to edit?" << endl;
    if(typeid(*tempItem) == typeid(Book))
    {
        //while input is valid
        cout << "1 - Book Author" << endl;
        cout << "2 - Book Title" << endl;
        cout << "3 - Book ISBN" << endl;
        cout << "4 - Book Category" << endl;
        cout << "5 - Book Cost" << endl;
        while(tempOption != '1' || tempOption != '2' || tempOption != '3' || tempOption != '4' || tempOption != '5')
        {
            cout << "Choose an option: ";
            cin >> tempOption;
            if(tempOption == '1' || tempOption == '2' || tempOption == '3' || tempOption == '4' || tempOption == '5')
                break;
            else
                cout << "Invalid input." << endl;
        }
    }
    if(typeid(*tempItem) == typeid(CD))
    {
        cout << "1 - CD Artist" << endl;
        cout << "2 - CD Title" << endl;
        cout << "3 - CD Number of Tracks" << endl;
        cout << "4 - CD Release Date" << endl;
        cout << "5 - CD Genre" << endl;
        cout << "6 - CD Cost" << endl;
        while(tempOption != '1' || tempOption != '2' || tempOption != '3' || tempOption != '4' || tempOption != '5' || tempOption != '6')
        {
            cout << "Choose an option: ";
            cin >> tempOption;
            if (tempOption == '1' || tempOption == '2' || tempOption == '3' || tempOption == '4' || tempOption == '5' ||
                tempOption == '6')
                break;
            else
                cout << "Invalid input." << endl;
        }
    }
    if(typeid(*tempItem) == typeid(DVD))
    {
        cout << "1 - DVD Title" << endl;
        cout << "2 - DVD Category" << endl;
        cout << "3 - DVD Runtime" << endl;
        cout << "4 - DVD Studio" << endl;
        cout << "5 - DVD Release Date" << endl;
        cout << "6 - DVD Cost" << endl;
        while(tempOption != '1' || tempOption != '2' || tempOption != '3' || tempOption != '4' || tempOption != '5' || tempOption != '6')
        {
            cout << "Choose an option: ";
            cin >> tempOption;
            if (tempOption == '1' || tempOption == '2' || tempOption == '3' || tempOption == '4' || tempOption == '5' || tempOption == '6')
                break;
            else
                cout << "Invalid input." << endl;
        }
    }
    cin.ignore(); //clears buffer for upcoming actions

    switch(tempOption)	//Edits book based on user input
    {
        case '1':
        {
            if(typeid(*tempItem) == typeid(Book))
            {
                string author;
                Book *tempBook = dynamic_cast<Book*>(tempItem);
                cout << "Enter new book author: ";
                getline(cin, author);
                (*tempBook).setAuthor(author);
                cout << "Book author changed." << endl;
            }
            else if(typeid(*tempItem) == typeid(CD))
            {
                string artist;
                CD *tempCD = dynamic_cast<CD*>(tempItem);
                cout << "Enter new CD artist: ";
                getline(cin, artist);
                (*tempCD).setArtist(artist);
                cout << "CD artist changed." << endl;
            }
            else
            {
                string title;
                DVD *tempDVD = dynamic_cast<DVD*>(tempItem);
                cout << "Enter new DVD title: ";
                getline(cin, title);
                (*tempDVD).setTitle(title);
                cout << "DVD title changed." << endl;
            }
            break;
        }
        case '2':
        {
            if(typeid(*tempItem) == typeid(Book))
            {
                string title;
                Book *tempBook = dynamic_cast<Book*>(tempItem);
                cout << "Enter new book title: ";
                getline(cin, title);
                (*tempBook).setTitle(title);
                cout << "Book title changed." << endl;
            }
            else if(typeid(*tempItem) == typeid(CD))
            {
                string title;
                CD *tempCD = dynamic_cast<CD*>(tempItem);
                cout << "Enter new CD title: ";
                getline(cin, title);
                (*tempCD).setTitle(title);
                cout << "CD title changed." << endl;
            }
            else
            {
                string category;
                DVD *tempDVD = dynamic_cast<DVD*>(tempItem);
                cout << "Enter new DVD category: ";
                cin >> category;
                cin.ignore();
                (*tempDVD).setCategory(category);
                cout << "DVD category changed." << endl;
            }
            break;
        }
        case '3':
        {
            if(typeid(*tempItem) == typeid(Book))
            {
                int isbn;
                Book *tempBook = dynamic_cast<Book*>(tempItem);
                cout << "Enter new book ISBN: ";
                cin >> isbn;
                cin.ignore();
                (*tempBook).setIsbn(isbn);
                cout << "Book ISBN changed." << endl;
            }
            else if(typeid(*tempItem) == typeid(CD))
            {
                int numTracks;
                CD *tempCD = dynamic_cast<CD*>(tempItem);
                cout << "Enter new CD number of tracks: ";
                cin >> numTracks;
                cin.ignore();
                (*tempCD).setNumTracks(numTracks);
                cout << "CD number of tracks changed." << endl;
            }
            else
            {
                int runtime;
                DVD *tempDVD = dynamic_cast<DVD *>(tempItem);
                cout << "Enter new DVD runtime(in seconds): ";
                cin >> runtime;
                cin.ignore();
                (*tempDVD).setRunTime(runtime);
                cout << "DVD runtime changed." << endl;
            }
            break;
        }
        case '4':
        {
            if(typeid(*tempItem) == typeid(Book))
            {
                string category;
                Book *tempBook = dynamic_cast<Book*>(tempItem);
                cout << "Enter new book category: ";
                cin >> category;
                cin.ignore();
                (*tempBook).setCategory(category);
                cout << "Book category changed." << endl;
            }
            else if(typeid(*tempItem) == typeid(CD))
            {
                string releaseDate;
                CD *tempCD = dynamic_cast<CD*>(tempItem);
                cout << "Enter new CD release date(mm/dd/yyyy): ";
                getline(cin, releaseDate);
                (*tempCD).setReleaseDate(releaseDate);
                cout << "CD release date changed." << endl;
            }
            else
            {
                string studio;
                DVD *tempDVD = dynamic_cast<DVD *>(tempItem);
                cout << "Enter new DVD studio: ";
                getline(cin, studio);
                (*tempDVD).setStudio(studio);
                cout << "DVD studio changed." << endl;
            }
            break;
        }
        case '5':
        {
            if(typeid(*tempItem) == typeid(Book))
            {
                float cost;
                Book *tempBook = dynamic_cast<Book*>(tempItem);
                cout << "Enter new book cost: ";
                cin >> cost;
                cin.ignore();
                (*tempBook).setCost(cost);
                cout << "Book cost changed." << endl;
            }
            else if(typeid(*tempItem) == typeid(CD))
            {
                string genre;
                CD *tempCD = dynamic_cast<CD *>(tempItem);
                cout << "Enter new CD genre: ";
                getline(cin, genre);
                (*tempCD).setGenre(genre);
                cout << "CD genre changed." << endl;
            }
            else
            {
                string releaseDate;
                DVD *tempDVD = dynamic_cast<DVD *>(tempItem);
                cout << "Enter new DVD release date(mm/dd/yyyy): ";
                getline(cin, releaseDate);
                (*tempDVD).setReleaseDate(releaseDate);
                cout << "DVD release date changed." << endl;
            }
            break;
        }
        case '6':
        {
            if(typeid(*tempItem) == typeid(CD))
            {
                float cost;
                CD *tempCD = dynamic_cast<CD *>(tempItem);
                cout << "Enter new CD cost: ";
                cin >> cost;
                cin.ignore();
                (*tempCD).setCost(cost);
                cout << "CD cost changed." << endl;
            }
            else
            {
                float cost;
                DVD *tempDVD = dynamic_cast<DVD *>(tempItem);
                cout << "Enter new DVD cost: ";
                cin >> cost;
                cin.ignore();
                (*tempDVD).setCost(cost);
                cout << "DVD cost changed." << endl;
            }
            break;
        }
        default:
            break;
    }
}

//Searches for item in vector
void LibraryItems::searchItem(bool searchCheck)	//boolean for searchItem and printItemInfo
{
    int tempId;
    cout << "Enter item's ID: ";
    cin >> tempId;

    LibraryItem *tempItem = nullptr;

    //Checks for item
    for(auto iter = itemVec.begin(); iter != itemVec.end(); iter++)
    {
        if((*iter)->getId() == tempId)
        {
            tempItem = *iter;
            break;
        }
    }

    //if item does not exist
    if(tempItem == nullptr)
        cout << "Item could not be found." << endl;
    else if(searchCheck == false)
        printItemInfo(tempItem);
    else
    {
        if(typeid(*tempItem) ==  typeid(Book))
        {
            Book *tempBook = dynamic_cast<Book*>(tempItem);
            cout << "Book " << (*tempBook).getId() << " (" << (*tempBook).getTitle() << ") exists in our database." << endl;
        }
        else if(typeid(*tempItem) == typeid(CD))
        {
            CD *tempCD = dynamic_cast<CD*>(tempItem);
            cout << "CD " << (*tempCD).getId() << " (" << (*tempCD).getTitle() << ") exists in our database." << endl;
        }
        else
        {
            DVD *tempDVD = dynamic_cast<DVD*>(tempItem);
            cout << "DVD " << (*tempDVD).getId() << " (" << (*tempDVD).getTitle() << ") exists in our database." << endl;
        }
    }
}

//Prints individual item info
void LibraryItems::printItemInfo(LibraryItem *item)
{
    if(typeid(*item) == typeid(Book))
        cout << "Type - Book" << endl;
    if(typeid(*item) == typeid(CD))
        cout << "Type - CD" << endl;
    if(typeid(*item) == typeid(DVD))
        cout << "Type - DVD" << endl;
    (*item).print();
    cout << endl;
}
