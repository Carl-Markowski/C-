/*
Carl Markowski
CS 3060 7.3
This code allows a chip maker to keep track of sales
*/

#include <iostream>
#include <iomanip>

using namespace std;

//Function prototype
int getJarsSold(string[]);
int getHighestSold(int[], int);
int getLowestSold(int[], int);
void displayJarsSold(int[], string[], int, int, int);

int main() {

	//Variables
	string salsaNames[5] = { "Mild", "Medium", "Sweet", "Hot", "Zesty" }; //Array to hold salsa names
	int numberOfJarsSold[5] = { 0 }; //Array to hold number of jars sold
	

	//Gets the number of elements in the array 
	int number = sizeof(numberOfJarsSold) / sizeof(numberOfJarsSold[0]);

	//Get the number of jars sold
	for (unsigned int i = 0; i < number; i++) {
		numberOfJarsSold[i] = getJarsSold(salsaNames);
	}

	//Get the highest and lowest number of jars sold
	int lowestAmountSold = getLowestSold(numberOfJarsSold, number);
	int highestAmountSold = getHighestSold(numberOfJarsSold, number);

	//Display the jars sold, total jars sold and the highest and lowest 
	displayJarsSold(numberOfJarsSold, salsaNames, lowestAmountSold, highestAmountSold, number);

	return 0;
}

int getJarsSold(string names[]) {

	//Variables
	int jars; //Holds the value of jars sold
	static int i = 0;

	//Getting the number of jars sold per typw
	cout << "Enter the number of jars sold for " << names[i] << ":";
	cin >> jars;

	//Input validation
	while (jars < 0) {
		cout << "ERROR: Please enter a positive value";
		cout << "Enter the number of jars sold for " << names[i] << ":";
		cin >> jars;
	}
	i++;

	return jars;
}

int getLowestSold(int jars[], int numElements) {

	//Variables
	int returnValue = jars[0]; //Holds the lowest value
	int i = 1;

	//While loop to compare one element to another
	while (i < numElements) {

		int compare = jars[i];

		if (returnValue < compare) {
			returnValue = compare;
		}
		i++;
	}
	
	//lowest value in the array is returned
	return returnValue;
}

int getHighestSold(int jars[], int numElements) {

	//Variables
	int returnValue = jars[0]; //Holds the highest value
	int i = 1;
	
	//While loop to compare two elements and determine the highest
	while (i < numElements) {
		int compare = jars[i];
		if (returnValue > compare) {
			returnValue = compare;
		}
		i++;
	}

	//Return the highest value in the arry
	return returnValue;
}

void displayJarsSold(int jars[], string names[], int highest, int lowest, int numElements) {

	//Variables
	int totalSales = 0; //Holds the total sales of all jars sold
	int i = 0;

	cout << "Sales for Each Type" << "\n----------------" << endl;

	//While loop to print out the number of jars sold per type
	while (i < numElements) {

		int value = jars[i];

		cout << names[i] << ": ";
		cout << value << endl;
		i++;
	}

	i = 0;

	//loop to add up the total number of sales
	while (i < numElements) {
		totalSales = jars[i] += totalSales;
		i++;
	}

	//Prints out the total sales, lowest type sold, and highest type sold
	cout << "Total Sales: " << totalSales << endl;
	cout << "The Lowest Amount Sold: " << lowest << endl;
	cout << "The Highest Amount Sold: " << highest << endl;

}

