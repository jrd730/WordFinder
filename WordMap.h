/**
    WordMap.h
    Jason Dietrich
    last modified 10/14/12

        A class for storing dictionary strings and is able to quickly look up anagrams of input strings.
        Works great for cheating at Scrabble.

*/

#include <algorithm>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>
using namespace std;

/**
    WordMap: a specialized data structure for rapidly retrieving valid anagrams of strings.

    Use insert(string) to load the dictionary with valid words.

    The strings are stored based on the alphabetical arrangement of each string's characters.

    Input strings are case sensitive.

    Use getAllWordsFromString() to return a vector with all dictionary strings
    that could be made up of the input string's characters.
*/
class WordMap
{
  public:
    WordMap ()
    {
      wordmap.resize (26);
    }
    ~WordMap (){}

    void insert (string newWord)
    {
      string key = newWord;
      stable_sort(key.begin(), key.end());
      it = wordmap[key.length()].find(key);

      if (it == wordmap[key.length()].end()){
        stack <string> newStack;
        newStack.push(newWord);
        wordmap[key.length()][key] = newStack;
      }
      else{
        it->second.push (newWord);
        //cout << it->second.top() << "\t";
      }
    }

    bool find (string targetWord)
    {
        string key = targetWord;
        stable_sort(key.begin(), key.end());
        it = wordmap[key.length()].find(key);
        if (it == wordmap[key.length()].end()){
          return false;
        }
        else{
          stack <string> tempStack = it->second;
          for (; !tempStack.empty(); tempStack.pop())
          {
            if (tempStack.top() == targetWord){
              return true;
            }
          }
        }
        return false;
    }

    vector <string> getAllWordsFromString (string letters)
    {
      map <string, int> validWordMap;
      vector <string> validWordVec;
      stack <string> subset;
      string key = letters;
      stable_sort(key.begin(), key.end());

      //cout << "Getting distinct subsets of letters...";
      subset.push(key);
      getAllSubsets (key, 2, subset);
      //cout << "complete! " << subset.size() << "\n\n";

      //cout << "Looking up words from subsets...";
      for (; !subset.empty(); subset.pop()){
        it = wordmap[subset.top().length()].find (subset.top());
        if (it != wordmap[subset.top().length()].end()){
          stack <string> wordStack = it->second;
          for (; !wordStack.empty(); wordStack.pop()){
              validWordMap[wordStack.top()] = 1;
          }
        }
      }
      //cout << "complete!\n\n";

      //cout << "Copying words to output vector...";
      map <string, int > :: iterator iter;
      validWordVec.resize(validWordMap.size());
      int i = 0;
      for (iter = validWordMap.begin(); iter != validWordMap.end(); iter++, i++){
        validWordVec[i] = (iter->first);
      }
      //cout << "complete!\n\n";
      return validWordVec;
    }

  private:

    void getAllSubsets (string initial, unsigned int minSubSize, stack<string>& subset)
    {
      for (unsigned int i=minSubSize; i<initial.length(); i++){
        getSubsets(initial, i, subset);
      }
    }

    void getSubsets (string initial, unsigned int subsetSize, stack<string>& subset)
    {
      bool include [initial.size()];
      fill (include, include+subsetSize, true);
      fill (include+subsetSize, include+initial.length(), false);

      do{
        string subStr("");
        for (unsigned int i=0; i<initial.size(); i++){
          if (include[i]){
              subStr += initial[i];
          }
        }
        subset.push(subStr);
      }while(prev_permutation(include, include+initial.length()));
    }

    vector <map <string, stack <string> > > wordmap;

    map <string, stack<string> > :: iterator it;
};
