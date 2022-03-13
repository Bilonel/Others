#include "Dictionary.h"
#include "Words.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <vector>
#include <string>
#include <fstream>
#include <time.h>

using namespace std;

Dictionary::Dictionary(char *filename)
{
	ifstream dataFile(filename);
	string tmp;

	if (!dataFile)
	{
		cout << "File open error!" << endl;
		exit(0);
	}
	else
	{
		dataFile >> tmp;
		while (!dataFile.eof())
		{
			words.insert(tmp);	  // set words

			if (tmp.length() == 5)
			{	// set valid secret words
				if(TestLegalSecretWord(tmp))
					secrets.push_back(tmp);
			}
			dataFile >> tmp;
		}	
	}
	dataFile.close();
}

string Dictionary::BringValidWord()
{
	srand(time(NULL));

	vector<string>::iterator it = secrets.begin();

	advance(it, rand() % secrets.size());   // to choose randomly a secret word
	cout << "\nI kept a word. \n";
	string tmp = *it;	
	return tmp;
}
bool Dictionary::IsWordValid(string word)	// is it in dictionary?
{
	bool flag = false;
	for (set<string>::iterator it = words.begin(); it != words.end(); ++it)
	{
		string buffer = *it;
		if (word == buffer)
		{
			flag = true; 
			break;
		}
	}
	return flag;
}
bool Dictionary::TestLegalSecretWord(string word) 	 // is it correct? 
{
	bool flag = 1;

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if ((word[i] == word[j]) && (i != j))   // if whole letters of the word are not different from each other, return 0. 
				flag = 0;
	if (flag)	// if they are different each other it can be included to 'valid secrets'.
		return true;
	else
		return false;
}
Dictionary::Dictionary() {}
Dictionary::~Dictionary() {}
int Words::countofMatchLetters(string word)
{
	int countofMatchLetters = 0;
	int flag = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < word.length(); j++)
		{
			if (secret[i] == word[j])   // when equality is achieved, count of match letters +1.
				flag = 1;
		}
		if (flag == 1)
			countofMatchLetters++;	  
		flag = 0;
	}
	return countofMatchLetters;
}
int Words::countofTruePlaceLetters(string word)
{
	int countofTruePlaceLetters = 0;
	for (int i = 0; i < 5; i++)
		if (secret[i] == word[i])
			countofTruePlaceLetters++;

	return countofTruePlaceLetters;
}
void Words::playgame(Dictionary &D)
{
	bool flag = false;
	string w;
	numguesses = 0;
	cheated = false;
	secret = D.BringValidWord();

	while (!flag)
	{
		cout << "\nGuess What?  ";
		cin >> w;
		numguesses++;
		
		if (D.IsWordValid(w))
		{
			if (w == secret)
			{
				cout << "You found the correct answer";
				if(cheated) cout << " using hint.";
				cout << "\nYou tried " << numguesses << " times."<<endl;
				flag = true;
			}
			else
			{
				cout << endl << "Number of Match Letters: " << countofMatchLetters(w);
				cout << endl << "Number of True Place Letters: " << countofTruePlaceLetters(w) << endl;
			}
		}
		else if (w == "xxxxx")
		{
			cout << "\nTip ; Secret Word: " << secret<<endl;
			cheated = true;
		}
		else
			cout << "Ýt is not include to dictionary !"<<endl;
	}
}
void EndText(char& playagain)
{
	cout << "\nDo you want to play again?  (Y/N): ";
	cin >> playagain;
	cout << endl << endl;
}