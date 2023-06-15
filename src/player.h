#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <cstring>
#include <memory>
#include <chrono>
#include <random>
#include <algorithm>
#include <cstring>
#include <vector>
#include "tile.h"
#include "enum.h"
// #include "timer.h"


class Player{
private:

    int score;
    std::string name;
    // char tiles[7];
    std::vector<char> tiles;
    
    // char temp_prev_tile_set[7];
    std::vector<char> temp_prev_tile_set;
    std::shared_ptr<Tile> tile;

public:
    Player(std::shared_ptr<Tile> tile);
    
    ~Player();

    void setScore(int score);
    int getScore() const;

    void setName(std::string name);
    std::string getName() const;

    void setTiles(const std::vector<char>& newTiles);
    std::vector<char> getTiles();

    void inputName(const std::vector<std::string>& existingNames, int i);
    void calculatePlayerScore(const std::string& word, int mainWordPlacement, int startingPosition, int endingPosition, Orientation wordOrientation);

    void saveCurrentTileSet();
    void revertToPrevSet();

    void removeTile(char tile);
    bool doesTileExist(char tile);

    int countNonEmptyTiles();
    // Distribute tiles to the current player based on how many they are missing in their set
    void drawTiles();
    void shuffleTiles();
    // swaps current tiles of the player to new tiles
    void swapTiles();

    // displays player's name, score and sets of tiles 
    void displayPlayerInfo();
    bool isTileSetEmpty();

};
#endif  