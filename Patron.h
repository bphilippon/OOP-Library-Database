#include <string>
using namespace std;

class Patron
{
public:
    Patron();
    Patron(string name, int id, float balance, int numItems);

    string getName();
    int getId();
    float getBalance();
    int getNumberOfItems();

    void setName(string name);
    void setId(int id);
    void setBalance(float balance);
    void setNumberOfItems(int numItems);
private:
    string name;
    int id;
    float balance;
    int numItems;
};
