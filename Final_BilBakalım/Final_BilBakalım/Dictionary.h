#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <set>
#include <vector>
#include <string>
using namespace std;

class Dictionary {
public:
	//Default Constructor
	Dictionary();
	//opens file and assign all words into set<string> words;
	Dictionary(char *filename);
	//Destructor
	~Dictionary();
	// return a random word (without repeated letters)
	string BringValidWord();
	// check if word is in Dictionary
	bool IsWordValid(string word);
private:
	// test if n. word has only unique letters
	bool TestLegalSecretWord(string word);
	set<string> words;
	vector<string> secrets;
};
#endif