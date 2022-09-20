#include "Patron.h"
#include <vector>
using namespace std;

class Patrons
{
public:
    Patrons() {patronCount = 0;}

    int currentPatronId;

    int getPatronCount();		//
    vector<Patron*> getPatronVector();

    void loadPatronData();		//
    void storePatronData();		//

    void addPatron();		//
    void editPatron();		//
    void deletePatron();		//
    void searchPatron(bool searchCheck);		//
    void printAllPatrons();		//
    void printPatronInfo(Patron *patron); 	//
    void payFines();

    void cleanupPatrons();		//
private:
    vector<Patron*> patronVec;
    int patronCount;
};
