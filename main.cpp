/*
 * File:   main.cpp
 * Author: Pit Apps
 *
 * Created on January 19, 2012, 2:49 PM
 */

#include "HexBoard.h"
#include <cctype>

using namespace std;
HexBoard HB;

/* Reads response on restart request and deals with it. */
int restart(char c) {
	switch (c) {
	case 'y':case 'Y':
		HB.reset();
		return 1;
	case 'n':case 'N':
		return 0;
	}
	return 0;
}

int main() {
	int x, y, level;
	char yn, settings;
	State::Player won;

	cout << "Welcome to Hex!\nYou are playing as Black, your goal is to connect Top and Bottom of the board." << endl;




	bool correctInput = false;

	while(!correctInput){
		cout << "Enter Level of difficulty [1-9] of the AI or enter 'h' for more information" << endl;
			cin >> settings;
		if (settings == 'h') {
			cout << "Enter a number between 1 to 9 for the difficulty, keeping in mind that the higher is level of AI, the longer you will waitfor the computer move." << endl;
			correctInput = false;
		}else if(isdigit(settings) && (int)settings > 48 && (int)settings < 58) {
			correctInput = true;
			level = ((int)settings-48)*100;
		}else{
			cout << "wrong input" << endl;
			correctInput = false;
		}
	}
	// Main game Loop
	while (true) {

		// Check if there's a winner and deal with it.
		won = HB.hasWon();
		if (won == State::HUMAN) {
			cout << "You have won.\n Play again? (y/n)" << endl;
			cin >> yn;
			if (!restart(yn)) break;
		} else if (won == State::COMPUTER) {
			cout << "You have lost.\n Play again? (y/n)" << endl;
			cin >> yn;
			if (!restart(yn)) break;
		}

		// Ask for next move.
		cout << "Enter your next move x y (0 to quit): ";
		cin >> x;
		if (x == 0) break;
		cin >> y;

		// Put a new piece on the board and handle any illegal moves.
		try {
			HB.putPiece(x, y);

			// Play the computer's move and print the board.
			HB.playComputer(level);
			HB.print();
		} catch (int e) {
			switch (e) {
			case 1:
				cout << "Invalid Coordinates! Please try again." << endl;
				break;
			case 2:
				cout << "A stone has already been placed on those coordinates. Please try again." << endl;
				break;
			}
		}
	}

	return 0;
}
