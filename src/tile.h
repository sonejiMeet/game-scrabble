#ifndef PHASE2_H
#define PHASE2_H

#include <iostream>
#include <map>
#include <utility>
#include <memory>


class Tile {
private:
    // Map of characters to their corresponding values
    std::map<char, int> charValues;
    std::map<char, unsigned int> letterCounts;
    
    std::map<std::pair<int, int>, char> bonusTile;
    unsigned int remainingTile;
    
    //map bonus tiles to given grid values on the board 
    void mapBonusTiles();
    // Initialize the point values of each character
    void initValues();
    // Intializes the counts of each letter
    void initLetterCount();
public:
    
    Tile();
    ~Tile();
    
    //getter function for letterCounts property
    std::map<char, unsigned int> getLetterCounts() const;
    void setLetterCounts(std::map<char, unsigned int> updatedMap);
    
    void printLetterCounts();
    
    std::map<std::pair<int,int>, char> getBonusTiles();
    
    int getRemainingTiles();

    //return the char of bonus tile thats on a given grid values
    char getBonusChar(int row, int col) const;

    // Convert a string to its corresponding score value
    int stringToValue(const std::string& word);
    int getTileValue(const char& character);
};
#endif