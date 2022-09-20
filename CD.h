#include "LibraryItem.h"
#include <string>
using namespace std;

class CD: public LibraryItem
{
public:
    CD();
    CD(int, float, string, int, string, string, int, string, string);

    string getArtist();
    string getTitle();
    int getNumTracks();
    string getReleaseDate();
    string getGenre();

    void setArtist(string artist);
    void setTitle(string title);
    void setNumTracks(int numTracks);
    void setReleaseDate(string releaseDate);
    void setGenre(string genre);

    void print();
    void fileprint(ofstream &fout);
private:
    string artist;
    string title;
    int numTracks;
    string releaseDate;
    string genre;
};
