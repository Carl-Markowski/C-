/*
Carl Markowski
CS2060 TTH
HomeWork 06
Due: April 9, 2022
This assignment will show my understanding of using files 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//Madlib Values
#define STRING_LENGTH 100
#define NUMBER_SENTENCES 5
#define NUMBER_WORDS 5
#define WORD_LENGTH 20
#define NOUN "noun"
#define ADJECTIVE "adjective"
#define NUM_FILES 3

//Function Prototypes
void getFilePath(char* finalPath, const char* directoryPath, const char* fileName);
bool getWordsFromFile(const char* path, char words[][WORD_LENGTH], int numberWords);
void getUserWords(char word[][WORD_LENGTH], const char* wordType, int numberWords);
bool writeSentenceToFile(const char* path, const char article[][WORD_LENGTH],const char verb[][WORD_LENGTH],
	const char preposition[][WORD_LENGTH],const char noun[][WORD_LENGTH],const char adjective[][WORD_LENGTH]
	,int numberWords, int numberSentences);

//Constants
const char* MADLIB_FILE = "madlib.txt";
const char* PREPOSITION_FILE = "prepositions.txt";
const char* ARTICLE_FILE = "articles.txt";
const char* VERB_FILE = "verbs.txt";
const char* DIRECTORY_PATH = "D:\\Carl\\Microsoft Visual Studio\\CS2060Projects\\BookExamples\\BookExamples\\";

int main (void) {
	char filePath[STRING_LENGTH];
	char article[NUMBER_WORDS][WORD_LENGTH];
	char verb[NUMBER_WORDS][WORD_LENGTH];
	char preposition[NUMBER_WORDS][WORD_LENGTH];
	char noun[NUMBER_WORDS][WORD_LENGTH];
 

	getFilePath(filePath, DIRECTORY_PATH, VERB_FILE);

	printf("%s", filePath);

	bool returns = getWordsFromFile(filePath, verb, NUMBER_WORDS);

	if (returns == false) {
		printf("\n%s", "Could not open file");
	}
	else {
		getUserWords(noun, NOUN, NUMBER_WORDS);
	}
	


}

/*
getFilePath joins the directory path and filename into one file path
Parameters:
finalPath - pointer to the array the path will be stored
directoryPath - path to folder
fileName - name of file
Return: void
*/
void getFilePath(char* finalPath, const char* directoryPath, const char* fileName) {
	
	strcpy(finalPath, directoryPath);
	strcat(finalPath, fileName);
}

/*
* getWordsFromFile reads the words from the files and places them into their respective arrays
* Parameters:
* path - pointer to the path passed in from getFilePath
* words[][]- 2D array used to store the words gotten from the file
* numberWords - integer used to hold the number of words in each file
* return true or false, depending on whether the file was opened or not
*/
bool getWordsFromFile(const char* path, char words[][WORD_LENGTH], int numberWords) {

	FILE* filePtr;
	filePtr = fopen(path, "r");
	bool returnValue = false;
	
	if (filePtr == NULL) {
		returnValue = false;
	}
	else {
		for (unsigned int i = 0; i < numberWords; i++) {
			fscanf(filePtr, "%s", words[i][WORD_LENGTH]);
		}
		returnValue = true;
	}
	return returnValue;
}

/*
getUserWords prompts the user for nouns or adjectives and stores them in a 2d array
Parameters:
word[][]- 2D array used to store the words read in 
wordType- pointer to the type of word being prompted for
numberWords - integer used to hold the amount of words needed from user
return - void
*/
void getUserWords(char word[][WORD_LENGTH], const char* wordType, int numberWords) {

	int wordCount = 0;
	char userInput[WORD_LENGTH];

	printf("\nPlease enter 5 %c: ", *wordType);

		while (wordCount < numberWords) {
			scanf("%s", userInput);
			word = userInput;
			wordCount++;
		}
}

/*
writeSentenceToFile created the madlib sentences and writes them to the file
Parameters-
path- pointer to the path of the file being wrote to
article[][]- 2D array that has the words for the article word type
verb[][]- 2D array that has the words for the verb word type
Prepositions[][]- 2D array that has the words for the preposition word type
noun[][]- 2D array that has the nouns entered by the user
adjective[][]- 2D array that has the adjectives entered by the user
numberWords- integer that holds the amount of words for each sentence
numberSentences- intgers that holds the amount of sentences that will be wrote to the file
return - true or false based on whether or not the file was opened
*/
bool writeSentenceToFile(const char* path, const char article[][WORD_LENGTH], const char verb[][WORD_LENGTH],
	const char preposition[][WORD_LENGTH], const char noun[][WORD_LENGTH], const char adjective[][WORD_LENGTH]
	, int numberWords, int numberSentences) {

}