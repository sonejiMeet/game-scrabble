#ifndef WINNER_H
#define WINNER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <map>
#include <utility>
#include <memory>
#include "tile.h"
#include "scrabble.h"
#include "player.h"

class GameState {

private:

    const std::vector<Player>& players;
    std::shared_ptr<Tile> tile;

public:
    //take a vector of Player objects as a parameter after instances of the Player object (based on num of players) are created in the main.cpp
    GameState(const std::vector<Player>& players, std::shared_ptr<Tile> tile);
    ~GameState();

    // Determine the winner of the game, (0,1,2,3) expected output for a players
    int determineWinner(int numOfPlayers) const;
    // Check if there is a tie among players
    bool isTie(int numOfPlayers) const;
    std::vector<Player> getTiedPlayers();

    // Check if the game is over (i.e., no more tiles left to draw and all players have used all their tiles)
    bool isEndOfGame() const;

};

#endif