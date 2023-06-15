#include "word.h"
/*
    TODO:   
*/


Word::Word(std::shared_ptr<Scrabble> board) : board(board){}
Word::~Word(){}

char Word::pickTile(){
    char tile;
    while (true) {
        std::cout << "Pick a tile from your set\n";
        if (std::cin >> tile && std::cin.peek() == '\n') break;
        else {
            std::cout << "Invalid input. Please enter a single character.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return std::toupper(tile);
}
bool Word::checkWord(std::string& word){
    std::string lowerCase;
    for(auto& c : word)
        lowerCase += tolower(c);

    std::ifstream File("dictionary/dictionary.txt");
    if(File.is_open()){
        std::string line;
        while (getline(File, line)){
            if(strcmp(line.c_str(), lowerCase.c_str()) == 0)
                return true;
        }
        return false;
        File.close();
    }
    return false;
}

void Word::placeLetter(char tile, int selectedPos, int nextPos, Orientation wordOrientation){
    if(wordOrientation == HORIZONTAL)
        board->setBoard(selectedPos, nextPos, tile);

    else if(wordOrientation == VERTICAL)
        board->setBoard(nextPos, selectedPos, tile);
}

void Word::addValidWord(const std::string& word){
    validWords.push_back(word);
}
bool Word::isValidWord(const std::string& lookupWord) const{

    if(find(validWords.begin(), validWords.end(), lookupWord) != validWords.end()){
        return false;
    }
    return true;
}

std::string Word::getWordFromBoard(int mainWordPlacement,int startingPosition, int endingPosition, Orientation wordOrientation){

    std::string word; 
    if(wordOrientation == HORIZONTAL){
        for(int i = startingPosition; i <= endingPosition; i++){
            word += board->getBoard(mainWordPlacement, i);
        }
    }
    else if(wordOrientation == VERTICAL){
        for(int i = startingPosition; i <= endingPosition; i++){
            word += board->getBoard(i, mainWordPlacement);
        }
    }
    return word;
}

