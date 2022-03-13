#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#define max 100
using namespace std;

void Guide();
void createMatrix (char[][max], int&, int&, int&);
void createSafePath (char[][max], int, int);
void add(char[][max], int, int, char, char, string, int);
void printMatrix (char[][max], int, int, int, int, char, char);
void playGame (char[][max], int, int, int, int, int, int, ofstream *, int);
void printToFile (int, int, ofstream *);
void endBegin_printToFile (string, int, ofstream *,double);
void move (int*, int*, bool*);

int main()
{
	char matrix[max][max] = { '0' };
	int row, column, difficulty;

	char  monster = 21, wall = '1', path = '0', gold = '$';

	ofstream DataFile("output.txt");

	endBegin_printToFile("begin", 0, &DataFile, 0);

	Guide();
	createMatrix(matrix, row, column, difficulty);
	playGame(matrix, row, column, gold, path, monster, wall, &DataFile, difficulty);

	cout << endl << endl;
	system("pause");
	return 0;
}
void Guide()
{
	char ch;
	cout << "Welcome to the Maze Game\nWould you like to see guide (Y/N):";
	cin >> ch;
	if (ch == 'Y' || ch == 'y' || ch == 'yes')
	{
		cout << endl << " + You are in a maze with the monsters ("<<(char)21<<"). ";
		cout << endl << " + Please, use the W,A,S,D keys to move and try to find a way to escape (0). ";
		cout << endl << " + Watch out for walls (1) and don't get caught by the monsters.. ";
		cout << endl << " + Collect treasures ($) on the way if you can. "; 
		cout << endl << " + If you get caught by monsters you won't die but you will lose your golds. ";
		cout << endl << " + Remember, God is watching you and records your every move in a notebook. (output.txt :D) ";	
	}
}
void createMatrix(char matrix[][max], int &row, int &column, int &difficulty)
{
	cout << "\n\nNow please, enter to number of rows and columns:" << endl;
	cin >> row >> column;
	cout << "Please, select the difficulty by number ( easy=1 / normal=2 / hard=3 ) :  " << endl;
	cin >> difficulty;
	cout << "Loading..." << endl;
	Sleep(1000);
	srand(time(NULL));

	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++)
			matrix[i][j] = (rand() % 2) + 48;  // randomly select; '0' (ascii=48) and '1' (ascii=49)

	add(matrix, row, column, '$', 21, "_monsters", difficulty);
	createSafePath(matrix, row, column);
	add(matrix, row, column, '$', 21, "_golds", (4 - difficulty));
	matrix[0][0] = 48;
}

void createSafePath(char matris[][max], int row, int col)	// to create least one safe way
{
	int i = 0, j = 0, flag;
	for (int t = 0; t < row + col; t++)
	{
		flag = rand() % 2;
		if (flag == 1)		// RIGHT
		{
			j++;
			matris[i][j] = '0';
		}
		else if (flag == 0)		// or DOWN
		{
			i++;
			matris[i][j] = '0';
		}
		if (j == col - 1)
			for (int a = i; a < row; a++)
				matris[a][j] = '0';
		else if (i == row - 1)
			for (int a = j; a < col; a++)
				matris[i][a] = '0';
	}
}
void add(char matrix[][max], int row, int column, char gold, char monster, string str, int difficulty)
{
	int i, j;
	double m = ((double)(row + column)/4) *(difficulty);

	for (int t = 0; t < m ; t++)
	{
		i = rand() % (row);
		j = rand() % (column);
			
		if (str == "_golds")
			matrix[i][j] = gold;
		else if (str == "_monsters")
			matrix[i][j] = monster;
		else
			matrix[i][j] = 49; // wall // ascii code of '1' = 49
	}

}
void printMatrix(char matrix[][max], int i, int j, int row, int column, char gold, char monster)
{
	for (int a = 0; a < row; a++)
	{
		for (int b = 0; b < column; b++)
		{
			if (a == i && b == j)
			{
				cout << left << setw(2) << matrix[a][b];
				cout << left << setw(6) << " *";
			}
			else
			{
				switch (matrix[a][b])
				{
				case '$':
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
					cout << left << setw(8) << matrix[a][b];
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); break;
				case 21:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					cout << left << setw(8) << matrix[a][b];
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); break;
				default:
					cout << left << setw(8) << matrix[a][b]; break;
				}

			}
		}
		printf("\n");
	}
	printf("\n"); printf("\n");
}
void playGame(char matrix[][max], int row, int column, int gold, int path, int monster, int wall, ofstream *DataFile, int difficulty)
{
	bool flag = true;
	int countOfGold = 0, i = 0, j = 0, turn=0;
	
	for (int t = 0; t < row*column; t++)
	{
		
		if (flag)
		{
			system("cls");
			printMatrix(matrix, i, j, row, column, gold, monster);
		}
		flag = true;
		int a = i, b = j;
		move(&i, &j, &flag);
		
		if (i == row)
		{
			double score = (double)(countOfGold + (row*column)*difficulty*difficulty * 10) / (turn);

			cout << "Congratulations, You survived:\nCollected Golds = " << countOfGold;
			cout << "\nNumber of Steps = " << turn << "\nYour Score = " << score << endl;
			endBegin_printToFile("end_win", countOfGold, DataFile, score);
			break;
		}
		else
		{
			if (matrix[i][j] == gold && flag)
			{
				countOfGold++;
				matrix[i][j] = path;
				printToFile(i, j, DataFile);
				turn++;
			}
			else if (matrix[i][j] == path && flag)
			{
				printToFile(i, j, DataFile);
				turn++;
			}

			else if (matrix[i][j] == monster)
			{
				cout << " You got caught by the monsters." << endl << " Wait 3 seconds to try again.." << endl;

				i = 0; j = 0; countOfGold = 0;
				Sleep(3000);

				endBegin_printToFile("end_lose", 0, DataFile, 0);
			}
			else if (matrix[i][j] == wall || i < 0 || j < 0 || j == column)
			{
				i = a;
				j = b;
			}
		}
	}
}
void printToFile(int i, int j, ofstream *DataFile)
{
	*DataFile << setw(6) << i;
	*DataFile << setw(6) << j;
	*DataFile << endl;
}
void endBegin_printToFile(string str, int countOfGold, ofstream *DataFile, double score)
{
	if (str == "begin")
		*DataFile << setw(7) << "Row" << setw(8) << "Column" << endl << "  --------------" << endl << setw(6) << "0" << setw(6) << "0" << endl;
	else if (str == "end_lose")
		*DataFile << setw(16) << "---GAME OVER---" << endl << endl << endl << setw(7) << "Row" << setw(8) << "Column" << endl << "  --------------" << endl << setw(6) << "0" << setw(6) << "0" << endl;
	else if (str == "end_win")
		*DataFile << endl << "You've successfully completed: \nCollected Golds = " << countOfGold << "\nYour Score = " << score << endl;
}
void move(int*i, int*j, bool*flag)
{
	int key = _getch();

	switch (key)
	{
	case'a':
	case'A': *j = *j - 1; break;			//LEFT
	case'd':
	case'D': *j = *j + 1; break;			//RIGHT
	case'w':
	case'W': *i = *i - 1; break;			//UP
	case's':
	case'S': *i = *i + 1; break;			//DOWN
	default: *flag = false; break;
	}
}


