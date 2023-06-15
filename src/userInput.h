#ifndef USERINPUT_H
#define USERINPUT_H

#include <iostream>
#include <limits>
#include <utility>
#include <memory>
#include "scrabble.h"
#include "colors.h"

class UserInput {
private:
    std::shared_ptr<Scrabble> board;
public:
    UserInput(std::shared_ptr<Scrabble> board);
    // returns number of players from user input
    int numOfPlayers();
    // ask if the current player thinks they created another valid word
    bool askAdditionalWord();

    // returns where the player wishes to place their word on the board as a tuple, (startrow, endrow, startcol, endcol)
    int getWordPlacement(Orientation wordOrientation);
    int nextPosition(Orientation wordOrientation);

    // ask if word placement is vertically or horizontally
    enum Orientation askOrientation();

    enum Argument userInputInitial(); 

    enum TurnAction userInputDuringTurn();

    int getStartingPosition();
    int getEndingPosition();
};

#endif