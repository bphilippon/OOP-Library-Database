#include "Patrons.h"
#include "LibraryItems.h"
#include "Loan.h"
#include <vector>
using namespace std;

class Loans
{
public:
    Loans() {loanCount = 0;}

    int currentLoanId;

    int getLoanCount();	//

    void loadLoanData();	//
    void storeLoanData();	//
    void cleanupLoans();	//

    void checkOutBook(vector<Patron*> patronVec, vector<LibraryItem*> itemVec);	//
    void checkInBook(vector<Patron*> patronVec, vector<LibraryItem*> itemVec);	//
    void listAllOverdue();	//	lists all overdue books
    void listAllItems(vector<Patron*> patronVec, vector<LibraryItem*> itemVec); 	//	for a paticular patron
    void updateStatus(Loan *loan, vector<Patron*> patronVec, vector<LibraryItem*> itemVec);	//
    void updateStatus(vector<Patron*> patronVec, vector<LibraryItem*> itemVec);	//
    void recheckLoan(vector<LibraryItem*> itemVec);	//
    void editLoan();	//
    void reportLost(vector<Patron*>  patronVec, vector<LibraryItem*> itemVec);	//
    void printAllOverdueForPatron(); 	//for a particular patron
    void printAllLoans();	//
private:
    vector<Loan*> loanVec;
    int loanCount;
};
