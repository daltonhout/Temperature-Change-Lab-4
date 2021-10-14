/*
* Dalton Hout
* Lab 4: Temperature Output
* 10/13/21
* Outputting a graph that displays hourly temperatures read from an input file.
*/
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cctype>


using namespace std;

int ChkErrors(ifstream& inFile);
//Pre: User inputs a file with temps.
//Post: When all data is correct type, it will be used to print the graph.
void BarGraph(ifstream& inFile, string fileName);
//Pre: Correct data in the input file.
//Post: Prints bar graph with temps in file.

int main()
{
	ifstream inFile;
	string fileName;

	//loop prompts user for a file name.
	do
	{
		cout << "Enter the input file name plaese: ";
		cin >> fileName;
		inFile.open(fileName.c_str());

		if (!inFile)
		{
			cout << "File failed to open, please make sure the file name is spelled correctly.\n";
			cout << "Enter file name again or press 'Z' to quit: ";
			cin >> fileName;
			cout << "\n\n\n";

			if (fileName == "Z" || fileName == "z")
			{
				cout << "Bye bye...\n\n";
				return 1;
			}
			inFile.open(fileName.c_str());
		}
	} while (!inFile);


	if (ChkErrors(inFile) == 1)
	{
		return 1;
	}
	//Reads the input file to print the stars to the screen.
	BarGraph(inFile, fileName);

	return 0;
}

//This makes sure the input file doesn't have any improper characters.
int ChkErrors(ifstream& inFile)
{
	char errorCheck;
	inFile >> errorCheck;
	//Loop makes sure the input file doesn't have invalid data types.
	while (inFile)
	{
		if (isalpha(errorCheck)) //True if input contains letters.
		{
			cout << "Error!";

			return 1;
		}
		inFile >> errorCheck; // Program terminates if an error was found in the input file.
	}
	inFile.close();
	return 0; //No errors were found.
}

void BarGraph(ifstream& inFile, string fileName)
{
	float temp;
	//Graph title
	cout << "\n\nTemps for 24 hours: \n";
	cout << setw(8) << "-30" << setw(8) << "0" << setw(10) << "30" << setw(10) << "60" << setw(10) << "90" << setw(10) << "120" << endl;

	inFile.open(fileName.c_str());
	inFile >> temp;

	while (inFile)
	{
		temp = ceil(temp); //This rounds floating point values to whole numbers.

		string OutputStars;
		OutputStars = "";

		if (temp < -30 || temp > 120) //If the temp is out of the given range, the next value is read in.
		{
			inFile >> temp;
			continue;
		}
		else //Temp is in given range.
		{
			cout << temp << ":";
		}
		//Loop detirmines the amount of stars per degree.
		for (int i = 1; i <= (abs(temp) / 3.0); ++i) //To calculate negative values, abs() is used.
		{
			OutputStars.append("*");
		}
		//If else prints the temp with the number of stars for that value.
		if (temp == -30)
		{
			cout << setw(12) << OutputStars + "|";
		}
		else if (temp > -30 && temp <= -10) {
			cout << setw(12) << OutputStars + "|";
		}
		else if (temp > -10 && temp < 0) {
			cout << setw(13) << OutputStars + "|";
		}
		else if (temp >= 0 && temp < 10) {
			cout << setw(14) << "|" << OutputStars;
		}
		else if (temp >= 10 && temp < 100) {
			cout << setw(13) << "|" << OutputStars;
		}
		else if (temp >= 100 && temp <= 120) {
			cout << setw(12) << "|" << OutputStars;
		}

		cout << endl;
		inFile >> temp;
	}
	cout << "* = 3 degrees";
	inFile.close();

}
