#include "LibraryItem.h"
#include <vector>
using namespace std;

class LibraryItems
{
public:
    LibraryItems() {itemCount = 0;}

    int currentItemId;

    int getItemCount();	//
    vector<LibraryItem*> getItemVector();

    void loadItemData();	//
    void storeItemData();	//
    void cleanupItems();	//

    void addItem();		//
    void editItem();	//
    void deleteItem();	//
    void searchItem(bool searchCheck);
    void printAllItems();	//
    void printItemInfo(LibraryItem *item);
private:
    vector<LibraryItem*> itemVec;
    int itemCount;
};
