wordfinder: wordfinder.o main.o
	g++ -o wordfinder main.cpp
	
main.o: main.cpp
	g++ -c -Wall -pedantic main.cpp
	
wordfinder.o: WordMap.h
	g++ -c -Wall -pedantic WordMap.h

