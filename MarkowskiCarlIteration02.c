/*
Carl Markowski
CS2060 TTH
Iteration 02
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define PIN_ENTRIES 4
#define MAX_PIN 5
#define MAX_LENGTH 20
#define MAX_CHARITY_LENGTH 5
#define MAX_FILE_LENGTH 120
#define MAX_ZIPCODE 99999
#define MIN_ZIPCODE 00000
#define PACKAGES "Single Pack (1), Double Pack (2), Triple Pack (3), Family Pack (4): "

//Seat structure
//name is used to store the name
//price is used to store the price of the seat
//seatIndex is used to hold the "index" of the linked list
//salesIndex is used to track the total number of tickets sold
//nextPtr points to the next node in the linked list
typedef struct Seat {
	char name[MAX_LENGTH];
	double price;
	char seatIndex;
	int salesIndex;
	struct Seat* nextPtr;
}Seat;

//Function Prototypes
bool isPinValid(int pinEntries);
bool adminSetup(double* percent, Seat** headPtr);
bool adminSummary(Seat* headPtr, double charPercent, int sales[]);
void setupValues(Seat** seatPtr);
void buildSeatList(Seat** headPtr, char name[], double price, int index);
char verifySelection();
char getSeatLevel(Seat* headPtr);
void getString(char* inputStringPtr);
bool validateZipCode(double zipCode, char* endPtr);
bool validateSeatPrice(const double price, char* endPtr);
double setUpCharity(double* percent);
void printLinkedList(Seat* headPtr);
int getNumberOfSeats(Seat* headPtr);
int packageChoice(const int packages[]);
void getPayment(const double min, const double max);
void customerReceipt(Seat* headPtr, double percent, int packageIndex, double selectedSeatPrice, char selectedSeat);
void createFilePath(char* filePath, const char* path, const char* name);
void writeToAdminSummary(const char* path, Seat* headPtr, double charPercent, int sales[]);
void appendCustomerReceipt(const char* path, Seat** headPtr, double percent, int packageIndex, double customerTotal
	, char selectedSeat);



//Constant Variables
const double CORRECT_PIN = 4932;
const double MIN_MAX_SEAT_PRICE[] = { 10, 500 };
const double CHARITY_MIN_MAX[] = { 10, 30 };
const int PACKAGE_OPTIONS[] = { 1,2,3,4 };
const char FILE_PATH[] = { "D:\\Carl\\Microsoft Visual Studio\\CS2060Projects\\BookExamples\\BookExamples\\TicketSales\\"};
const char ADMIN_FILE[] = { "AdminSummary.txt" };
const char RECIEPT_FILE[] = { "receipt.txt" };


int main(void) {

	Seat* headPtr = NULL;
	double percent = 0;
	bool sellingMode = true;
	bool adminBool = false;
	
	//boolean set to see if adminSetup completes
	bool didAdminSetup = adminSetup(&percent, &headPtr);
	int seatSales[MAX_CHARITY_LENGTH] = {0};


	while(sellingMode == true){

		//if the admin did setup
		//Print out the available seats
		if (didAdminSetup == true) {
			printf("\n%s", "Welcome to the Ticket Sales Module.");
			printLinkedList(headPtr);
			printf("\nPercentage going to charity is %.2lf !!", percent);

			//Get the user's seat choice
			char selectedSeat = getSeatLevel(headPtr);

			//if 'Q' is entered then run the adminSummary
			//if the admin does not enter the pin correctly, continue in sales mode
			if (selectedSeat == 'Q') {
				//get pin and run summary
				adminBool = adminSummary(headPtr, percent, seatSales);

				//If admin didn't enter the correct pin, continue in sales mode
				if (adminBool == false) {
					sellingMode = true;
				}
				//else end sales mode and write the summary to the ADMIN_FILE
				else {
					sellingMode = false;

					char finalPath[MAX_FILE_LENGTH];
					createFilePath(finalPath, FILE_PATH, ADMIN_FILE);
					writeToAdminSummary(finalPath, headPtr, percent, seatSales);
				}
			}
			//If 'Q' was not entered, finish the sale
			else {

				//Get the package choice from the user
				int packageIndex = packageChoice(PACKAGE_OPTIONS);


				//index through the linked list to find the price needed for the calculations
				//and when the correct seat level node is located, use the currentPtr->salesIndex to add the 
				//package choices together for the total sales
				double selectedSeatPrice = 0;
				Seat* currentPtr = headPtr;
				bool seatPriceFound = false;

				while (seatPriceFound != true) {
					if (currentPtr->seatIndex == selectedSeat) {
						selectedSeatPrice = currentPtr->price;
						seatSales[currentPtr->salesIndex] = packageIndex + seatSales[currentPtr->salesIndex];
						seatPriceFound = true;
					}
					else {
						currentPtr = currentPtr->nextPtr;
					}
				}
				//getPayment called to receive the "payment" from the user
				getPayment(MIN_ZIPCODE, MAX_ZIPCODE);

				//customerReceipt called to print out a reciept if wanted
				customerReceipt(headPtr, percent, packageIndex, selectedSeatPrice, selectedSeat);
			}
		}
		else if (didAdminSetup == false) {
			sellingMode = false;
			printf("\n%s", "You have not entered the correct pin within 4 attempts.\nGoodBye.");
		}
	}
}//main

//adminSetup verifies that all the seats and the charity percentage have been setup
//percent is the charity percent
//HeadPtr is the pointer to the head of the linked list
//returns true if the pin is valid, the seat levels have been setup, and the
//charity percentage has been setup 
bool adminSetup(double* percent, Seat** headPtr) {

	bool validPin = false;
	bool returnValue = false;
	bool whileCondition = false;
	double* percentPTR = percent;

	//do while loop to get valid pin entry
	do {

		validPin = isPinValid(PIN_ENTRIES);

		//if the pin was valid, call the setupValues function
		if (validPin == true) {
			printf("%s", "Access Granted\n");
			setupValues(headPtr);
			
			//When the admin is done setting up the seats, call setupCharity
			*percent = setUpCharity(percentPTR);
			returnValue = true;
			whileCondition = true;
			
		}
		//If the pin as not entered correctly in 4 attempts
		//set the return to false and the while condition to true
		else {
			returnValue = false;
			whileCondition = true;
		}
	} while (whileCondition != true);

	return returnValue;
}//adminSetup


//isPinValid checks to see if the pin was entered correctly
//pinEntries is the number of times the pin can be entered
//Returns a boolean based on whether or not the pin was entered
//in the correct amount of times
bool isPinValid(int pinEntries) {
	bool returnValue = false;
	char entry[MAX_PIN];
	char* ptr = NULL;
	long int pinEntry = 0;
	int numEntries = 0;

	//Gets the pin from the admin and validates it
	do {

		//Gets the pin entry from the admin
		printf("%s", "Please enter the four digit pin: ");
		fgets(entry, MAX_PIN, stdin);
		while ((getchar() != '\n'));
	
		//converts the char to a long int
		pinEntry = strtol(entry, &ptr, 10);

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
}//isPinVaild


//setupValues is a function that gets the names and prices for the seat levels
//from the admin and then calls the buildSeatList function to create the seat linked list
//seatPtr is a double pointer to receive the headPtr from the main
//No return value
void setupValues(Seat** seatPtr) {

	char verifiedSelection = 'Y';
	char name[MAX_LENGTH];
	char pricePtr[MAX_LENGTH];
	char* endPtr = NULL;
	double price;
	int index = 0;
	bool priceFlag = false;

	//Prompt admin for the names of the seats
	printf("%s\n", "Enter the names and prices for the different seat levels");
	printf("WARNING- Seat prices have a range from %.2lf to %.2lf.\n", MIN_MAX_SEAT_PRICE[0], MIN_MAX_SEAT_PRICE[1]);

	while (verifiedSelection != 'N') {
		
		//Get the name of the seat from admin
		printf("%s", "Please enter the name of the seat: ");
		getString(name);

		do {
			//Get the price of the seat from admin
			printf("%s\n", "Please enter the price of this seat: ");
			getString(pricePtr);

			//convert the string to a double 
			price = strtod(pricePtr, &endPtr);

			//priceflag is a boolean that is true or false based on the return of validateSeatPrice
			priceFlag = validateSeatPrice(price, endPtr);
		} while (priceFlag != true);

			//buildSeatList builds the seat linked list
			buildSeatList(seatPtr, name, price, index);

			index++; 

			//Ask admin if they would like to add another seat
			printf("%s", "Would you like to add another seat? Y or N: ");
			verifiedSelection = verifySelection();
	}
}//setupValues


//verifySelection is a function that asks the user if yes or no 
//returns the character that the user entered
char verifySelection() {

	char selection = 'N';
	char returnValue = 'N';
	bool validInput = false;

	//Gets 'Y' or  'N' from user and checks for valid input
	do {
		selection = getchar();
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
}//verifySelection


//buildSeatList constructs the linked list for the seats to be stored in
//headPtr is the head of the linked list
//name[] is the char array that contains the string for the name of the seat from the admin
//price is the price entered by the admin for the seat
void buildSeatList(Seat** headPtr, char name[], double price, int index) {

	//Dynamically allocate memory for the new seat
	Seat* newSeatPtr = malloc(sizeof(Seat));

	//If it was created then assign the values to the new seat
	if (newSeatPtr != NULL) {
		strcpy(newSeatPtr->name, name);
		newSeatPtr->price = price;
		newSeatPtr->seatIndex = name[0];
		newSeatPtr->salesIndex = index;
		newSeatPtr->nextPtr = NULL;

		//if head is null then assign the newSeatPtr to be the head
		if (*headPtr == NULL) {
			*headPtr = newSeatPtr;
		}
		//else, create a currentPtr to hold the head value and 
		//check if currentPtr's nextPtr is null
		else {
			Seat* currentPtr = *headPtr;
			//If it is not null then currentPtr set currentPtr to the nextPtr 
			while (currentPtr->nextPtr != NULL) {
				currentPtr = currentPtr->nextPtr;
			}
			//when currentPtr is not null, assign newSeatPtr to be the nextPtr
			currentPtr->nextPtr = newSeatPtr;
		}
	}
	else {
		printf("No memory to create %s", name);
	}
}//buildSeatList


//getString is a function that gets input from the user using fgets()
//No return value
void getString(char* inputStringPtr) {

		fgets(inputStringPtr, MAX_LENGTH, stdin);
		inputStringPtr[0] = toupper(inputStringPtr[0]);
	//if the string gotten from stdin has a new line character at the end of the input
	//then change it to a \0
	if (inputStringPtr[strlen(inputStringPtr) - 1] == '\n')
	{
		inputStringPtr[strlen(inputStringPtr) - 1] = '\0';
	}
}//getString


//validateZipCode is a function that is used to validate the zip code entered
//buff is the string gotten from the user
bool validateZipCode(double zipCode, char *endPtr) {


	bool returnValue = false;
	errno = 0;

	if (*endPtr != '\0') {
		returnValue = false;
	}
	else if ((zipCode < MIN_ZIPCODE) || (zipCode > MAX_ZIPCODE)) {
		returnValue = false;
	}
	else {
		returnValue = true;
	}

	return returnValue;

}//validateZipCode


//validateSeatPrice is a function that validates the seat price entered by the admin
//price is the amount entered 
//endPtr is the last character of the entry
//return is based on whether or not the price entered is valid
bool validateSeatPrice(const double price, char* endPtr) {

	bool returnValue = false;

	//if price is larger than the max or smaller than the min
	//set returnValue to false
	if (price > MIN_MAX_SEAT_PRICE[1] || price < MIN_MAX_SEAT_PRICE[0]) {
		returnValue = false;
	}
	//if endPtr does not equal \0
	//set returnValue to false
	else if (*endPtr != '\0') {
		returnValue = false;
	}
	//else returnValue equals true
	else {
		returnValue = true;
	}

	return returnValue;
}//validateSeatPrice


//setUpCharity is a function that setups the charity percentage
double setUpCharity(double* percent) {

		char setCharity[MAX_CHARITY_LENGTH];
		char* endPtr = NULL;
		bool validInput = false;
		double returnValue = 0;

		//Do while loop to setup the charity percent and validate the input 
		do {
			printf("%s\n", "Please enter the percentage going to charity");
			printf("WARNING: The charity percentage has a range of %.2lf and %.2lf\n", CHARITY_MIN_MAX[0], CHARITY_MIN_MAX[1]);
			getString(setCharity);

			returnValue = strtod(setCharity, &endPtr);

			//if the amount entered is in the range than return exit the do while
			if (returnValue >= CHARITY_MIN_MAX[0] && returnValue <= CHARITY_MIN_MAX[1]) {
				validInput = true;
			}
			else {
				validInput = false;
			}

		} while (validInput == false);
		return returnValue;
}//setUpCharity


//printLinkedlist is a function to print out the seat linked list
void printLinkedList(Seat* headPtr) {

	//set a current pointer to the headptr
	Seat* current = headPtr;

	//while current is not null, print the seat name and price
	while (current != NULL) {
		printf("\nSeat Level: %s", current->name);
		printf(" and Price: %.2lf", current->price);
		current = current->nextPtr;
	}
}//printLinkedlist

//getSeatLevel is a function to get the seat level choice from the user
//headPtr is to get the head of the seat linked list from main
char getSeatLevel(Seat* headPtr) {

	char seatLevel[MAX_LENGTH];
	char returnValue = 'N';
	char verifiedSelection = 'N';
	bool whileCondition = false;

	//Do- while loop continues to loop through if 'N' is chosen in the verifySelection function
	do {
		//Get the name of the seat from the user
		printf("\n%s", "Please enter the name of the seat you would like for the game: ");
		getString(seatLevel);

		bool seatFound = false;
		Seat* currentPtr = headPtr;
		int numberOfSeats = getNumberOfSeats(headPtr);
		int index = 0;

		if (seatLevel[0] == 'Q') {
			returnValue = seatLevel[0];
			whileCondition = true;
		}
		else {
			//While the seat has not been found in the list
			while (index != numberOfSeats) {

				//if string compare comes back equal (0)
				//set the returnValue to the first letter of the string
				//and set seatFound boolean to true
				if (strcmp(currentPtr->name, seatLevel) == 0) {
					returnValue = seatLevel[0];
					seatFound = true;
				}
				//else set currentPtr to its nextPtr
				else {
					currentPtr = currentPtr->nextPtr;
				}
				index++;
			}

			//if the seat has been found in the linked list
			//then ask the customer if that is what they want
			if (seatFound == true) {
				//verifies the customers selection using the verifySelection function
				printf("Is %s for %.2lf the correct seat? Y or N?", currentPtr->name, currentPtr->price);
				verifiedSelection = verifySelection();
			}
			//if the seat was not in the linked list than
			//set the whileCondition to false
			else {
				printf("%s", "That seat name has not been found");
			}

			//if verifiedSelection was yes than set the while condition to true
			if (verifiedSelection == 'Y') {
				whileCondition = true;
			}
			else {
				whileCondition = false;
			}
		}
	} while (whileCondition != true);
	return returnValue;
}//getSeatLevel

//getNumberOfSeats is a function that gets the number of seats in the linked list
//headPtr is a pointer to recieve that head of the linked list
int getNumberOfSeats(Seat* headPtr) {

	int size = 0;

	Seat* current = headPtr;

	while (current != NULL) {
		current = current->nextPtr;
		size++;
	}
	return size;
}

//adminSummary is a function used to display the total amount of sales if the 
//correct pin is entered
//headPtr is a pointer to the linked list
//charPercent is the percentage going to charity
//sales[] is the amount of seats sold in each category
bool adminSummary(Seat* headPtr, double charPercent, int sales[]) {

	bool validPin = false;
	double salesTotal = 0;
	double charityTotal = 0;
	bool returnValue = false;
	validPin = isPinValid(PIN_ENTRIES);

	//If the admin entered the correct pin, print out the following pieces of info
	if (validPin == true) {

		Seat* currentPtr = headPtr;
		int index = 0;

		printf("%s\n", "------------------------------------------------------------------");
		printf("\t\t%s\n", "DENVER NUGGETS TICKET SUMMARY");
		printf("%s\n", "------------------------------------------------------------------");

		printf("%s", "Level\t\tPrice\t\tSold\t\tSales Total\tCharity Total");

		//For loop to go through each index of the arrays and print out the information
		while (currentPtr != NULL) {
			salesTotal = currentPtr->price * sales[index];
			charityTotal = salesTotal * (charPercent / 100);
			printf("\n%s\t\t", currentPtr->name);
			printf("%.2lf\t\t", currentPtr->price);
			printf("%d\t\t", sales[index]);
			printf("%.2lf\t\t", salesTotal);
			printf("%.2lf\t\t", charityTotal);
			printf("%s", "\n");
			currentPtr = currentPtr->nextPtr;
			index++;
		}
		double totalSales = 0;
		double totalDonation = 0;
		currentPtr = headPtr;
		index = 0;

		//For- loop used to total up the sales and charity donation
		while (currentPtr != NULL) {
			double salesTotal = currentPtr->price * sales[index];
			double charityTotal = salesTotal * (charPercent / 100);
			totalSales = salesTotal + totalSales;
			totalDonation = charityTotal + totalDonation;
			currentPtr = currentPtr->nextPtr;
			index++;
		}
		printf("\nTotal Sales: %.2lf\n", totalSales);
		printf("Total Charity Donation: %.2lf\n", totalDonation);

		returnValue = true;
	}
	else {
		returnValue = false;
	}

	return returnValue;
}//adminSummary


//packageChoice prompts the user for the package they would like to purchase 
//packages[] is an array with the possible packages to buy
//returns the package selection (1,2,3,4)
int packageChoice(const int packages[]) {

	static long int packageSelection = 0;
	char package[MAX_LENGTH];
	char* endPtr = NULL;
	int returnValue = 0;
	char verifiedSelection = 'N';

	printf("Package Choices are: %s\n", PACKAGES);

	//Gets the package selection from the user with a do-while loop
	do {
		printf("%s", "Please choose the type of package you would like:");
		getString(package);
		
		packageSelection = strtol(package, &endPtr, MAX_LENGTH);

		if (packageSelection == 0 || packageSelection > 4) {
			printf("%ld is an invalid selection.", packageSelection);
			verifiedSelection = 'N';
		}
		else {

			//Checks the packages array to verify which one was selected
			for (unsigned int i = 0; i < sizeof(packages); i++) {
				if (packageSelection == i + 1) {
					returnValue = packages[i];
				}
			}
			printf("Is %ld the correct selection? (Y)es or (N)o: \n", packageSelection);
			verifiedSelection = verifySelection();
		}

	} while (verifiedSelection == 'N');

	return returnValue;
}//packageChoice

//getPayment is a function that prompts the user for their zip code to pay for the tickets
//min is the low end of the range for an acceptable zip code
//max is high end of the range for an acceptable zip code
//No return Value
void getPayment(const double min, const double max) {
	
	char enteredZip[MAX_LENGTH];
	char* endPtr = NULL;
	double zipCode = 00000;
	bool validInput = false;

	//ask the user for their zip code while the input is NOT valid
	do {
		printf("%s\n", "Please enter your Zip Code to pay for you tickets: ");
		getString(enteredZip);
		
		zipCode = strtod(enteredZip, &endPtr);

		//If validateZipCode sends back false, print error message
		//and set validInput flag to false
		if (validateZipCode(zipCode, endPtr) == false) {
			printf("%s\n", "Invalid Zip Code");
			validInput = false;
		}
		else {
			validInput = true;
		}
	} while (validInput == false);
}//getPayment

//customerReceipt is a function that prompts the customer if they would like a receipt 
//headPtr is the pointer to the head of the linked list
//percent is the charity percentage set by the admin
//packageIndex is the number of tickets that was requested by the customer
//selectedSeatPrice is the price associated to the seat chosen by the customer
//selectedSeat is the reference to teh seat chosen 
//No return value
void customerReceipt(Seat* headPtr, double percent, int packageIndex, double selectedSeatPrice, char selectedSeat) {

	//Calculations for the customers total
	double customerTotal = selectedSeatPrice * packageIndex;

	//Asking the customer if they would like a receipt
	char selection = 'N';
	printf("%s", "Would you like a receipt for your purchase? (Y)es or (N)o?");
	selection = verifySelection();

	//Getting the correct seat name from the list
	Seat* currentPtr = headPtr;
	bool seatFound = false;
	char name[MAX_LENGTH];

	//while the correct has not been found
	while (seatFound != true) {
		//if the selected seat matches the seatIndex
		//copy the name from currentPtr to the name array
		if (currentPtr->seatIndex == selectedSeat) {
			strcpy(name, currentPtr->name);
			seatFound = true;
		}
		//Else make the currentPtr equal to its nextPtr
		else {
			currentPtr = currentPtr->nextPtr;
		}
	}

	//If customer selects yes, print out the following pieces of info
	if (selection == 'Y') {
		printf("\n%s", "Denver Nuggest Charity Ticket Receipt");
		printf("\nSeat Level: %s", name);
		printf("\nPackage: %d", packageIndex);
		printf("\nTotal Cost: %.2lf", customerTotal);
		printf("\nDonation To Charity: %.2lf\n", customerTotal * (percent / 100));

		char path[MAX_FILE_LENGTH];
		createFilePath(path, FILE_PATH, RECIEPT_FILE);
		appendCustomerReceipt(path, &headPtr, percent, packageIndex, customerTotal, selectedSeat);
	}
	else;
}//customerReceipt

//createFilePath creates the necessary path for the file wanted
//filePath is the path being created
//path is the const file path value
//name is the name of the file
void createFilePath(char* filePath, const char* path, const char* name) {

	size_t length = 0;
	strcpy(filePath, path);
	length = strlen(filePath);
	strncat(filePath, name, length);

}//createFilePath

//writeToAdminSummary is a function that prints the total sales to the Admin summary file
//path is the file path to be opened
//headPtr is a pointer to the head of the linked list
//charPercent is the charity percentage setup by the admin
//sales[] is an array that holds the total number of sales for each seat
void writeToAdminSummary(const char* path, Seat* headPtr, double charPercent, int sales[]) {

	FILE* adminFilePtr;

	//If adminFilePtr is not opened properly, print error message
	if ((adminFilePtr = fopen(path, "w")) == NULL) {
		printf("%s", "Admin summary file could not be opened");
	}
	//else, print the data to the file
	else {

		double salesTotal = 0;
		double charityTotal = 0;
		char sentence[MAX_FILE_LENGTH];
	
		Seat* currentPtr = headPtr;
		int index = 0;

		sprintf(sentence, "%s\n", "----------------------------------------------------------------------------------");
		fputs(sentence, adminFilePtr);
		sprintf(sentence, "\t%s\n", "DENVER NUGGETS TICKET SUMMARY");
		fputs(sentence, adminFilePtr);
		sprintf(sentence, "%s\n", "----------------------------------------------------------------------------------");
		fputs(sentence, adminFilePtr);

		sprintf(sentence, "%s", "Level\t\tPrice\t\tSold\t\tSales Total\t\tCharity Total");
		fputs(sentence, adminFilePtr);

		while (currentPtr != NULL) {

			//For loop to go through each index of the arrays and print out the information
			salesTotal = currentPtr->price * sales[index];
			charityTotal = salesTotal * (charPercent / 100);
			sprintf(sentence, "\n%s\t\t", currentPtr->name);
			fputs(sentence, adminFilePtr);
			sprintf(sentence, "%.2lf\t\t", currentPtr->price);
			fputs(sentence, adminFilePtr);
			sprintf(sentence, "%d\t\t", sales[index]);
			fputs(sentence, adminFilePtr);
			sprintf(sentence, "%.2lf\t\t", salesTotal);
			fputs(sentence, adminFilePtr);
			sprintf(sentence, "%.2lf\t\t", charityTotal);
			fputs(sentence, adminFilePtr);
			sprintf(sentence, "%s", "\n");
			fputs(sentence, adminFilePtr);
			currentPtr = currentPtr->nextPtr;
			index++;

		}
			double totalSales = 0;
			double totalDonation = 0;
			currentPtr = headPtr;
			index = 0;

			while (currentPtr != NULL) {
				double salesTotal = currentPtr->price * sales[index];
				double charityTotal = salesTotal * (charPercent / 100);
				totalSales = salesTotal + totalSales;
				totalDonation = charityTotal + totalDonation;
				currentPtr = currentPtr->nextPtr;
				index++;
			}
			sprintf(sentence,"\nTotal Sales: %.2lf\n", totalSales);
			fputs(sentence, adminFilePtr);
			sprintf(sentence,"Total Charity Donation: %.2lf\n", totalDonation);
			fputs(sentence, adminFilePtr);
			fclose(adminFilePtr);
	}
}//writeToAdminSummary

//appendCustomerReciept is a function that will append a reciept to a file everytime the customer wants a receipt
//path is the file path needed to write to the file
//headPtr is the pointer to the linked list
//percent is the charity percentage setup by the admin
//packageIndex is the package selected by the customer
//selectedSeatPrice is the price of the seat that was selected by the customer
//selectedSeat is the seat that was selected 
void appendCustomerReceipt(const char* path, Seat** headPtr, double percent, int packageIndex, double customerTotal
	, char selectedSeat) {

	FILE* receiptPtr;

	if ((receiptPtr = fopen(path, "a")) == NULL) {
		printf("%s", "Customer Reciept file could not be opened.");
	}
	else {
		//Getting the correct seat name from the list
		Seat* currentPtr = *headPtr;
		bool seatFound = false;
		char name[MAX_LENGTH];
		char sentence[MAX_FILE_LENGTH];

		//while the correct has not been found
		while (seatFound != true) {
			//if the selected seat matches the seatIndex
			//copy the name from currentPtr to the name array
			if (currentPtr->seatIndex == selectedSeat) {
				strcpy(name, currentPtr->name);
				seatFound = true;
			}
			//Else make the currentPtr equal to its nextPtr
			else {
				currentPtr = currentPtr->nextPtr;
			}
		}

		//If customer selects yes, print out the following pieces of info
			sprintf(sentence,"\n%s", "Denver Nuggest Charity Ticket Receipt");
			fputs(sentence, receiptPtr);
			sprintf(sentence,"\nSeat Level: %s", name);
			fputs(sentence, receiptPtr);
			sprintf(sentence,"\nPackage: %d", packageIndex);
			fputs(sentence, receiptPtr);
			sprintf(sentence,"\nTotal Cost: %.2lf", customerTotal);
			fputs(sentence, receiptPtr);
			sprintf(sentence,"\nDonation To Charity: %.2lf\n", customerTotal * (percent / 100));
			fputs(sentence, receiptPtr);

			fclose(receiptPtr);
	}
}//appendCustomerReceipt
