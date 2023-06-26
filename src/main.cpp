#include <iostream>
#include <memory>
#include <cstring>
#include <vector>
#include "scrabble.h"
#include "tile.h"
#include "player.h"
#include "word.h"
#include "userInput.h"
#include "gamestate.h"
#include "colors.h"
#include "enum.h"

void clearScreen(){
    #ifdef _WIN32
        int result = system("cls");
        static_cast<void>(result);
    #else 
        int result = system("clear");
        static_cast<void>(result);
    #endif
}

int main(void) {

    clearScreen();
    
    std::shared_ptr<Scrabble> board = std::make_shared<Scrabble>();
    std::shared_ptr<Tile> tile = std::make_shared<Tile>();
    std::vector<Player> players;
    Word word(board);
    UserInput userInput(board);
    GameState gameState(players, tile);

    int numPlayers = userInput.numOfPlayers(); 
    std::vector<std::string> existingNames;
    
    for(int i = 0; i < numPlayers; i++){
        Player player(tile);
        players.push_back(player);
        players[i].inputName(existingNames, i+1);
        existingNames.push_back(players[i].getName());
    }
    existingNames.clear();

    while(gameState.isEndOfGame()){ 
        for(int i = 0; i < numPlayers; i++){
            // if(tile->getRemainingTiles() != 0 && !players[i].isTileSetEmpty()){
                board->printBoard(tile->getBonusTiles());
                board->saveCurrentBoardState();
                players[i].drawTiles();
                players[i].saveCurrentTileSet();
                players[i].displayPlayerInfo();
                
                Argument userInputInitial = userInput.userInputInitial();

                if(userInputInitial == CONTINUE_PLAYING){
                    clearScreen();
                    board->printBoard(tile->getBonusTiles());
                    players[i].displayPlayerInfo();
                    
                    Orientation wordOrientation = userInput.askOrientation();
                    int mainWordPlacement = userInput.getWordPlacement(wordOrientation);
                    int nextPosition;
                    bool turnContinues = true;
                    while(turnContinues == true){
                        
                        TurnAction userInputTurn = userInput.userInputDuringTurn();

                        if(userInputTurn == SHUFFLE_TILES){
                            players[i].shuffleTiles();
                            board->printBoard(tile->getBonusTiles(), wordOrientation, mainWordPlacement);
                            players[i].displayPlayerInfo();
                        }
                        else if(userInputTurn == CONTINUE){
                            if(!players[i].isTileSetEmpty()){
                                char chosenTile = word.pickTile();
                                if(players[i].doesTileExist(chosenTile)){
                                    nextPosition = userInput.nextPosition(wordOrientation);
                                    if(board->isBoardPositionEmpty(mainWordPlacement, nextPosition, wordOrientation)){
                                        word.placeLetter(chosenTile, mainWordPlacement, nextPosition, wordOrientation);
                                        players[i].removeTile(chosenTile);
                    
                                        board->printBoard(tile->getBonusTiles(), wordOrientation, mainWordPlacement);
                                        players[i].displayPlayerInfo();        
                                    }
                                    else std::cout << ANSI_B_RED << "This grid is not empty. Try again." << ANSI_COLOR_RESET << std::endl;
                                
                                }
                                else std::cout  << ANSI_B_RED << "This tile does not exist in your set!" << ANSI_COLOR_RESET << std::endl;
                            } else std::cout  << ANSI_B_RED << players[i].getName() << " has no more tiles left!" << ANSI_COLOR_RESET << std::endl;
                        }
                        else if(userInputTurn == LOCK_IN_WORD){
                            
                            int startingPosition = userInput.getStartingPosition();
                            int endingPosition = userInput.getEndingPosition();
                            
                            std::string wordOnBoard = word.getWordFromBoard(mainWordPlacement, startingPosition,endingPosition, wordOrientation);
                            
                            if(word.checkWord(wordOnBoard) && word.isValidWord(wordOnBoard)){
                                word.addValidWord(wordOnBoard);
                                players[i].calculatePlayerScore(wordOnBoard, mainWordPlacement, startingPosition, endingPosition, wordOrientation);
                                
                                std::cout << ANSI_B_GRN <<players[i].getName() << "'s score was changed to " << players[i].getScore() << ANSI_COLOR_RESET << std::endl;
                                std::cout << ANSI_B_GRN << "The word was '" << wordOnBoard << "'" << ANSI_COLOR_RESET << std::endl;
                                turnContinues = false;
                            }
                            else if (!word.checkWord(wordOnBoard) || !word.isValidWord(wordOnBoard)) {
                                board->revertBoardState();
                                std::cout << ANSI_B_GRN << "Board reverted to previous state" << ANSI_COLOR_RESET << std::endl;
                                players[i].revertToPrevSet();
                                board->printBoard(tile->getBonusTiles());
                                players[i].displayPlayerInfo();
                                if(!word.checkWord(wordOnBoard))
                                    std::cout << ANSI_RED << " \"" << wordOnBoard <<"\" is not in the english dictionary! Try again!" << ANSI_COLOR_RESET <<  std::endl;
                                else
                                    std::cout << ANSI_RED << "This word is not valid, it has already been used before!" << ANSI_COLOR_RESET << std::endl;
                            }
                        }
                        else if(userInputTurn == FORFEIT){
                            clearScreen();
                            board->revertBoardState();
                            std::cout << ANSI_B_GRN << "Board reverted to previous state" << ANSI_COLOR_RESET << std::endl;
                            players[i].revertToPrevSet();
                            std::cout << ANSI_B_GRN << players[i].getName() <<"'s tile reverted to previous state" << ANSI_COLOR_RESET << std::endl;
                            turnContinues = false;
                        }
                    }
                    
                }else if(userInputInitial == SWAP_TILES) {
                    players[i].swapTiles();
                    std::cout << ANSI_B_CYN << players[i].getName() << "'s tiles were swapped and their turn was skipped." << ANSI_COLOR_RESET << std::endl;
                }
                else // at this point means if(userInput == SKIP_TURN)
                    continue;
            
            // }    

        }
    }
    if(gameState.isTie(numPlayers)){
        clearScreen();
        std::cout << ANSI_B_GRN << "It's a tie!" << ANSI_COLOR_RESET << std::endl;

        std::vector<Player> tiedPlayers = gameState.getTiedPlayers();
        for (const Player& player : tiedPlayers) {
            std::cout << ANSI_B_GRN << "Player " << player.getName() << " tied with a score of " << player.getScore() << "!" << ANSI_COLOR_RESET << std::endl;
        }
    } else{
        int winnerIndex = gameState.determineWinner(numPlayers);
        if (winnerIndex != -1) {
            
            const Player& winner = players[winnerIndex];
            std::cout << ANSI_B_GRN << "\n\n\nThe winner is " << winner.getName() << " with a score of " << winner.getScore() << ANSI_COLOR_RESET << std::endl;
        } else {
            std::cout << ANSI_B_RED << "No winner found!" << ANSI_COLOR_RESET << std::endl;
        }
    }




    return 0;
}