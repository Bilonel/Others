#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<cmath>
#include <iomanip>
#include <fstream>
#include <string>
#define max 100
using namespace std;

void inputmatris (int start, int finish , double[21][21] , int upper , int lower);
void makemirror (int start, int finish, double[21][21], int mirror);
void makekernel (int mirror, double[max][max], int fsize);
void apply(int start, int finish, int fsize, int mirror, double[21][21], double[max][max], double[21][21]);
bool isOdd(int);

int main()
{
	srand(time(NULL));
	ifstream Input("inputs.txt");
	
	int ImageSize, FilterSize, UpperLimit, LowerLimit;
	Input >> ImageSize >> FilterSize >> UpperLimit >> LowerLimit;

	if ( !Input.is_open() )
	{	
		cout << "Cannot open the input file." << endl << "Program terminates!!!" << endl << endl << endl;
		system("pause");
		exit(0);
	}
	else if ( !isOdd(ImageSize) || !isOdd(FilterSize) )
	{	
		cout << "Image size and filter size have to be odd numbers!" << endl << "Program terminates !!!" << endl << endl << endl;
		system("pause");
		exit(0);
	}
	

	ofstream Out("Output.txt");

	Out.setf(ios::fixed);
	Out.precision(4);

	
	int k, m;
	
	double Image[21][21] = { 0 }, kernel[max][max] = { 0 }, OutputGrid[21][21] = { 0 };

	int MirrorSize = FilterSize / 2;
	int start = (21 - ImageSize) / 2;
	int finish = (21 + ImageSize) / 2;
	
	inputmatris (start, finish, Image, UpperLimit, LowerLimit);

	makemirror (start, finish, Image, MirrorSize);

	makekernel (MirrorSize, kernel, FilterSize);
	
	apply (start, finish, FilterSize, MirrorSize, Image, kernel, OutputGrid);


	//-------------------------------------------------------------OUTPUT

	Out << "Input Image (" << ImageSize << "x" << ImageSize << ")" << endl << "-------------------------" << endl;
	for (k = start; k < finish; k++)
	{
		for (m = start; m < finish; m++)
			Out << setw(9) << Image[k][m];
		Out << endl;
	}
	Out << endl;

	Out << "Filter (" << FilterSize << "x" << FilterSize << ")" << endl << "--------------------------" << endl;
	for (k = 0; k < FilterSize; k++)
	{
		for (m = 0; m < FilterSize; m++)
		{
			Out << right << setw(9) << kernel[k][m];
		}
		Out << endl;
	}
	Out << endl;

	Out << "Input Grid (21x21)" << endl << "----------------------------" << endl;
	for (k = 0; k < 21; k++)
	{
		for (m = 0; m < 21; m++)
			Out << setw(9) << Image[k][m];
		Out << endl;
	}
	Out << endl;

	Out << "Output Grid (21x21)" << endl << "------------------------------" << endl;
	for (k = 0; k < 21; k++)
	{
		for (m = 0; m < 21; m++)
			Out << right << setw(9) << OutputGrid[k][m];
		Out << endl;
	}
	Out << endl;

	Out << "Output 'Filtered' Image (" << ImageSize << "x" << ImageSize << ")" << endl << "-------------------------------" << endl;
	for (k = start; k < finish; k++)
	{
		for (m = start; m < finish; m++)
			Out << right << setw(9) << OutputGrid[k][m];
		Out << endl;
	}
	Out << endl;

	Input.close();
	Out.close();

	char a='\n';
	ifstream in("output.txt");

	while (in)
	{
		while (a != '\n')
		{
			cout << a;
			in.get(a);	
		}
		in.get(a);
		cout << endl;
	}

	in.close();

	system("pause");
	return 0;
}

void inputmatris(int start, int finish, double Image[21][21], int upper, int lower)
{
	int k,m;

	for (k = start; k < finish; k++)
	{
		for (m = start; m < finish; m++)
			Image[k][m] = rand() % (upper - lower + 1) + lower;
	}
}

void makemirror(int start, int finish, double Image[21][21], int mirror)
{
	int k, m;

	for (k = start - mirror; k < start; k++)
	{
		for (m = start; m < finish; m++)
			Image[k][m] = Image[start][m];
	}

	for (k = finish; k < finish + mirror; k++)
	{
		for (m = start; m < finish; m++)
			Image[k][m] = Image[finish - 1][m];
	}

	for (k = start - mirror; k < finish + mirror; k++)
	{
		for (m = start - mirror; m < start; m++)
			Image[k][m] = Image[k][start];
	}

	for (k = start - mirror; k < finish + mirror; k++)
	{
		for (m = finish; m < finish + mirror; m++)
			Image[k][m] = Image[k][finish - 1];
	}
}

void makekernel(int mirror, double kernel[max][max], int fsize)
{
	int d, i, j;
	double value;

	for (d = 0; d < mirror; d++)
	{
		value = 1.0 / pow((2 * (d + 1) + 1), 2);
		for (i = -(d + 1); i <= d + 1; i++)
		{
			for (j = -(d + 1); j <= d + 1; j++)
				kernel[mirror - i][mirror - j] = kernel[mirror - i][mirror - j] + value;
		}

	}
	for (i = 0; i < fsize; i++)
	{
		for (j = 0; j < fsize; j++)
		{
			kernel[i][j] = kernel[i][j] / static_cast<double>(fsize);
		}
	}
}

void apply(int start, int finish, int fsize, int mirror, double Image[21][21], double kernel[max][max], double OutputGrid[21][21])
{
	int i, j, k, m;
	double x = 0;

	for (i = start; i < finish; i++)
	{
		for (j = start; j < finish; j++)
		{
			for (k = 0; k < fsize; k++)
			{
				for (m = 0; m < fsize; m++)
				{
					x = x + (kernel[k][m] * Image[k + i - mirror][m + j - mirror]);
				}
			}

			OutputGrid[i][j] = x / static_cast<double>(fsize*fsize);
			x = 0;
		}
	}
}

bool isOdd(int x)
{
	if (x % 2 == 1)
		return true;
	else
		return false;
}
