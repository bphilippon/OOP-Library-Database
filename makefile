output: main.o Loans.o Loan.o LibraryItems.o LibraryItem.o Book.o CD.o DVD.o Patrons.o Patron.o
	g++ main.o Loans.o Loan.o LibraryItems.o LibraryItem.o Book.o CD.o DVD.o Patrons.o Patron.o -o output
main.o: main.cpp Loans.cpp Loans.h
	g++ -c main.cpp
Loans.o: Loans.cpp Loans.h
	g++ -c Loans.cpp
Loan.o: Loan.cpp Loan.h
	g++ -c Loan.cpp
LibraryItems.o: LibraryItems.cpp LibraryItems.h Book.cpp Book.h CD.cpp CD.h DVD.cpp DVD.h
	g++ -c LibraryItems.cpp Book.cpp CD.cpp DVD.cpp
LibraryItem.o: LibraryItem.cpp LibraryItem.h
	g++ -c LibraryItem.cpp
Book.o: Book.cpp Book.h
	g++ -c Book.cpp
CD.o: CD.cpp CD.h
	g++ -c CD.cpp
DVD.o: DVD.cpp DVD.h
	g++ -c DVD.cpp
Patrons.o: Patrons.cpp Patrons.h
	g++ -c Patrons.cpp
Patron.o: Patron.cpp Patron.h
	g++ -c Patron.cpp
clean:
	rm *.o;
