/*
Carl Markowski
CS 3060 11.14
This program utilizes structures to hold a certain values in an array of that 
structure type
*/

#include<iostream>
#include<string>
#include<iomanip>

using namespace std;

//Structure
struct Bin {

	string nameOfPart; //Holds the name of the part
	int numParts = 0; //Holds the number of parts in the bin

}bin;


//Function Prototype
void displayBins(Bin[], int);
void addParts(Bin[], int, int, int);
void subParts(Bin[], int, int, int);
int getUserSelection();

//Global Constants
const int MAX_NUM_PARTS = 30; //The maximum number of parts a bin can hold
const int NUM_BINS = 10; //The number of bins available to hold parts

int main() {

	//Variables
	Bin arrayOfBins[NUM_BINS]; //Array of bins
	bool flag = false; //Flag to determine whether or not to continue loop
	int userSelection = 0; //Holds the value of the user selection
	char yesOrNo; //Gets the yes or no value from the user

	//Initialize the arrayOfBins array
	arrayOfBins[0].nameOfPart = "Valve"; arrayOfBins[0].numParts = 10;
	arrayOfBins[1].nameOfPart = "Bearing"; arrayOfBins[1].numParts = 5;
	arrayOfBins[2].nameOfPart = "Bushing"; arrayOfBins[2].numParts = 15;
	arrayOfBins[3].nameOfPart = "Coupling"; arrayOfBins[3].numParts = 21;
	arrayOfBins[4].nameOfPart = "Flange"; arrayOfBins[4].numParts = 7;
	arrayOfBins[5].nameOfPart = "Gear"; arrayOfBins[5].numParts = 5;
	arrayOfBins[6].nameOfPart = "Gear Housing"; arrayOfBins[6].numParts = 5;
	arrayOfBins[7].nameOfPart = "Vacuum Gripper"; arrayOfBins[7].numParts = 25;
	arrayOfBins[8].nameOfPart = "Cable"; arrayOfBins[8].numParts = 18;
	arrayOfBins[9].nameOfPart = "Rod"; arrayOfBins[9].numParts = 12;

	
	//While loop, stops when the user doesn't want to change 
	//any bins anymore
	while (!flag) {

		//Display the bins
		displayBins(arrayOfBins, NUM_BINS);

		//Ask user to select a bin or select 0 to exit loop
		userSelection = getUserSelection();

		//If user selects a bin, ask user if they would like to add or subtract from the bin
		if (userSelection != 0) {
			cout << "Would you like to add parts to the bin?\n" 
				"Please enter 'y' for Yes or 'n' for No: " << endl;
			cin >> yesOrNo;
			cin.clear();
			cin.ignore();
			
			flag = false;

			//Checks if the user entered a 'y' for yes and converts it to uppercase
			//so the entry doesn't have to be case sensitive
			if (toupper(yesOrNo) == 'Y') {
				addParts(arrayOfBins, NUM_BINS, MAX_NUM_PARTS, userSelection);
				flag = false;
			}
			else {
				
				//If the entry was not a 'y' then it moves onto ask about
				//subtracting parts from the bin
				cout << "Would you like to subtract parts from the bin?\n"
					"Please enter 'y' for Yes or 'n' for No: " << endl;
				cin >> yesOrNo;
				flag = false;

				//If the entry is 'y' for subtracting from the bins then it goes into 
				//the subParts function
				if (toupper(yesOrNo) == 'Y') {
					subParts(arrayOfBins, NUM_BINS, MAX_NUM_PARTS, userSelection);
					flag = false; 
				}
			}
		}
		//If user selected 0, exit the loop
		else {
			cout << "Thank you. GoodBye:)" << endl;
			flag = true;
		}
	}

	return 0;
}

//Function to display the Bins
void displayBins(Bin array[], int numBins) {

	cout << "Part Description" << "\t" << "Number Of Parts" << endl;

	for (int i = 0; i < numBins; i++) {

		cout << i + 1 << setw(15) << array[i].nameOfPart << "\t\t" << array[i].numParts << endl;

	}
}

//gets the bin the user would like to access
int getUserSelection() {

	int returnValue = 0;

	cout << "What bin would you like access: " << endl;
	cin >> returnValue;

	return returnValue;
}

//Adds parts to the bin if the user wants to add
void addParts(Bin array[], int numBins, int maxParts, int userSelection) {

	//Variables
	int numAdd = 0; //Holds the number of parts to be added to the bin
	bool flag = false; //Flag used to check if the number inputted by the user is valid

	//Asks the user for the numebr they would like to add
	cout << "Please enter the number of " << array[userSelection - 1].nameOfPart
		<< " you would like to add: " << endl;
	cin >> numAdd;

	while (!flag) {

		//Checks if the user entered a number that sets the bin
		//over the max amount of parts
		if (array[userSelection - 1].numParts + numAdd > maxParts) {
			cout << "The bin can not hold more than 30 parts." << endl;
			cout << "Please enter the number of " << array[userSelection - 1].nameOfPart
				<< " you would like to add: " << endl;
			cin >> numAdd;
		}

		//Checks to see if the user entered a negative number
		else if (numAdd < 0) {
			cout << "Please enter a positive number." << endl;
			cout << "Please enter the number of " << array[userSelection - 1].nameOfPart
				<< " you would like to add: " << endl;
			cin >> numAdd;
		}
		else {
			flag = true;
		}
	}

	//Adds the parts that the user wants to add to the parts
	//already in the bin
	array[userSelection - 1].numParts += numAdd;
}

//Subtracts parts from the bins if the user wants to subtract parts
void subParts(Bin array[], int numBins, int maxParts, int userSelection) {

	//Variables
	int numSub = 0; //Holds the number of parts that are to be subtracted
	bool flag = false; //Flag to check whether or not the user has entered valid numbers

	//Asks the user for the number of parts they would like to subtract
	cout << "Please enter the number of " << array[userSelection - 1].nameOfPart << " you would like to subtract: " << endl;
	cin >> numSub;

	//Checks if the user entered valid numebrs
	while (!flag) {
		
		//If the number of parts in the bin goes below 0, than an error message
		//is printed and the user is asked for  new amount to subtract
		if (array[userSelection - 1].numParts - numSub < 0) {
			cout << "The bin can't hold less than 0 parts. Please enter a new number." << endl;
			cout << "Please enter the number of " << array[userSelection - 1].nameOfPart << " you would like to subtract: " << endl;
			cin >> numSub;
		}
		else {
			flag = true;
		}
	}

	//Subtracts the number of parts indicated by the user from the
	//parts already in the bin
	array[userSelection - 1].numParts -= numSub;
}

