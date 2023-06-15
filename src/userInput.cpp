#include "userInput.h"
UserInput::UserInput(std::shared_ptr<Scrabble> board) : board(board){}

int UserInput::numOfPlayers(){
    std::cout << ANSI_B_BLU << "Enter number of players (minimum 2, maximum 4): " << ANSI_COLOR_RESET;
    int playerNum;
    while (true) {
        std::cin >> playerNum;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (std::cin.fail()) {  // if input is not an integer
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << ANSI_RED << "Invalid input. Please enter a number between 2 and 4.\n" << ANSI_COLOR_RESET;
            continue;
        }
        if (playerNum <= 1 || playerNum > 4) {
            std::cerr << ANSI_RED << "Invalid number of players. Please enter a number between 2 and 4.\n" << ANSI_COLOR_RESET;
        } else {
            break;
        }
    }
    return playerNum;
}


int UserInput::getWordPlacement(Orientation wordOrientation){
    int selectedPos = 0;
    std::string promptMessage;

    if (wordOrientation == HORIZONTAL) promptMessage = "Select the Row along which you would like to place your word!: ";
    else if (wordOrientation == VERTICAL) promptMessage = "Select the Col along which you would like to place your word!: ";

    while (true) {
        std::cout << ANSI_B_BLU << promptMessage << ANSI_COLOR_RESET << std::endl;
        if (std::cin >> selectedPos && selectedPos >= 0 && selectedPos <= board->getCols() - 1) break;
        else {
            std::cerr << ANSI_RED << "Invalid input! Input should be within the bounds of the board." << ANSI_COLOR_RESET << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return selectedPos;
}

int UserInput::nextPosition(Orientation wordOrientation){
    int nextPos = 0;
    std::string promptMessage;

    if (wordOrientation == HORIZONTAL) promptMessage = "Select the next column: ";
    else if (wordOrientation == VERTICAL) promptMessage = "Select the next row: ";
    while (true) {
        std::cout << ANSI_B_BLU << promptMessage << ANSI_COLOR_RESET << std::endl;
        if (std::cin >> nextPos && nextPos >= 0 && nextPos <= board->getCols() - 1) break;
        else {
            std::cerr << ANSI_RED << "Invalid input! Input should be within the bounds of the board." << ANSI_COLOR_RESET << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return nextPos;
}

enum Orientation UserInput::askOrientation(){
    char orientation;
    std::cout << ANSI_B_BLU<< "Which orientation do you wish to place your tiles? \n\t(h) for horizontal or (v) for vertical! \n" << ANSI_COLOR_RESET;
    while(true){
        std::cin >> orientation;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (std::cin.fail()) { 
            std::cin.clear();
            std::cerr << ANSI_RED  << "Invalid input\n" << ANSI_COLOR_RESET;
        } else if (orientation == 'h' || orientation == 'H' || orientation == 'v' || orientation == 'V') {
            {
                if(orientation == 'h' || orientation == 'H') return HORIZONTAL;
                else return VERTICAL;
            }
        } else {
            std::cerr << ANSI_RED << "Invalid input. Expected input is (h/H) for horizontal or (v/V) for vertical. \n" << ANSI_COLOR_RESET;
        }
    }
}

enum Argument UserInput::userInputInitial(){
    
    char value;
    std::cout << ANSI_B_BLU << "\n(esc) Continue Playing\n(1) Skip your turn!\n(2) Swap Tiles (Your turn will be skipped)" << ANSI_COLOR_RESET << std::endl;
    while(true){
        std::cin >> value;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << ANSI_RED << "Invalid input.\n" << ANSI_COLOR_RESET;
            continue;
        }
        switch (value) {
        case '1':
            return SKIP_TURN;
        case '2':
            return SWAP_TILES;
        case 27: // escape key in ASCII
            return CONTINUE_PLAYING;
        default:
            std::cerr << ANSI_RED << "Invalid input. Please enter a valid option.\n" << ANSI_COLOR_RESET;
            break;
        }

    }
} 

enum TurnAction UserInput::userInputDuringTurn(){
    char value;
    std::cout << ANSI_B_BLU << "\n(esc) Continue Playing\n(1) Shuffle Tiles\n(2) Lock in your word\n(3) Forfeit your turn" << ANSI_COLOR_RESET << std::endl;
    while(true){
        std::cin >> value;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << ANSI_RED << "Invalid input.\n" << ANSI_COLOR_RESET;
            continue;
        }
        switch (value) {
        case '1':
            return SHUFFLE_TILES;
        case '2':
            return LOCK_IN_WORD;
        case '3':
            return FORFEIT;
        case 27: // escape key in ASCII
            return CONTINUE;
        default:
            std::cerr << ANSI_RED << "Invalid input. Please enter a valid option.\n" << ANSI_COLOR_RESET;
            break;
        }

    }
}


int UserInput::getStartingPosition() {
    int startingPosition = 0;
    std::cout << "Enter Starting position of the word" << std::endl;
    while (true) {
        if (std::cin >> startingPosition && startingPosition >= 0 && startingPosition <= board->getCols() - 1) break;
        else {
            std::cerr << ANSI_RED << "Invalid input! Input should be within the bounds of the board." << ANSI_COLOR_RESET << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return startingPosition;
}

int UserInput::getEndingPosition() {
    int endingPosition = 0;
    std::cout << "Enter Ending position of the word" << std::endl;
    
    while (true) {
        if (std::cin >> endingPosition && endingPosition >= 0 && endingPosition <= board->getCols() - 1) break;
        else {
            std::cerr << ANSI_RED << "Invalid input! Input should be within the bounds of the board." << ANSI_COLOR_RESET << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return endingPosition;

}