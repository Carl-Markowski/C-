/*
Carl Markowski
CS2060 TTH 
Homework #7
Linked List 
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define MAX_NAME 100

//Pet structure 
typedef struct Pet {
	char petName[MAX_NAME];
	int age;
	struct Pet* nextPtr;
}Pet;

//Function Prototypes
void insertPet(Pet** petPtr, int age, char name[]);
void printLinkedList(Pet* headPtr);
bool removeLinks(Pet** headPtr, char name[]);
char wouldYouLikeToRemove(char input[]);
void sortPet(Pet* headPtr, Pet* newPetPtr);

int main(void) {

	Pet* headPTR = NULL;

	char name[MAX_NAME];
	int numberOfPets = 0;;
	int age = 0;
	

	//Getting how many pets need to be entered by the user
	printf("%s\n", "How many pets do you want to enter: ");
	scanf("%d", &numberOfPets);

	printf("Enter the name and age for %d pets: \n", numberOfPets);

	//For loop used to iterate through the names and ages
	for (int i = 0; i < numberOfPets; i++) {
		printf("%s", "Please enter a name: ");
		scanf("%s", name);
		while ((getchar() != '\n'));
		printf("%s", "Please enter an age: ");
		scanf("%d", &age);
		while ((getchar() != '\n'));
		insertPet(&headPTR, age, name);
	}

	//Prints out the linked list
	printf("%s\n", "These are the Pets: ");
	printLinkedList(headPTR);

	char input[2];
	char removeName[MAX_NAME];
	bool done = false;
	bool successfulRemove = false;

	//While loop used to loop through the list and remove the pets 
	while(done != true && headPTR != NULL){
		printf("%s", "Would you like to remove any pets? Y or N: ");
		//scanf("%s", input);
		fgets(input, 2, stdin);

		char returnValue = wouldYouLikeToRemove(input);

		//If the user wants to remove a pet 
		if (returnValue == 'Y') {

			//Getting the name to remove
			printf("%s", "Enter the name of the pet: ");
			scanf("%s", removeName);
			//fgets(removeName, sizeof removeName, stdin);
			while ((getchar() != '\n'));
			
			//Getting a boolean to verify that the link was removed or not 
			successfulRemove = removeLinks(&headPTR, removeName);

			//If the link was successfully removed
			if (successfulRemove == true) {
				printLinkedList(headPTR);
			}
			
			//Else the name to remove was not found
			else {
				printf("%s\n", "That name is not in the list");
			}

			done = false;
		}
		//Else if the user does not want to remove a pet
		else if (returnValue == 'N') {
			done = true;
		}
	}
}


//Function used to insert the new pet into the linked list
//Pet **petPtr is the headPTR being sent in
//Int age is the age of the pet
//name[] is the name entered by the user
void insertPet(Pet **petPtr, int age, char name[]) {
	Pet *petsPtr = malloc(sizeof(Pet));

	//Creating the new Pet by using strcpy to copy the name 
	//Setting the age to age and the nextPtr to null
	strcpy(petsPtr->petName, name);
	petsPtr->age = age;
	petsPtr->nextPtr = NULL;

	//If the head is NULL then make headPtr the new pet
	if (*petPtr == NULL) {
		*petPtr = petsPtr;
	}
	//Else iterate through the linked list and add the node in
		else {
		sortPet(petPtr, petsPtr);
		Pet* currentPtr = *petPtr;
			while (currentPtr->nextPtr != NULL) {
				currentPtr = currentPtr->nextPtr;
			}
			currentPtr->nextPtr = petsPtr;
		}
}

//Function used to print the linked list
void printLinkedList(Pet* headPtr) {

	Pet *current = headPtr;
	while (current != NULL) {
		printf("%s", current->petName);
		printf("\t%d\n", current->age);
		current = current->nextPtr;
	}
}

//Function used to remove the links
//headPtr is the headPTR from main
//name[] is the name being removed
bool removeLinks(Pet** headPtr, char name[]) {

	Pet* currentPtr = *headPtr;
	Pet* previousPtr = NULL;
	bool returnValue = false;

	//While loop to iterate while current is not null
	while (currentPtr != NULL) {

		//if current pet name is equal to the name sent in 
		if (strcmp(currentPtr->petName, name) == 0) {

			//if previous still equals null then we are removing the headPTR
			if (previousPtr == NULL) {
				*headPtr = currentPtr->nextPtr;
				returnValue = true;
			}
			//Else, skip over the headPtr and continue to search for the correct node to remove
			else {
				previousPtr->nextPtr = currentPtr->nextPtr;
				returnValue = true;
			}
		}
		else {
			previousPtr = currentPtr;
		}
		currentPtr = currentPtr->nextPtr;
	}

	//returnValue shows whether or not the node was found and removed
	return returnValue;
}

//Function used to find out whether or not the user would like to remove a pet
char wouldYouLikeToRemove(char input[]) {

	//use strcmp to compare the string being sent in to "Y" or "n"
	char returnValue = 'y';
	if (strcmp(input, "y") == 0 || strcmp(input, "Y") == 0) {
		returnValue = 'Y';
	}
	else if (strcmp(input, "n") == 0|| strcmp(input, "N") == 0) {
		returnValue = 'N';
	}

	return returnValue;
}

void sortPet(Pet* headPtr, Pet* newPetPtr) {

	Pet* currentPtr = headPtr;

	if (headPtr->petName > newPetPtr->petName) {
		headPtr->nextPtr = newPetPtr;
	}
	else {
		headPtr->nextPtr = currentPtr;
		headPtr = newPetPtr;
	}
}