/*
* Carl Markowski
* CS2060 TTH
* OS: Windows
* HW:3 B
* Due: 02/15/2022
* This program will display my understanding of control structures 
* and my ability to write a simple code in C
*/

//Preprocessor Directives
#include <stdio.h>
#include <stdbool.h>

void calculateTotals(void);

int main(void) {

	//Print statements to "open" the board shop
	printf("%s", "Welcome to Markowski's Board Shop!!");
	printf("%s", "\nWe have boards for rental starting at $35 for 2 hours.");
	printf("%s", "\nEvery hour after 2 is an additional $10, for up to 10 hours!");

	//Calling the calculateTotals function
	calculateTotals();

}//End of main

void calculateTotals(void) {

	//Declared and initialized variables
	unsigned int boards = 0;
	double amount = 0, hours = 0, userInput = 0;
	double totalHours = 0;
	double totalSum = 0;
	


	while (userInput != -1) {

		//Simple print statement and scanf to capture input
		//"while" to clear buffer
		printf("%s", "\nEnter the number of hours the board was rented for or -1 to quit : ");
		scanf("%lf", &userInput);
		while ((getchar() != '\n'));

			//If statement to check valid input and make variables equal to
			//necessary values
			if (userInput != -1 && userInput < 0 || userInput > 10) {
				printf("%s", "Invalid Entry.Please enter the number of hours the board was rented for.");
			}
			else if (userInput > 0 && userInput <= 2) {
				amount = 35;
				hours = userInput;
				boards++;
			}
			else if (userInput > 2 && userInput <= 3) {
				amount = 45;
				hours = userInput;
				boards++;
			}
			else if (userInput > 3 && userInput <= 4) {
				amount = 55;
				hours = userInput;
				boards++;
			}
			else if (userInput > 4 && userInput <= 5) {
				amount = 65;
				hours = userInput;
				boards++;
			}
			else if (userInput > 5 && userInput <= 10) {
				amount = 75;
				hours = userInput;
				boards++;
			}
			else if (userInput == -1 && boards == 0) {
				printf("%s\n", "No boards were rented");
			}
			else if (userInput == -1) {
				amount = 0;
				hours = 0;
			}
			else {
				printf("%s", "Invalid Entry. Please enter the number of hours the board was rented.");
			}

			//Adding together total sum and total hours for the display
			totalSum = amount + totalSum;
			totalHours = hours + totalHours;

		}//End of while loop

	//Displaying the information from the while loop
	printf("%s\n", "Total for the day");
	printf("%s", "Boards: ");
	printf("%d\n", boards);
	printf("%s", "Total Hours: ");
	printf("%.2f\n", totalHours);
	printf("%s", "Total Charge: ");
	printf("%.2f\n", totalSum);
	
}//End of calculateTotal function

