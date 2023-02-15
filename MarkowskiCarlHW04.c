/*
 Carl Markowski
 CS2060 TTH
 Assignment 4
 Due: 02/24/2022
 This assignment will display my ability to use and manipulate 2D arrays
*/

#include <stdio.h>

//Defining values for the functions, Can be changed 
#define STUDENTS 4
#define GRADE_CATEGORIES 5
#define CATEGORIES "1. Learning Activity 2. Homework 3. Project 4. Midterm 5. Final"
const double GRADE_CATEGORY_WEIGHT[GRADE_CATEGORIES] = { 0.1, 0.3, 0.3, 0.15, 0.15 };

//Function prototypes
void calculateAverage(const int grades[STUDENTS][GRADE_CATEGORIES],size_t people, size_t tests);
void displayFinalGrades();

int studentGrades[STUDENTS][GRADE_CATEGORIES];
double studentAverages[STUDENTS];
double classAverage;

int main(void) {
	
	unsigned int grade = 0;

	//Prints the opening statement of the program
	printf("This program will calculate the grades for these categories %s\n", CATEGORIES);
	printf("%s\n", "The category weights are:");

	//Prints the different weights
	for (unsigned int i = 0; i < GRADE_CATEGORIES; i++) {
		printf("Category %d", i + 1);
		printf(" weight is %.2lf\n", GRADE_CATEGORY_WEIGHT[i]);
	}

	printf("The correct order to enter the grades for each student is:  %s\n", CATEGORIES);

	//Iterates through the 2D array and takes a value for the grades
	for (unsigned int student = 0; student < STUDENTS; student++) {
		for (unsigned int grades = 0; grades < GRADE_CATEGORIES; grades++) {
			printf("Enter the grade for each category for student %d:\n", student + 1);
			scanf("%d", &grade);
			studentGrades[student][grades] = grade;
		}
	}

	//Function calls to calculate and display the classes grades
	calculateAverage(studentGrades,STUDENTS, GRADE_CATEGORIES);
	displayFinalGrades();

}


void calculateAverage(const int grades[STUDENTS][GRADE_CATEGORIES],size_t people, size_t tests) {

	double weightedGrades = 0;
	double average = 0;
	
	for (unsigned int student = 0; student < people; student++) {
		average = 0;
		for (unsigned int grade = 0; grade < tests; grade++) {
			weightedGrades = grades[student][grade] * GRADE_CATEGORY_WEIGHT[grade];
			average += weightedGrades;
		}
		studentAverages[student] = average;
	}

	for (unsigned int i = 0; i < people; i++) {
		classAverage = studentAverages[i] + classAverage;
	}
	classAverage = classAverage / people;
}

void displayFinalGrades() {
	
	printf("\n%s\n", "Grades entered for each student");
	for (unsigned int row = 0; row < STUDENTS; row++) {
		for (unsigned int col = 0; col < GRADE_CATEGORIES; col++) {
			int grade = studentGrades[row][col];
			printf("Student %d: ", row + 1);
			printf("%d\t", grade);
		}
		printf("%s", "\n");
	}

	char letterGrade;
	printf("\n%s\n", "Final grades for students, respectively:");

	for (unsigned int rows = 0; rows < STUDENTS; rows++) {
			double avg = studentAverages[rows];
			if (avg >= 90) {
				letterGrade = 'A';
			}
			else if (avg >= 80 && avg < 90) {
				letterGrade = 'B';
			}
			else if (avg >= 70 && avg < 80) {
				letterGrade = 'C';
			}
			else if (avg >= 65 && avg < 70) {
				letterGrade = 'D';
			}
			else {
				letterGrade = 'F';
			}
			printf("Student % d: ", rows + 1);
			printf("%.2lf", studentAverages[rows]);
			printf("\t%c\n ", letterGrade);
			}

	printf("%s\n", "The class average is: ");
	printf("\t%.2lf", classAverage);
}