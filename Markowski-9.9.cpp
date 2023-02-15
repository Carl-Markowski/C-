/*
Carl Markowski
CS 3060 9.9
*/

#include <iostream>
#include <iomanip>

using namespace std;

//Function Prototypes
int getArraySize(); //Gets the size if the array
void getArrayValues(int*, int); //Gets the values for the array
double getMedianOfArray(int*, int); //Finds the median of the array

int main() {

	//Variables
	int arraySize = 0; //Holds the value of the array size
	int array[100] = { 0 }; //Array for the values of the function
	double median = 0.0; //Holds the return value from getMedianOfArray

	arraySize = getArraySize(); //Gets the size of the array

	getArrayValues(array, arraySize); //Gets the values for the array

	//Get the median of the array
	median = getMedianOfArray(array, arraySize);

	cout << "The median of the array is: " << median;

	return 0;
}

//This function gets the size of the array
int getArraySize() {

	int arraySize = 0;

	cout << "Enter the number of values you will enter: ";
	cin >> arraySize;

	return arraySize;
}

//This function gets the values for the array
void getArrayValues(int* array, int numElements) {

	for (int i = 0; i < numElements; i++) {
		cout << "Enter the values to be tested: ";
		cin >> array[i];
	}
}

//This function gets the median of the array
double getMedianOfArray(int* array, int numElements) {

	double returnValue = 0.0;
	int half = 0;

	//Finds out if numElements is even or odd
	if (numElements % 2 == 0) {

		half = numElements / 2;

		returnValue = static_cast<double> (array[half] + array[half - 1]) / 2;
	}
	else {

		half = (numElements / 2);

		returnValue = static_cast<double> (array[half]);
	}

	return returnValue;
}