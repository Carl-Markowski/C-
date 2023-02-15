/*
Carl Markowski
CS 2060 TTH
Assignment 5
Due: 03/15/2022
This program will show my ability to pass variables and arrays by reference 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 3
#define PIN_ENTRIES 3

//Function prototypes
bool adminSetup(double prices[SIZE], double *percentPTR);
bool isPinValid(double pin);
void setupValues(double setPrices[SIZE], double *charPercent);
void printPrices(double seatPrices[SIZE], double charPercent);

//Constants
const char SEAT_LEVELS[] = {'C','M','U'};
const double CORRECT_PIN = 4932;

int main(void) {
	double seatPrices[SIZE];
	double charityPercent = 0;
	bool didAdminSetup = false;

	//Function call of adminSetup
	didAdminSetup = adminSetup(seatPrices, &charityPercent);
	if (didAdminSetup == true) {
		printf("%s", "Move on to sales mode\n");
		printPrices(seatPrices, charityPercent);
	}
	else;

}

//Function used to tell main if admin setup was successful
bool adminSetup(double prices[SIZE], double *percentPTR) {
	double pinEntry = 0;
	bool validPin = false;
	bool returnValue = false;
	int numEntries = 0;
	

	//do while loop to get valid pin entry
	do {
		numEntries++;
		printf("%s", "Please enter the four digit pin: ");
		scanf("%lf", &pinEntry);
		validPin = isPinValid(pinEntry);
		
		//if the pin was valid run value setup
		if (validPin == true) {
			printf("%s", "Access Granted\n");
			numEntries = 3;
			setupValues(prices, percentPTR);
			returnValue = true;
		}
		else {
			printf("%s", "Invaild Entry, ");
			returnValue = false;
		}
	} while (numEntries != PIN_ENTRIES);

	return returnValue;
}

//Function to validate pin
bool isPinValid(double pin) {
	bool returnValue = false;

		if (pin == CORRECT_PIN) {
			returnValue = true;
		}
		else {
			returnValue = false;
		}
	return returnValue;
}

//Function to setup the values of the seats ans charity percent
void setupValues(double setPrices[SIZE], double *charPercent) {
	double seatPrices = 0;
	double setCharity = 0;
	bool validInput = false;
	
	//Do while loop to setup the seat price and validate the input 
	do {
		printf("%s", "Please enter an amount for the (C)ourtside seats: ");
		scanf("%lf", &seatPrices);

		if (seatPrices > 200 && seatPrices <= 500) {
			setPrices[0] = seatPrices;
			validInput = true;
		}
		else {
			validInput = false;
		}
	} while (validInput == false);

	//Do while loop to setup the seat price and validate the input 
	do {
		printf("%s", "Please enter an amount for the (M)id Level seats: ");
		scanf("%lf", &seatPrices);

		if (seatPrices > 75 && seatPrices <= 200) {
			setPrices[1] = seatPrices;
			validInput = true;
		}
		else {
			validInput = false;
		}
	} while (validInput == false);
	
	//Do while loop to setup the seat price and validate the input 
	do {
		printf("%s", "Please enter an amount for the (U)pper Level seats: ");
		scanf("%lf", &seatPrices);

		if (seatPrices >= 10 && seatPrices <= 75) {
			setPrices[2] = seatPrices;
			validInput = true;
		}
		else {
			validInput = false;
		}
	} while (validInput == false);

	//Do while loop to setup the charity percent and validate the input 
	do {
		printf("%s", "Please enter the percentage going to charity: ");
		scanf("%lf", &setCharity);

		if (setCharity > 5 && setCharity <= 25) {
			charPercent = &setCharity;
			validInput = true;
		}
		else {
			validInput = false;
		}

	} while (validInput == false);
}

//function to print the seat prices and charity percent
void printPrices(double seatPrices[SIZE], double charPercent) {

	for (unsigned int i = 0; i < SIZE; i++) {
		printf("The price of %c", SEAT_LEVELS[i]);
		printf(" is: %.2lf\n", seatPrices[i]);
	}

	charPercent = charPercent / 100;
	printf("The percentage going to charity is: %.2lf", charPercent);
}