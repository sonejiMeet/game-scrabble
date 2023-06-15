#include "tile.h"
Tile::Tile(){
    
    initLetterCount();
    initValues();
    mapBonusTiles();
    remainingTile = 0;

}

Tile::~Tile(){
    
}

void Tile::initLetterCount(){
    
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int counts[] = {9, 2, 2, 4, 12, 2, 3, 2, 9, 1, 1, 4, 2, 6, 8, 2, 1, 6, 4, 6, 4, 2, 2, 1, 2, 1};

    for (size_t i = 0; i < alphabet.length(); i++) {
        letterCounts[alphabet[i]] = counts[i];
    }
}

void Tile::printLetterCounts() {
    for (auto const& pair: letterCounts) {
        std::cout << "{" << pair.first << ": " << pair.second << "}" << std::endl;
    }
}

int Tile::getRemainingTiles(){
    for (auto const& pair: letterCounts){
        remainingTile += pair.second;
    }
    return this->remainingTile;
}
std::map<char, unsigned int> Tile::getLetterCounts() const{
    return letterCounts;
}

void Tile::setLetterCounts(std::map<char, unsigned int> updatedMap){
    letterCounts = updatedMap;
}

void Tile::initValues(){
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int counts[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

    for (size_t i = 0; i < alphabet.length(); i++) {
        charValues[alphabet[i]] = counts[i];
    }
    
}

void Tile::mapBonusTiles(){
    bonusTile[{0, 0}] = 'T';
    bonusTile[{0, 3}] = 'd';
    bonusTile[{0, 7}] = 'T';
    bonusTile[{0, 11}] = 'd';
    bonusTile[{0, 14}] = 'T';

    bonusTile[{1, 1}] = 'D';
    bonusTile[{1, 5}] = 't';
    bonusTile[{1, 9}] = 't';
    bonusTile[{1, 13}] = 'D';

    bonusTile[{2, 2}] = 'D';
    bonusTile[{2, 6}] = 'd';
    bonusTile[{2, 8}] = 'd';
    bonusTile[{2, 12}] = 'D';

    bonusTile[{3, 0}] = 'd';
    bonusTile[{3, 3}] = 'D';
    bonusTile[{3, 7}] = 'd';
    bonusTile[{3, 11}] = 'D';
    bonusTile[{3, 14}] = 'd';

    bonusTile[{4, 4}] = 'D';
    bonusTile[{4, 10}] = 'D';

    bonusTile[{5, 1}] = 't';
    bonusTile[{5, 5}] = 't';
    bonusTile[{5, 9}] = 't';
    bonusTile[{5, 13}] = 't';

    bonusTile[{6, 2}] = 'd';
    bonusTile[{6, 6}] = 'd';
    bonusTile[{6, 8}] = 'd';
    bonusTile[{6, 12}] = 'd';

    bonusTile[{7, 0}] = 'T';
    bonusTile[{7, 3}] = 'd';
    bonusTile[{7, 7}] = '*';
    bonusTile[{7, 11}] = 'd';
    bonusTile[{7, 14}] = 'T';

    bonusTile[{8, 2}] = 'd';
    bonusTile[{8, 6}] = 'd';
    bonusTile[{8, 8}] = 'd';
    bonusTile[{8, 12}] = 'd';

    bonusTile[{9, 1}] = 't';
    bonusTile[{9, 5}] = 't';
    bonusTile[{9, 9}] = 't';
    bonusTile[{9, 13}] = 't';

    bonusTile[{10, 4}] = 'D';
    bonusTile[{10, 10}] = 'D';

    bonusTile[{11, 0}] = 'd';
    bonusTile[{11, 3}] = 'D';
    bonusTile[{11, 7}] = 'd';
    bonusTile[{11, 11}] = 'D';
    bonusTile[{11, 14}] = 'd';

    bonusTile[{12, 2}] = 'D';
    bonusTile[{12, 6}] = 'd';
    bonusTile[{12, 8}] = 'd';
    bonusTile[{12, 12}] = 'D';

    bonusTile[{13, 1}] = 'D';
    bonusTile[{13, 5}] = 't';
    bonusTile[{13, 9}] = 't';
    bonusTile[{13, 13}] = 'D';

    bonusTile[{14, 0}] = 'T';
    bonusTile[{14, 3}] = 'd';
    bonusTile[{14, 7}] = 'T';
    bonusTile[{14, 11}] = 'd';
    bonusTile[{14, 14}] = 'T';
}

std::map<std::pair<int,int>, char> Tile::getBonusTiles(){
    return bonusTile;
}

char Tile::getBonusChar(int row, int col) const{
    auto pos = std::make_pair(row, col);
        if (bonusTile.count(pos)) {
            return bonusTile.at(pos);
        }
        return 'n';
    
}
int Tile::stringToValue(const std::string& word){
    int value = 0;
    for (char c : word){
        value += charValues[toupper(c)];
    }
    return value;
}

int Tile::getTileValue(const char& character){
    return charValues[character];
}



