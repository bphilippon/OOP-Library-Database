#ifndef LIBRARYITEM_H
#define LIBRARYITEM_H
#include <string>
#include <fstream>
using namespace std;

class LibraryItem
{
public:
    LibraryItem();
    LibraryItem(int id, float cost, string currentStatus, int loanPeriod);
    virtual ~LibraryItem(){};

    int getId();
    float getCost();
    string getCurrentStatus();	//In, Out, Lost
    int getLoanPeriod();

    void setId(int id);
    void setCost(float cost);
    void setCurrentStatus(string currentStatus);
    void setLoanPeriod(int loanPeriod);

    virtual void print();
    virtual void fileprint(ofstream &fout);
    friend ofstream& operator<<(ofstream &fout, LibraryItem &item);
private:
    int id;
    float cost;
    string currentStatus;
    int loanPeriod;		//in days
};
#endif
