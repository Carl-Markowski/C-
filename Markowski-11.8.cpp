/*
Carl Markowski
CS 3060 11.8
This code is used to show my ability to use structures and compare strings
to find the correct object in the structure
*/

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//Structure
struct Customer {

	string name; //Holds the name of the customers
	string address = ""; //Holds the address of the customer
	string cityState = ""; //Holds the city and state of the customer
	double zipCode = 0; //Holds the zipCode
	long long telephoneNumber = 0; //Holds the telephone number
	long accountBalance = 0; //Holds the accountBalance 
	long dateOfPayment = 0; //Holds the date of the last payment

};

//Function Prototypes
bool findCustomer(Customer[], int);

//Constants
const int NUM_CUSTOMERS = 2;

int main() {

	//Variables
	Customer array[NUM_CUSTOMERS];

	array[0] = { "Carl Markowski", "507 JohnDoe Dr", "Colorado Springs, Co", 80915, 1234567891,
																			10000, 02122023 };

	array[1] = { "John Doe", "899 Johndoe Dr", "Colorado Springs, Co", 80915, 1234567891, 100000
																					, 02122023 };
	bool found = false; //Flag to see if a customer was found or not



	found = findCustomer(array, NUM_CUSTOMERS);

	if (!found) {
		cout << "There were no matches." << endl;
	}
	

	return 0;
}


//This function finds the customers in the array
bool findCustomer(Customer array[], int number) {

	//Variables
	string entry;
	int count = 0;
	bool returnFlag = false;

	//Get the partial name being looked for
	cout << "Please enter the name of the customer you are trying to find: " << endl;
	cin >> entry;
	cin.ignore();


	//Iterates through the entire array to find potential matches, if no matches it returns fasle
	while (count != number) {

		Customer temp = array[count];
		size_t found = temp.name.find(entry, 0);

		if (found != string::npos) {
			cout << "Customer: " << temp.name << endl;
			returnFlag = true;
		}
		count++;
	}

	return returnFlag;
}