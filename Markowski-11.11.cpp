/*
Carl Markowski
CS 3060 11.11
This program shows my ability to utilize structures 
*/

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct MonthlyBudget {

	double housing; 
	double utilities;
	double houseHoldExp;
	double transpo;
	double food;
	double medical;
	double insurance;
	double entertainment;
	double clothing;
	double misc;
};

//Function Prototype
void getExpenses(MonthlyBudget *);
void displaySpending(MonthlyBudget *, MonthlyBudget, double);

//Const
const MonthlyBudget BUDGET = { 500.00, 150.00, 65.00, 50.00, 250.00, 30.00, 100.00, 150.00, 75.00, 50.00 };
const int NUM_EXP = 10;
const double TOTAL_MONTHLY_BUDGET = 1420.00;

int main() {

	//Variables
	MonthlyBudget userExp = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};//A monthly budget object to hold the spending from the user
	MonthlyBudget *userPtr = &userExp;

	//Get the expenses from user
	getExpenses(userPtr);

	//Calculate and display over and under amounts
	displaySpending(userPtr, BUDGET, TOTAL_MONTHLY_BUDGET);

	return 0;
}

void getExpenses(MonthlyBudget *userExp) {

	//This will ask the user to input their expenses for the month and assign those values to userExp
	cout << "Welcome to the Budget Tracker" << endl;
	cout << "Please enter the amounts you spent for this month in each category" << endl;
	
	cout << "Housing: " << endl;
	cin >> userExp -> housing;

	cout << "Utilities: " << endl;
	cin >> userExp -> utilities;

	cout << "HouseHold Expenses: " << endl;
	cin >> userExp -> houseHoldExp;

	cout << "Transportation: " << endl;
	cin >> userExp -> transpo;

	cout << "Food: " << endl;
	cin >> userExp -> food;

	cout << "Medical: " << endl;
	cin >> userExp -> medical;

	cout << "Insurance: " << endl;
	cin >> userExp -> insurance;

	cout << "Entertainment: " << endl;
	cin >> userExp -> entertainment;

	cout << "Clothing: " << endl;
	cin >> userExp -> clothing;

	cout << "Miscellaneous: " << endl;
	cin >> userExp -> misc;

}

void displaySpending(MonthlyBudget *user, MonthlyBudget budget, double totalExp) {

	//Variables
	double overUnder = 0.0; //Used to hold the difference between the set budget and what was spent by the user

	overUnder = budget.housing - user -> housing;

	if (overUnder > 0) {
		cout << "Your HOUSING budget is $" << budget.housing << " and you spent $" << user -> housing <<
			" leaving you $" << overUnder << " in the GREEN." << endl;
	}
	else {
		cout << "Your HOUSING budget is $" << budget.housing << " and you spent $" << user -> housing <<
			" leaving you $" << overUnder << " in the RED." << endl;
	}

	overUnder = budget.utilities - user -> utilities;

	if (overUnder > 0) {
		cout << "Your UTILITY budget is $" << budget.utilities << " and you spent $" << user -> utilities <<
			" leaving you $" << overUnder << " in the GREEN." << endl;
	}
	else {
		cout << "Your UTILITY budget is $" << budget.utilities << " and you spent $" << user -> utilities <<
			" leaving you $" << overUnder << " in the RED." << endl;
	}

	overUnder = budget.houseHoldExp - user -> houseHoldExp;

	if (overUnder > 0) {
		cout << "Your HOUSEHOLD EXPENSE budget is $" << budget.houseHoldExp << " and you spent $" << user -> houseHoldExp <<
			" leaving you $" << overUnder << " in the GREEN." << endl;
	}
	else {
		cout << "Your HOUSEHOLD EXPENSE budget is $" << budget.houseHoldExp << " and you spent $" << user -> houseHoldExp <<
			" leaving you $" << overUnder << " in the RED." << endl;
	}

	overUnder = budget.transpo - user -> transpo;

	if (overUnder > 0) {
		cout << "Your TRANSPORTATION budget is $" << budget.transpo << " and you spent $" << user -> transpo <<
			" leaving you $" << overUnder << " in the GREEN." << endl;
	}
	else {
		cout << "Your TRANSPORTATION budget is $" << budget.transpo << " and you spent $" << user -> transpo <<
			" leaving you $" << overUnder << " in the RED." << endl;
	}

	overUnder = budget.food - user -> food;

	if (overUnder > 0) {
		cout << "Your FOOD budget is $" << budget.food << " and you spent $" << user -> food <<
			" leaving you $" << overUnder << " in the GREEN." << endl;
	}
	else {
		cout << "Your FOOD budget is $" << budget.food << " and you spent $" << user -> food <<
			" leaving you $" << overUnder << " in the RED." << endl;
	}

	overUnder = budget.medical - user -> medical;

	if (overUnder > 0) {
		cout << "Your MEDICAL budget is $" << budget.medical << " and you spent $" << user -> medical <<
			" leaving you $" << overUnder << " in the GREEN." << endl;
	}
	else {
		cout << "Your MEDICAL budget is $" << budget.medical << " and you spent $" << user -> medical <<
			" leaving you $" << overUnder << " in the RED." << endl;
	}

	overUnder = budget.insurance - user -> insurance;

	if (overUnder > 0) {
		cout << "Your INSURANCE budget is $" << budget.insurance << " and you spent $" << user -> insurance <<
			" leaving you $" << overUnder << " in the GREEN." << endl;
	}
	else {
		cout << "Your INSURANCE budget is $" << budget.insurance << " and you spent $" << user -> insurance <<
			" leaving you $" << overUnder << " in the RED." << endl;
	}

	overUnder = budget.entertainment - user -> entertainment;

	if (overUnder > 0) {
		cout << "Your ENTERTAINMENT budget is $" << budget.entertainment << " and you spent $" << user -> entertainment <<
			" leaving you $" << overUnder << " in the GREEN." << endl;
	}
	else {
		cout << "Your ENTERTAINMENT budget is $" << budget.entertainment << " and you spent $" << user -> entertainment <<
			" leaving you $" << overUnder << " in the RED." << endl;
	}

	overUnder = budget.clothing - user -> clothing;

	if (overUnder > 0) {
		cout << "Your CLOTHING budget is $" << budget.clothing << " and you spent $" << user -> clothing <<
			" leaving you $" << overUnder << " in the GREEN." << endl;
	}
	else {
		cout << "Your CLOTHING budget is $" << budget.clothing << " and you spent $" << user -> clothing <<
			" leaving you $" << overUnder << " in the RED." << endl;
	}

	overUnder = budget.misc - user -> misc;

	if (overUnder > 0) {
		cout << "Your MISCELLANEOUS budget is $" << budget.misc << " and you spent $" << user -> misc <<
			" leaving you $" << overUnder << " in the GREEN." << endl;
	}
	else {
		cout << "Your MISCELLANEOUS budget is $" << budget.misc << " and you spent $" << user -> misc <<
			" leaving you $" << overUnder << " in the RED." << endl;
	}
}
