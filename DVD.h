#include "LibraryItem.h"
#include <string>
using namespace std;

class DVD: public LibraryItem
{
public:
    DVD();
    DVD(int, float, string, int, string, string, int, string, string);

    string getTitle();
    string getCategory();
    int getRunTime();
    string getStudio();
    string getReleaseDate();

    void setTitle(string title);
    void setCategory(string category);
    void setRunTime(int runTime);
    void setStudio(string studio);
    void setReleaseDate(string releaseDate);

    void print();
    void fileprint(ofstream &fout);
private:
    string title;
    string category;
    int runTime;	//in seconds
    string studio;
    string releaseDate;
};
