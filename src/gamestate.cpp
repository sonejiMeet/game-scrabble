#include <gamestate.h>

GameState::GameState(const std::vector<Player>& players, std::shared_ptr<Tile> tile) : players(players), tile(tile){

}
GameState::~GameState(){}

int GameState::determineWinner(int numOfPlayers) const{
    if(numOfPlayers <= 0) 
        return -1;
    
    int highestScore = players[0].getScore(); //assume that fisrt player has highest score
    int winnerIndex = 0;
    bool tie = false;

    for (int i = 1; i < numOfPlayers; ++i) {
        int playerScore = players[i].getScore();
        if (playerScore > highestScore) {
            highestScore = playerScore;
            winnerIndex = i;
            tie = false;
        } else if (playerScore == highestScore) {
            tie = true;
        }
    }

    if (tie) {
        return -2;
    }

    return winnerIndex;
}

bool GameState::isTie(int numOfPlayers) const{
    int winnerIndex = determineWinner(numOfPlayers);
    return (winnerIndex == -2);
}

std::vector<Player> GameState::getTiedPlayers(){
    std::vector<Player> tiedPlayers;
    int highestScore = players[0].getScore();

    for (const Player& player : players) {
        if (player.getScore() == highestScore) {
            tiedPlayers.push_back(player);
        }
    }

    return tiedPlayers;
}

bool GameState::isEndOfGame() const{

    return (tile->getRemainingTiles() != 0);
}