/* 
* Simple hangman game 
* Currently runs in the console
* TODO: Add real dictionary
* GUI support may be added
* stephen.carter@mail.mcgill.ca
* Stephen Carter 2016
*/
#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>

using namespace std;

//global variables, maybe add word as global?
int gLeft = 10;
string guesses;
string display;

//struct and operator used to check for non alpha 
struct only_alpha {
	bool operator()(char c) {
		return !isalpha(c);
	}
};
//set up window
string setupWindow() {
	string input;
	cout << "*******************************" << endl;
	cout << "Simple Hangman Game Version 0.1" << endl;
	cout << "*******************************" << endl << endl;
	system("pause");
	system("CLS");

	cout << "welcome to hangman, please enter a word " << endl;
	//loop until valid entry
	while (1) {
		cin >> input;
		bool not_letters = find_if(input.begin(), input.end(), only_alpha()) != input.end();
			//if valid entry return
			if (!not_letters) {
				system("CLS");
				cout << "Word accepted... setting up game";
				return input;
			}
			else {
				cout << "invalid entry, please try again..." << endl;
			}
	}

}
//to delete
//void setupGameWindow(string word) {
//	system("CLS");
//	cout << "*******************************" << endl;
//	cout << "Simple Hangman Game Version 0.1" << endl;
//	cout << "*******************************" << endl << endl;
//	cout << "Guesses remaining = " << gLeft << endl << endl;
//	
//	for (int i = 0; i < word.length()-1; i++) {
//		cout << "_ ";
//	}
//	cout << "_" << endl << endl;
//	
//	//cout << "Enter your guess" << endl;
//}

//take users guess
bool guess(string word, string &guess, string &newstr) {
	cout << "Please enter your guess" << endl;
	newstr = word;
	//loop until valid guess is entered
	while (1) {
		cin >> guess;
		bool not_letters = find_if(guess.begin(), guess.end(), only_alpha()) != guess.end();
		if (guess.length() == 1 && !not_letters) {
			break;
		}
		else {
			cout << "invalid entry, please guess again..." << endl;
		}
	}
	//newstr is word were guessed letter is removed
	replace(newstr.begin(), newstr.end(), char(guess[0]), '_');
	if (newstr == word) {
		return false;
	}
	return true;
}
//update the displayed word, i.e guessed letters
void updateDisplayWord(string word, string curGuess) {
	for (int i = 0; i < word.length(); i++) {
		if (word[i] == curGuess[0]) {
			display[i] = curGuess[0];
		}
	}
}
//update game window
void updateWindow() {
	system("CLS");
	cout << "*******************************" << endl;
	cout << "Simple Hangman Game Version 0.1" << endl;
	cout << "*******************************" << endl << endl;
	cout << "Guesses remaining = " << gLeft << endl;
	cout << "List of guessed letters = \"" << guesses << "\"" << endl << endl;
	
	cout << display << endl;
}

//window to display on win
void displayWinWindow() {
	system("CLS");
	cout << "*******************************" << endl;
	cout << "Simple Hangman Game Version 0.1" << endl;
	cout << "*******************************" << endl << endl;
	cout << "********************************" << endl;
	cout << "********************************" << endl << endl;
	cout << "            You Win!            " << endl << endl;
	cout << "********************************" << endl;
	cout << "********************************" << endl << endl;
}
//window to display on loss
void displayLoseWindow() {
	system("CLS");
	cout << "*******************************" << endl;
	cout << "Simple Hangman Game Version 0.1" << endl;
	cout << "*******************************" << endl << endl;
	cout << "********************************" << endl;
	cout << "********************************" << endl << endl;
	cout << "            You Lose!           " << endl << endl;
	cout << "********************************" << endl;
	cout << "********************************" << endl << endl;
}
//main i.e., game  
void main() {
	// strings
	string curGuess, updatedWord;
	string word = setupWindow();
	string answer = word;
	//set up display word
	for (char c : word) {
		display.append("_");
	}
	//make sure word is lower
	transform(word.begin(), word.end(), word.begin(), ::tolower);
	//setup first window and start game
	updateWindow();
	while (gLeft > 0) {
		//take users guess and update guesses
		bool result = guess(word, curGuess, updatedWord);
		if (guesses.find(curGuess) != string::npos) {
			
		}
		else {
			gLeft--;
			guesses.append(curGuess);
		}
		//logic for if guess is correct
		if (result) {
			updateDisplayWord(word, curGuess);
			updateWindow();
			word = updatedWord;
		}
		//logic if guess is incorrect
		else {
			updateWindow();
		}
		//show win window
		if (display == answer) {
			displayWinWindow();
			return;
		}
	}
	//show lose window
	displayLoseWindow();
	cout << "Word was = " << answer << endl;
}