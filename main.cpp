/*
 * File:   main.cpp
 * Author: Pit Apps
 *
 * Created on January 19, 2012, 2:49 PM
 */

#include "HexBoard.h"

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
    int x, y;
    char yn;
    State::Player won;

    cout << "Welcome to Hex!\nYou are playing as Black, your goal is to connect Top and Bottom of the board." << endl;

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
