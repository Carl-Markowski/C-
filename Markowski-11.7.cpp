/*
Carl Markowski
CS 3060 11.8
*/

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

//Structure 
struct Customer {
	
	string name; //Holds the name
	string address; //Holds the address of the customer
	string cityState; //Holds the city and state
	double zipCode; //Holds the zip code
	long long telephoneNumber; //Holds the telephone number
	long accountBalance; //Holds the balance of the customers account
	long dateOfPayment; //Holds the date of the last payment

};

//Function Prototypes
void getCustomerInfo(Customer[], int);
void displayCustomers(Customer[], int);
bool findCustomer(Customer[], int);

//Constants
const int NUM_CUSTOMERS = 2;

int main() {

	//Variables
	Customer array[NUM_CUSTOMERS]; //Holds the array of customer
	bool flag = false; //Flag used to indiciate if the user is done or not
	bool found = false; //Holds the return value from findCustomer
	Customer foundCustomer; //Holds the customer that the user is trying to find


	//While the user wants to stay in the menu
	while (!flag) {

		int menuPick = 0;

		//Allows customer to pick from the menu
		cout << "Welcome\n" << "Please choose a menu option to continue:\n" << "1: Enter new customers.\n"
			<< "2. Search for an existing customer.\n" << "3. Display all current customers.\n Enter 0 to exit."
			<< endl;
		cin >> menuPick;
		cin.ignore();
		
		//Determine what option was selected by the user
		if (menuPick == 1) {
			getCustomerInfo(array, NUM_CUSTOMERS);
		}
		else if (menuPick == 2) {
			found = findCustomer(array, NUM_CUSTOMERS);

			if (!found) {
				cout << "There was no matches" << endl;
			}
		}
		else if (menuPick == 3) {
			displayCustomers(array, NUM_CUSTOMERS);
		}
		else if (menuPick == 0) {
			flag = true;
		}
	}

	cout << "Thank you. GoodBye:)";

	return 0;
}

//This function gets all the information for the customers
void getCustomerInfo(Customer array[], int number) {

	int count = 0;
	Customer temp = array[0];
	bool flag = false;

	while (!flag) {

		cout << "Please enter the Name of the customer: " << endl;
		cin >> temp.name;
		cin.ignore();

		cout << "Please enter the address: " << endl;
		cin >> temp.address;
		cin.ignore();

		cout << "Please enter the city and state: " << endl;
		cin >> temp.cityState;
		cin.ignore();

		cout << "Please enter the Zip Code: " << endl;
		cin >> temp.zipCode;

		cout << "Please enter your telephone number: " << endl;
		cin >> temp.telephoneNumber;
		cin.ignore();

		cout << "Enter the account balance: " << endl;
		cin >> temp.accountBalance;
		cin.ignore();
		
		if (temp.accountBalance < 0) {
			cout << "Please enter a positive value." << endl;
			cout << "Enter the account balance: " << endl;
			cin >> temp.accountBalance;
			cin.ignore();
		}

		cout << "Enter the date of the last payment in the form of XXXXXXXX: " << endl;
		cin >> temp.dateOfPayment;
		cin.ignore();

		array[count] = temp;
		count++;
	
		if (count == number) {
			flag = true;
		}
	}
}

//This function displays all the customers information 
void displayCustomers(Customer array[], int number) {

	int count = 0;
	Customer temp;
	
	cout << "The current customers are: " << endl;

	for (count = 0; count < number; count++) {

		temp = array[count];

		cout << "Name: " << temp.name << endl;
		cout << "Address: " << temp.address << endl;
		cout << "City, State, and Zip Code: " << temp.cityState << " " << temp.zipCode << endl;
		cout << "Telephone number: " << temp.telephoneNumber << endl;
		cout << "Account Balance: " << temp.accountBalance << endl;
		cout << "Date of Last Payment: " << temp.dateOfPayment << "\n" << endl;
	}
}

//This function finds the customers being searched for by the user
bool findCustomer(Customer array[], int number) {

	//Variables
	string entry;
	int count = 0;
	bool returnFlag = false;
	
	//Get the partial or full name being searched for
	cout << "Please enter the name of the customer you are trying to find: " << endl;
	cin >> entry; 
	cin.ignore();

	//Iterates through the entire customer array to find potential matches
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