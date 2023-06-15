#include "scrabble.h"
#include "colors.h"
/*
    TODO: create a instruction template before the game starts

*/
Scrabble::Scrabble() : board{}, prev_state{}{
    initializeBoard();
}

Scrabble::~Scrabble() {

}

char Scrabble::getBoard(int row, int col) const{
    return toupper(board[row][col]);
}

void Scrabble::setBoard(int row, int col, char value){
    board[row][col] = toupper(value);
}

void Scrabble::initializeBoard() {
    std::fill(&board[0][0], &board[0][0] + sizeof(board), '-');
    //memset
}

void Scrabble::saveCurrentBoardState(){     
    //memcpy
    std::copy(&board[0][0], &board[0][0] + sizeof(board), &prev_state[0][0]);
}

void Scrabble::revertBoardState(){
    std::copy(&prev_state[0][0], &prev_state[0][0] + sizeof(prev_state), &board[0][0]);
}
int Scrabble::getRows(){
    return numRows;
}
int Scrabble::getCols(){
    return numCols;
}

bool Scrabble::isBoardPositionEmpty(int mainWordPlacement, int nextPosition, Orientation wordOrientation){
    if(wordOrientation == HORIZONTAL){
        if(board[mainWordPlacement][nextPosition] != '-')
            return false;
    }
    else if(wordOrientation == VERTICAL){
        if(board[nextPosition][mainWordPlacement] != '-')
            return false;
    }
    return true;
}

std::string Scrabble::selectColor(char bonusCharacter) const{
    switch (bonusCharacter) {
        case 'T': return ANSI_B_RED;
        case 'D': return ANSI_B_MAG;
        case 't': return ANSI_B_BLU;
        case 'd': return ANSI_B_CYN;
        case '*': return ANSI_B_YEL;
        default: return ""; 
    }
}

void Scrabble::printAppropriateTile(int i, int j, const std::map<std::pair<int,int>, char>& bonusTile) const{
    std::pair<int,int> currentPosition = std::make_pair(i,j);
    if(bonusTile.find(currentPosition) != bonusTile.end() && board[i][j] == '-'){
        char bonusCharacter = bonusTile.at(currentPosition);
        std::string selectedColor = selectColor(bonusCharacter);
        if(selectedColor != "") std::cout << selectedColor << " " << bonusCharacter << " " << ANSI_COLOR_RESET;
    }
    else if(board[i][j] == '-'  ) std::cout << " " << board[i][j] << " ";
    else std::cout << " " << ANSI_BH_GRN << board[i][j] << ANSI_COLOR_RESET << " ";
}


void Scrabble::printBoard(std::map<std::pair<int,int>, char> bonusTile, Orientation wordOrientation, int value) const {
    std::cout << "         ";
    
    for (int i = 0; i < numCols; i++) {
        if(i == 0 && wordOrientation == VERTICAL && value == 0) std::cout << ANSI_B_GRN << i << ANSI_COLOR_RESET;
        else if(i == 0) std::cout << i;
        if (i > 0 && i < 10) {
            if(wordOrientation == VERTICAL && value == i) std::cout << "    " << ANSI_B_GRN << i << ANSI_COLOR_RESET;
            else std::cout << "    " << i;
        } else if(i == 10 || i > 10) {
            if(wordOrientation == VERTICAL && value == i) std::cout << "   "  << ANSI_B_GRN << i << ANSI_COLOR_RESET;
            else std::cout << "   " << i;

        }    
    }
    std::cout << std::endl;
    if(wordOrientation == HORIZONTAL && value == 0) std::cout << ANSI_B_GRN << "      +" <<  ANSI_COLOR_RESET;
    else std::cout << "      +";
    
    for (int i = 0; i < numCols; i++) {
        if (wordOrientation == HORIZONTAL && value == 0) {
            std::cout << ANSI_B_GRN << "----+";
            if(i == numCols-1) std::cout << ANSI_COLOR_RESET;
        } else {
            std::cout << "----+";
        }
    }

    std::cout << std::endl;

    for (int i = 0; i < numRows; i++) {
        if((wordOrientation == HORIZONTAL && i == value)) std::cout << "   " << ANSI_B_GRN << i << ANSI_COLOR_RESET; 
        else std::cout << "   "<< i;
        if (i < 10) {
            std::cout << "  ";
        } else {
            std::cout << " ";
        }
        if((wordOrientation == VERTICAL && value == 0) ) std::cout << ANSI_B_GRN << "|" << ANSI_COLOR_RESET;
        else std::cout << "|";
        
        for (int j = 0; j < numCols; j++) {
            printAppropriateTile(i, j, bonusTile);
            if((wordOrientation == VERTICAL && j == value-1) || (wordOrientation == VERTICAL && j == value)) std::cout << ANSI_GRN << " |" << ANSI_COLOR_RESET;
            else std::cout << " |";
        }

        std::cout << std::endl;
        
        if ((wordOrientation == HORIZONTAL && i == value-1 ) || (wordOrientation == HORIZONTAL && i == value)) {
            std::cout << "      " << ANSI_B_GRN << '+';
            for (int j = 0; j < numCols; j++) {
                std::cout << "----+";
                if(j == numCols-1) std::cout << ANSI_COLOR_RESET;
            }
            std::cout << std::endl;
        } else {
            std::cout << "      +";
            for (int j = 0; j < numCols; j++) {
                std::cout << "----+";
            }
            std::cout << std::endl;
        }
    }
}


