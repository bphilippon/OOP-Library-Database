#include <ctime>
#include <string>
using namespace std;

class Loan
{
public:
    Loan();
    Loan(int loanId, int itemId, int patronId, tm *dueDate, string currentStatus, bool recheck);

    int getLoanId();
    int getItemId();
    int getPatronId();
    tm* getDueDate();
    string getCurrentStatus();
    bool wasRechecked();

    void setLoanId(int loanId);
    void setItemId(int itemId);
    void setPatronId(int patronId);
    void setDueDate(tm *dueDate);
    void setCurrentStatus(string currentStatus);
    //void recheckLoan();
    void setRecheck(bool recheck);

private:
    int loanId;
    int itemId;
    int patronId;
    tm* dueDate;
    string currentStatus;
    bool recheck;
};
