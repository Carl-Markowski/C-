/*
Carl Markowski
CS 3060-002
This is 6.6 from the text book "timesTen" Function
*/

//Preprocessor Direective
#include <iostream>
using namespace std;

//Function Prototype
int timesTen (int); 

//Main Function
int main() {

	int value = 0;
	timesTen(value);

	cout<< "The value is "<< value;
	return 0;
}

/*
Definition of timesTen
Function used to receive a number and multiply it by 10
*/
int timesTen(int number) {
	
	cout << "Enter a Value: "; //Statement used to print "Enter a Value: " to the console
	cin >> number; //cin used to hold the value inputted in the variable number

	return number * 10; //Return statement 
}


