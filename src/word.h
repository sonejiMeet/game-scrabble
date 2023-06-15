#ifndef PHASE3_H
#define PHASE3_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <memory>
#include <cctype>
#include "scrabble.h"
#include "player.h"
#include "enum.h"

class Word {

private:

    std::vector<std::string> validWords;
    std::shared_ptr<Scrabble> board;
    
public:
    Word(std::shared_ptr<Scrabble> board);
    ~Word();

    // Check if a given word is in the dictionary.txt
    bool checkWord(std::string& word);
    
    // Check if a given word hasn't already been used
    bool isValidWord(const std::string& lookupWord) const;
    
    char pickTile();
    
    //places word on the board by taking start and end of the grid values
    void placeLetter(char tile, int selectedPos, int nextPos, Orientation wordOrientation);

    // Verify if the first player placed their word intersecting the center tile "board[7][7]"
    bool verifyFirstTurn();

    // Add the inserted word to the vector of current valid words
    void addValidWord(const std::string& word);

    std::string getWordFromBoard(int mainWordPlacement,int startingPosition, int endingPosition, Orientation wordOrientation);
};
#endif