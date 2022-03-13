#include "Dictionary.h"
#include "Words.h"

#include <iostream>
using namespace std;

int main()
{
	char PlayAgain = 'Y';
	char filename[30];

	cout << "Welcome to Guess What? \n------------------------\nPlease, Enter file name:" << endl;
	cin >> filename;

	Dictionary _Dict1(filename);
	Words _Words1;
	
	while ( PlayAgain == 'Y' || PlayAgain == 'y' )
	{		
		_Words1.playgame(_Dict1);
		EndText(PlayAgain);
	}
	
	system("pause");
	return 0;
}