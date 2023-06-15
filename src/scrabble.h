#ifndef SCRABBLE_H
#define SCRABBLE_H

#include <iostream>
#include <limits>
#include <stack>
#include <cstring>
#include <vector>
#include <map>
#include <utility>
#include "enum.h"

class Scrabble {
private:
    static const int numRows = 15;
    static const int numCols = 15;  

    char board[numRows][numCols];

    // temp storage for previous state of the board
    char prev_state[numRows][numCols];

public:
    Scrabble();
    ~Scrabble();

    int getRows();
    int getCols();

    char getBoard(int row, int col) const;
    void setBoard(int row, int col, char value);

    // init board with a '_' symbol
    void initializeBoard();

    void printBoard(std::map<std::pair<int,int>, char> bonusTile, Orientation wordOrientation = NONE, int value = -1) const;
    std::string selectColor(char bonusCharacter) const;
    void printAppropriateTile(int i, int j, const std::map<std::pair<int,int>, char>& bonusTile) const;

    void saveCurrentBoardState();
    void revertBoardState();
    
    bool isBoardPositionEmpty(int mainWordPlacement, int nextPosition, Orientation wordOrientation);
};

#endif