/**
  main.cpp
  Jason Dietrich
  last modified 10/14/12

    Demonstrates basic controller functions for a WordMap object.

    To test WordMap's functionality simply run this program with
    the "OSPD4.txt" as the first argument. This will load
    OSPD4 (a file containing over 178k English words) into the
    WordMap dictionary. You will then be prompted to input a
    string of characters, which are then processed by WordMap
    and exchanged for a list of all dictionary words that are
    valid anagrams of your input string.

*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "WordMap.h"
using namespace std;
WordMap wordmap;
void loadFile (string fileName);

int main(int argc, char** argv)
{
  if (argc == 2){
    cout << "Loading " << argv[1] << "...";
    loadFile(argv[1]);
    cout << "complete.\n";
  }
  while (true){
    string input;
    cout << "Enter a string of upper-case letters from which to find anagrams\n:> ";
    cin >> input;

    vector <string> wordList = wordmap.getAllWordsFromString (input);

    for (unsigned int i=0; i<wordList.size(); i++){
      cout << wordList[i] << "\t";
    }
    cout << wordList.size() << "\n\n";
  }
  return 0;
}

void loadFile (string fileName)
{
  ifstream fin;
  fin.open (fileName.c_str());
  if (!fin.fail()){
    char nextChar;
    bool add = true;
    string newWord("");
    while (fin.good()){
      nextChar = fin.get();
      if (nextChar != fin.eof()){
        if (nextChar == ' '){
          add = false;
          wordmap.insert(newWord);
          //cout << newWord << endl;
        }
        else if (nextChar == '\n'){
          newWord = ("");
          add = true;
        }
        else if (add){
          newWord+=nextChar;
        }
      }
    }
  }
}
