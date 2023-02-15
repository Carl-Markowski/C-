/*
Carl Markowski
CS 2060 TTH 
Iteration 01
March 29, 2022
This is the first iteration of the Ticket fundraiser
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 3
#define PIN_ENTRIES 3
#define NUMSEATS 4
#define PACKAGES "Single Pack (1), Double Pack (2), Triple Pack (3), Family Pack (4): "

//Function Prototypes
char getSeatLevel(size_t seats);
bool adminSetup(double prices[SIZE], double *percent);
bool isPinValid(int pinEntries);
void setupValues(double setPrices[SIZE]);
double setUpCharity(double *percent);
void printPrices(double seatPrices[SIZE], double charPercent);
bool adminSummary(double prices[], double charPercent, int sales[]);
char verifySelection();
int packageChoice(const int packages[]);
void getPayment(const double min, const double max);
void customerReceipt(char seat,int seatIndex, int package, double prices[], double charPercent);

//Const variables 
const char SEAT_LEVELS[] = { 'C','M','U','Q'};
const char *SEAT_NAMES[] = { "(C)ourtside", "(M)id", "(U)pper" };
const int PACKAGE_CHOICES[] = {1,2,3,4};
const double CORRECT_PIN = 4932;
const double ZIP_MIN = 11111;
const double ZIP_MAX = 99999;
const double SEATONE_MIN_MAX[] = { 200, 500 };
const double SEATTWO_MIN_MAX[] = { 75, 200 };
const double SEATTHREE_MIN_MAX[] = { 10, 75 };
const double CHARITY_MIN_MAX[] = { 5, 25 };


int main(void) {
	double seatPrices[SIZE];
	int seatSales[SIZE] = {0};
	double charityPercent = 0;
	bool didAdminSetup = false;
	bool sellingMode = true;
	bool adminBool = false;
	unsigned int numSeats = NUMSEATS;
	unsigned int packageIndex = 0;
	unsigned int seatLevelIndex = 0;

	//Function call of adminSetup
	didAdminSetup = adminSetup(seatPrices, &charityPercent);
	while (sellingMode == true) {

		if (didAdminSetup == true) {
			printf("\n%s", "Welcome to the Ticket Sales Module.");
			printf("\n%s", "The prices for the seats and the amount going to charity are: \n");
			printPrices(seatPrices, charityPercent);

			char seatLevel = getSeatLevel(numSeats);

			for (unsigned int i = 0; i < sizeof SEAT_LEVELS; i++) {
				if (seatLevel == SEAT_LEVELS[i]) {
					seatLevelIndex = i;
				}
			}

			if (seatLevel == 'Q') {
				//get pin and run summary
				adminBool = adminSummary(seatPrices, charityPercent, seatSales);
				sellingMode = false;

				if (adminBool == false) {
					sellingMode = true;
				}
			}
			else {
				//packageChoice called to get the number of tickets desired
				packageIndex = packageChoice(PACKAGE_CHOICES);

				//Sets the index of seatSales to the packageIndex so the total number of tickets sold will
				//be saved throughout the code
				for (unsigned int i = 0; i < SIZE; i++) {
					if (seatLevel == SEAT_LEVELS[i]) {
						seatSales[i] = seatSales[i] + packageIndex;
					}
				}

				//getPayment called to get the payment from the user
				getPayment(ZIP_MIN, ZIP_MAX);

				//customerReceipt called to print out receipt if wanted
				customerReceipt(seatLevel ,seatLevelIndex, packageIndex, seatPrices, charityPercent);
			}
		}
	}
}//End Main

//Function used to tell main if admin setup was successful
bool adminSetup(double prices[SIZE], double *percent){
	
	bool validPin = false;
	bool returnValue = false;
	bool whileCondition = false;
	double* percentPTR = percent;

	//do while loop to get valid pin entry
	do {
		
		validPin = isPinValid(PIN_ENTRIES);

		//if the pin was valid run value setup
		if (validPin == true) {
			printf("%s", "Access Granted\n");
			setupValues(prices);
			*percent = setUpCharity(percentPTR);
			returnValue = true;
			whileCondition = true;
		}
		else {
			returnValue = false;
			whileCondition = true;
		}
	} while (whileCondition != true);

	return returnValue;
}

//Function to validate pin
bool isPinValid(int pinEntries) {
	bool returnValue = false;
	double pinEntry = 0;
	int numEntries = 0;

	//Gets the pin from the admin and validates it
	do {

		printf("%s", "Please enter the four digit pin: ");
		scanf("%lf", &pinEntry);
		while ((getchar() != '\n'));

		//If pin is correct, return true and set the while condition to true
		if (pinEntry == CORRECT_PIN) {
			returnValue = true;
			numEntries = pinEntries;
		}
		//If the pin is incorrect, return false and set the while condition to false but increment the counter
		else {
			printf("%s", "Invalid Entry ");
			returnValue = false;
			numEntries++;
		}
	} while (numEntries != pinEntries);
	return returnValue;
}

//Function to setup the values of the seats ans charity percent
void setupValues(double setPrices[SIZE]) {
	double seatPrices = 0;
	bool validInput = false;

	//Do while loop to setup the seat price and validate the input 
	do {
		printf("%s", "Please enter an amount for the (C)ourtside seats: ");
		scanf("%lf", &seatPrices);
		while ((getchar() != '\n'));

		if (seatPrices > SEATONE_MIN_MAX[0] && seatPrices <= SEATONE_MIN_MAX[1]) {
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
		while ((getchar() != '\n'));

		if (seatPrices > SEATTWO_MIN_MAX[0] && seatPrices <= SEATTWO_MIN_MAX[1]) {
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
		while ((getchar() != '\n'));

		if (seatPrices >= SEATTHREE_MIN_MAX[0] && seatPrices <= SEATTHREE_MIN_MAX[1]) {
			setPrices[2] = seatPrices;
			validInput = true;
		}
		else {
			validInput = false;
		}
	} while (validInput == false);
}

//Function used to setup the charity percent 
double setUpCharity(double *percent) {
	double setCharity = 0;
	bool validInput = false;
	double returnValue = 0;

	//Do while loop to setup the charity percent and validate the input 
	do {
		printf("%s", "Please enter the percentage going to charity: ");
		scanf("%lf", &setCharity);
		while ((getchar() != '\n'));

		if (setCharity > CHARITY_MIN_MAX[0] && setCharity <= CHARITY_MIN_MAX[1]) {
			validInput = true;
			returnValue = setCharity;
		}
		else {
			validInput = false;
		}

	} while (validInput == false);
	return returnValue;
}

//function to print the seat prices and charity percent
void printPrices(double seatPrices[SIZE], double charPercent) {

	for (unsigned int i = 0; i < SIZE; i++) {
		printf("The price of %c", SEAT_LEVELS[i]);
		printf(" is: %.2lf\n", seatPrices[i]);
	}

	printf("The percentage going to charity is: %.0lf%%", charPercent);
}

//Function gets the seat choice from the user
char getSeatLevel(size_t seats) {

	char seatLevel = 'C';
	char returnValue = 'C';
	char verifiedSelection = 'N';
	bool whileCondition = false;

	//Do- while loop continues to loop through if 'N' is chosen in the verifySelection function
	do {
		printf("\n%s", "Please enter your seat level: (C)ourtside, (M)id, or (U)pper ");
		scanf("%c", &seatLevel);
		while ((getchar() != '\n'));

		//verifies the customers selection using the verifySelection function
		printf("Is %c the correct selection? (Y)es or (N)o? \n", seatLevel);
		verifiedSelection = verifySelection();

		//For-loop to check the seatLevel against the SEAT_LEVEL array
		for (unsigned int i = 0; i < seats; i++) {
			if (toupper(seatLevel) == SEAT_LEVELS[i]) {
				returnValue = SEAT_LEVELS[i];
				whileCondition = true;
			}
			else if (toupper(seatLevel) != SEAT_LEVELS[i]) {
				whileCondition = false;
			}
		}

		if (verifiedSelection == 'Y') {
			whileCondition = true;
		}
		else {
			whileCondition = false;
		}
	} while (whileCondition != true);


	return returnValue;
}

//Prints the summary of the purchases in sales mode if 'Q' is entered by the admin
bool adminSummary(double prices[], double charPercent, int sales[]) {

	bool validPin = false;
	double salesTotal = 0;
	double charityTotal = 0;
	bool returnValue = false;
	validPin = isPinValid(PIN_ENTRIES);

	//If the admin entered the correct pin, print out the following pieces of info
	if (validPin == true) {
		printf("%s", "Level\t\tPrice\t\tSold\t\tSales Total\t\tCharity Total");

		//For loop to go through each index of the arrays and print out the information
		for (unsigned int i = 0; i < SIZE; i++) {
			salesTotal = prices[i] * sales[i];
			charityTotal = salesTotal * (charPercent / 100);
			printf("\n%s\t\t", SEAT_NAMES[i]);
			printf("%.2lf\t\t", prices[i]);
			printf("%d\t\t", sales[i]);
			printf("%.2lf\t\t", salesTotal);
			printf("%.2lf\t\t", charityTotal);
			printf("%s", "\n");
		}
		double totalSales = 0;
		double totalDonation = 0;

		//For- loop used to total up the sales and charity donation
		for (unsigned int j = 0; j < SIZE; j++) {
			double salesTotal = prices[j] * sales[j];
			double charityTotal = salesTotal * (charPercent / 100);
			totalSales = salesTotal + totalSales;
			totalDonation = charityTotal + totalDonation;
		}
		printf("\nTotal Sales: %.2lf\n", totalSales);
		printf("Total Charity Donation: %.2lf\n", totalDonation);

		returnValue = true;
	}
	else {
		returnValue = false;
	}

	return returnValue;
}

//Function to verify if the customer meant to choose what they did
char verifySelection() {
	
	char selection = 'N';
	char returnValue = 'N';
	bool validInput = false;

	//Gets 'Y' or  'N' from user and checks for valid input
	do {
		scanf("%c", &selection);
		while ((getchar() != '\n'));

		if (toupper(selection) == 'Y') {
			returnValue = 'Y';
			validInput = true;
		}
		else if (toupper(selection) == 'N') {
			returnValue = 'N';
			validInput = true;
		}
		else {
			validInput = false;
		}
	} while (validInput == false);
	return returnValue;
}

//Function that gets the package choice from the user and calls the 
//verifySelection function to verify the selection
int packageChoice(const int packages[]) {

	static int packageSelection = 0;
	int returnValue = 0;
	char verifiedSelection = 'N';

	printf("Package Choices are: %s\n", PACKAGES);
	
	//Gets the package selection from the user with a do-while loop
	do {
		printf("%s", "Please choose the type of package you would like:");
		scanf("%d", &packageSelection);
		while ((getchar() != '\n'));

		//Checks the packages array to verify which one was selected
		for (unsigned int i = 0; i < sizeof packages;i++) {
			if (packageSelection == i + 1) {
				returnValue = packages[i];
			}
		}
		printf("Is %d the correct selection? (Y)es or (N)o: \n", packageSelection);
		verifiedSelection = verifySelection();

	} while (verifiedSelection == 'N');

	return returnValue;
}

//Function that receieves the "payment" from the user
void getPayment(const double min, const double max){

	double zipCode = 00000;
	bool validInput = false; 

	do {
		printf("%s", "Please enter your Zip Code to pay for you tickets: ");
		scanf("%lf", &zipCode);
		while ((getchar() != '\n'));

		//Checking for the min and max of the zip code and verifying it is in the range
		if (zipCode > min && zipCode < max) {
			validInput = true;
		}
		else {
			validInput = false;
		}

	} while (validInput == false);
}

//Function that will print out a receipt if customer wants one
void customerReceipt(char seat,int seatIndex, int package, double prices[], double percent) {

	double customerTotal = prices[seatIndex] * package;

	char selection = 'N';
	printf("%s", "Would you like a receipt for your purchase? (Y)es or (N)o?");
	selection = verifySelection();

	//If customer selects yes, print out the following pieces of info
	if (selection == 'Y') {
		printf("\n%s", "Denver Nuggest Charity Ticket Receipt");
		printf("\n%s", SEAT_NAMES[seatIndex]);
		printf("\n%d", package);
		printf("\nTotal Cost: %.2lf", customerTotal);
		printf("\nDonation To Charity: %.2lf\n", customerTotal * (percent / 100));
	}
	else;
}