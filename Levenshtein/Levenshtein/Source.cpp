// Arend van Dormalen
// Assignment for BIT Students

#include <iostream>
#include <algorithm>
#include <string>

using std::min; 
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::to_string;

// Function to calculate minimum value of three options, using build in min/2 function.
int minThree(int del, int ins, int sub) {
	return min(min(del,ins),sub);
}

// Distance will be calculated in a table, in order to avoid checking the same subproblems.
int editDistance(string firstWord, string secondWord) {

	int m;
	int n;
	
	// Take maximum index from longest word
	if (firstWord.length() > secondWord.length()) {
		m = secondWord.length();
		n = firstWord.length();
	}
	else
	{
		m = firstWord.length();
		n = secondWord.length();
	}

	// Create 2-dimensional array
	// (This should be changed to vector, as it handles dynamic input.)
	int distTable[50][50];


	// Fill arrays
	for (int i = 0; i <= m; i++)
	{
		for (int j = 0; j <= n; j++)
		{

			// If first word is empty, cost is found by inserting every letter from second word.
			// Initializes top row.
			if (i == 0){
				distTable[i][j] = j;
			}

			// If second word is empty, cost is found by removing every letter from second word.
			// Initializes top column.
			else if (j == 0) {
				distTable[i][j] = i;
			}

			// If a letter is the same, move to the next letter in both words.
			else if (firstWord[i - 1] == secondWord[i - 1]){
				distTable[i][j] = distTable[i - 1][j - 1];
			}

			// If letters differ, increase cost and chose minimum option.
			else {
				distTable[i][j] = 1 + minThree(
					distTable[i][j - 1],		// Addition
					distTable[i - 1][j],		// Deletion
					distTable[i - 1][j - 1]);	// Substitution
			}


			// After change, check if transposition would improve cost.
			if (i > 1 && j > 1 && firstWord[i-1] == secondWord[i-2] && firstWord[i-2] == secondWord[i-1]) {
					distTable[i][j] = min(distTable[i][j], distTable[i - 2][j - 2] + 1); // Transposition
			}

		}

	}

	return distTable[m][n];
}

// Main sends text to the console and parses the user input.
int main() {

	string firstWord, secondWord;

	cout << "Enter first word:  ";
	getline(cin, firstWord);
	cout << "Enter second word: ";
	getline(cin, secondWord);

	int minDist = editDistance(firstWord, secondWord);

	cout << "Levenshtein distance between \"" + firstWord + "\" and \"" + secondWord + "\" is: " + to_string(minDist);
	cin.get(); // Keep console open
	return 0;
}



