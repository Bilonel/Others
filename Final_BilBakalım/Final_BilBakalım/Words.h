#ifndef WORDS_H
#define WORDS_H

#include <string>
class Words {
public:
	Words() {}; //Default Constructor
	~Words() {}; //Destructor
	// public interface to play game of Words
	//it may call from main() using followings;
	//main(){
	//Words W;
	//W.playgame(W);
	//}
	void playgame(Dictionary &);
private:
	// count functions compare string param with the secret word
	// find common letters in any order
	int countofMatchLetters(string);
	// find common letters in place
	int countofTruePlaceLetters(string);
	// track number of guesses used
	int numguesses;
	// flag set to true if cheat code is used
	bool cheated;
	// word to guess
	string secret;
};
void EndText(char&);
#endif