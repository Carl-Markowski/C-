/*
Carl Markowski
Cs 3060 9.8
*/

#include <iostream>
#include <iomanip>

using namespace std;

//Function prototype
int getModeOfArray(int*, int);
void getValues(int*, int);

int main() {

	//Const for the array size
	const int SIZE = 10;

	//Variables
	int arrayToBeTested[SIZE] = { 0 }; //Array to be tested
	int modeOfArray = 0; //Integer to hold the mode of the array

	getValues(arrayToBeTested, SIZE); //Gets the values for the array to be tested

	//Gets the mode of the array 
	modeOfArray = getModeOfArray(arrayToBeTested, SIZE);

	if (modeOfArray != -1) {
		cout << "The mode of the array is " << modeOfArray << ".";
	}
	else {
		cout << "There is no mode in this array.";
	}

	return 0;
}

void getValues(int *array, int numElements){

	for (int i = 0; i < numElements; i++) {
		cout << "Please Enter various numbers between 0 and 10: ";
		cin >> array[i];
	}
}

//Function to get the mode of the array (most occuring value)
int getModeOfArray(int *array, int numElements) {

	int compare1 = 0; //First compare value
	int compare2 = 0; //Holds the current mode
	int iterator = 0; //Iterates through the array
	int count1 = 0; //Counts the number of occurences
	int count2 = 0; //Used to compare which value is higher
	int lastOccurence = 0; //Holds the value of the last occurence

	//For loop to iterate through the array
	for (int i = 0; i < numElements; i++) {
		compare1 = array[i]; //Making compare1 equal to the first element of the array
		
		//For loop to check if compare1 equals any values in the array
		for (int j = i + 1; j < numElements + 1; j++) {

			//If compare1 is eqaul to the current array element then
			//set lastOccurence equal to compare1 and increment count1
			if (compare1 == array[j]) {
				lastOccurence = compare1;
				count1++;
				if (count1 > count2) {
					count2 = count1;
					compare2 = compare1;
				}
				else if (compare1 == lastOccurence) {
					count1++;
					if (count1 > count2) {
						count2 = count1;
						compare2 = compare1;
					}
				}
			}
		}
	}

	//If the count of all the occurences is more than 0 than return the most common occurence
	if (count2 > 0) {
		return compare2;
	}
	//If it is less than 0 return -1
	else {
		return -1;
	}
}