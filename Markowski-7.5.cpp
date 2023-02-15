/*
Carl Markowski
CS 3060 7.5
This program will utilize 2D arrays to store certain values
*/

#include <iostream>
#include <iomanip>

using namespace std;

//Function Prototypes
int getMonkeyInfo(int, int);
double getAvgFoodEaten(int[][5], int, int);
int getLeastAmountEaten(int[][5], int, int);
int getHighestAmountEaten(int[][5], int, int);
void displayInfo(double, int, int);


int main() {
	
	//Variables
	int monkeyArray[3][5];//2D Array
	double avgEaten = 0; //Holds the avg amount of food eaten
	int lowestEaten = 0; //Holds the lowest amount of food eaten
	int highestEaten = 0; //Holds the highest amount of food eaten
	int rows = 3; //holds the number of rows
	int cols = 5; //holds the number of columns



	//Get the monkey information
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			monkeyArray[row][col] = getMonkeyInfo(row, col);
		}
	}
	
	//Get the avg amount of food eaten
	avgEaten = getAvgFoodEaten(monkeyArray, rows, cols);

	//Get the least amount of food eaten
	lowestEaten = getLeastAmountEaten(monkeyArray, rows, cols);

	//Get the highest amount of food eaten
	highestEaten = getHighestAmountEaten(monkeyArray, rows, cols);

	//Display the information needed
	displayInfo(avgEaten, lowestEaten, highestEaten);

	return 0;
}

int getMonkeyInfo(int monkey, int day) {
	
	//Variables
	int i = 0; //Iterates through rows
	int j = 0; //Iterates through cols
	int returnValue = 0; //Returns the amount of food eaten

	//Gets the amount of food eaten per monkey
	cout << "Enter the amount of food eaten by monkey " << monkey + 1 << " on day " << day + 1 << ":" << endl;
	cin >> returnValue;

	//Input Validation
	while (returnValue < 0) {
		cout << "ERROR: Please enter a positive value.\n";
		cout << "Enter the amount of food eaten by monkey " << monkey + 1 << " on day " << day + 1 << ":" << endl;
		cin >> returnValue;
	}

	return returnValue;
}

double getAvgFoodEaten(int monkey[][5], int row, int col) {

	//Variables
	double totalDays = row * col; //Holds the number of total days
	double totalFood = 0; //Holds the total amount of food
	double returnValue = 0; //Returns the avg amount of food eaten by all the monkeys

	//Iterates through the 2D array and totals the amount of food eaten
	for (int rows = 0; rows < row; rows++){
		for (int cols = 0; cols < col; cols++) {
			double food = monkey[rows][cols];
			totalFood = food += totalFood;
		}
	}

	//Sets returnValue equal to the avg (food/days)
	returnValue = totalFood / totalDays;

	return returnValue;
}

int getHighestAmountEaten(int monkey[][5], int rows, int cols) {

	//Variables
	int row = 0; //Iterates through the rows
	int col = 0; //Iterates through the cols
	int returnValue = 0; //Holds the highest value

	//Iterates through the 2D array and finds the highest amount eaten
	for (row = 0; row < rows; row++) {
		for (col = 0; col < cols; col++) {
			int compare = monkey[row][col];

			if (compare > returnValue) {
				returnValue = compare;
			}
		}
	}

	return returnValue;
}

int getLeastAmountEaten(int monkey[][5], int rows, int cols) {

	//Variables
	int row = 0; //Iterates through the rows
	int col = 0; //Iterates thrugh the cols
	int returnValue = monkey[0][0]; //Holds the least amount eaten

	//Iterates through the 2D array to find the lowest amount eaten
	for (row = 0; row < rows; row++) {
		for (col = 0; col < cols; col++) {
			int food = monkey[row][col];

			if (returnValue > food) {
				returnValue = food;
			}
		}
	}
	return returnValue;
}

void displayInfo(double avg, int lowest, int highest) {

	//
	cout << "Monkey Food Report\n" << "---------------" << endl;
	cout << "The average amount of food eaten was: " << avg << endl;
	cout << "The lowest amount of food eaten was: " << lowest << endl;
	cout << "The highest amount of food eaten was: " << highest;
	
}