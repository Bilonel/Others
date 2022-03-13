#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<cmath>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	ifstream ClassA("group1.txt");
	ifstream ClassB("group2.txt");
	ofstream Output("StudentNotes.txt");
	int i, x, y, k , t , j ;
	double z, sum = 0.0;
	double avgofgroup1 = 0, avgofgroup2 = 0;
	string lesson;
	
	Output << " Course" << "   Average";
	Output << " " << "  " <<"0   10   20   30   40   50   60   70   80   90   100" << endl;
	Output <<" ID"<< setw(13) <<" "<<"    "<< "|....|....|....|....|....|....|....|....|....|....|"<<endl<<endl;
	
	for(k=0;k<100;k++)
	{
		for (i = 0; i < 100; i++)
		{
			if (i == 0)
			{
				ClassA >> lesson;
					if (!ClassA)								
						break;

					Output <<" "<< lesson ;
			}
			else
			{
		
				ClassA >> x;

				if (x == -999)
				{
					z = i - 1;
					i = 100;
				

				}
				else
					sum = sum + x;
					
			}

		}
		if (!ClassA)
			break;

		double avg = sum / z;
		avgofgroup1 = avgofgroup1 + avg;
		sum = 0;

		Output << fixed << showpoint;
		Output << setw(12) << setprecision(2) << avg <<"    ";
		
		int bar = avg / 1.97 + 1;
		for (t = 0; t < bar; t++)
			Output << "*";
		Output <<endl;

		cin.clear();
		for (j = 0; j < 100; j++)
		{
			if (j == 0)
			{
				ClassB >> lesson;

			}
			else
			{

				ClassB >> x;

				if (x == -999)
				{
					z = j - 1;
					j = 100;


				}
				else
					sum = sum + x;

			}
			

		}
		

		avg = sum / z;
		avgofgroup2 = avgofgroup2 + avg;
		sum = 0;

		Output << fixed << showpoint;
		Output << setw(16) << setprecision(2) << avg << "    ";

		bar = avg / 1.97 + 1;
		for (t = 0; t < bar; t++)
			Output << "#";
		Output << endl;
	}
	Output << endl << "Group1 => ***" << endl << "Group2 => ###";
	Output << endl << "Average of Group1: " << avgofgroup1/(k);
	Output << endl << "Average of Group2: " << avgofgroup2/(k);









	ClassA.close();
	ClassB.close();
	Output.close();
	cout << "Processing data..." << endl << endl;
	system("pause");
	return 0;
}
