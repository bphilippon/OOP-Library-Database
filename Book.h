#include "LibraryItem.h"
#include <string>
using namespace std;

class Book: public LibraryItem
{
public:
    Book();
    Book(int, float, string, int, string, string, int, string);

    string getAuthor();
    string getTitle();
    int getIsbn();
    string getCategory();

    void setAuthor(string author);
    void setTitle(string title);
    void setIsbn(int isbn);
    void setCategory(string category);

    void print();
    void fileprint(ofstream &fout);
private:
    string author;
    string title;
    int isbn;
    string category;
};

