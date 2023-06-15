#include "player.h"
#include "colors.h"
/*
    TODO: 
*/
Player::Player(std::shared_ptr<Tile> tile) : tile(tile){
    
    score = 0;
    name = "";
    tiles.reserve(7);

    temp_prev_tile_set.reserve(7);
}

Player::~Player(){
    
}

void Player::displayPlayerInfo() {
    std::cout << "\n\t \t" << name << "'s turn! score -> " << score << " Tiles -> [ ";
    bool isFirstNonEmpty = true;
    for (const auto& tile : tiles) {
        if (tile != '\0') {
            if (isFirstNonEmpty) {
                std::cout << tile << " ";
                isFirstNonEmpty = false;
            } else {
                std::cout << tile << " ";
            }
        } else {
            std::cout << "_ ";
        }
    }
    std::cout << "]\n";
}

void Player::setScore(int score){
    this->score = score;
}
int Player::getScore() const{
    return score;
}

void Player::setName(std::string name){
    this->name = name;
}
std::string Player::getName()const{
    return name;
}

void Player::setTiles(const std::vector<char>& newTiles){
    tiles = newTiles;
}
std::vector<char> Player::getTiles(){
    return tiles;
}

void Player::inputName(const std::vector<std::string>& existingNames, int i) {
    while (true) {
        std::cout << "Enter player " << i << "'s name: ";
        if (i != 0) std::getline(std::cin, name);
        else {
            std::getline(std::cin, name);
            break;
        }
        if (std::find(existingNames.begin(), existingNames.end(), name) != existingNames.end()) {
            std::cout << "Name is already taken. Try another one.\n";
        } else {
            break;
        }
    }
}

void Player::saveCurrentTileSet(){
    temp_prev_tile_set = tiles;
}
void Player::revertToPrevSet(){
    tiles = temp_prev_tile_set; 
}

void Player::removeTile(char tile){
    for(std::vector<char>::size_type i = 0; i < tiles.size(); i++){
        if(tiles[i] == tile) {
            tiles[i] = '\0';
            break;
        }
    }
}
bool Player::doesTileExist(char tile){
    for(std::vector<char>::size_type i = 0; i < tiles.size(); i++){
        if(tiles[i] == tile) return true;
    }
    return false;
}

int Player::countNonEmptyTiles(){
    int count = 0;
    for (const auto& tile : tiles) {
        if (tile != '\0') {
            count++;
        }
    }
    return count;
}

void Player::drawTiles() {
    unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 g(seed); // Mersenne Twister engine

    auto letterCnts = tile->getLetterCounts();
    int total_count = 0;
    for (const auto& entry : letterCnts) {
        total_count += entry.second;
    }
    
    int missingTiles = 7 - countNonEmptyTiles();
    
    tiles.resize(7);

    for (int i = 0; i < missingTiles; i++) {
        if (total_count == 0) {
            tiles[i] = '\0';
            continue;
        }

        int rand_num = std::uniform_int_distribution<int>{0, total_count - 1}(g);
        char temp_tile = '\0';

        for (auto& entry : letterCnts) {
            rand_num -= entry.second;
            if (rand_num < 0) {
                temp_tile = entry.first;
                entry.second--;
                total_count--;
                break;
            }
        }
        for (auto& tile : tiles) {
            if (tile == '\0') {
                tile = temp_tile;
                break;
            }
        }
    }

    tile->setLetterCounts(letterCnts);
}

void Player::shuffleTiles(){
    std::random_shuffle(tiles.begin(), tiles.end());
}

void Player::swapTiles() {
    auto letterCnts = tile->getLetterCounts();
    for (const auto& t : tiles) {
        if (t != '\0') {
            letterCnts[t]++;
        }
    }
    tiles.clear();

    tile->setLetterCounts(letterCnts);
    // drawTiles();
}


bool Player::isTileSetEmpty(){
    return tiles.empty();
}
void Player::calculatePlayerScore(const std::string& word, int mainWordPlacement, int startingPosition, int endingPosition, Orientation wordOrientation) {
    int mainWordScore = tile->stringToValue(word);
    int additionalWordsScore = 0;


    for (int i = startingPosition; i <= endingPosition; i++) {
        char letter;
        char bonusChar;
        if (wordOrientation == VERTICAL) {
            letter = word[i - startingPosition];
            bonusChar = tile->getBonusChar(i, mainWordPlacement);
        } else {
            letter = word[i - startingPosition];
            bonusChar = tile->getBonusChar(mainWordPlacement, i);
        }

        if (bonusChar != 'n') {
            int tileScore = tile->getTileValue(letter);
            if (bonusChar == 'd' || bonusChar == 't') {
                
                tileScore *= (bonusChar == 'd' ? 2 : 3);
                additionalWordsScore += tileScore;
            } else if (bonusChar == 'D' || bonusChar == 'T') {
                tileScore = mainWordScore * (bonusChar == 'D' ? 2 : 3);
                additionalWordsScore += tileScore;
            }
            else { // if bonusChar == '*'
                tileScore = mainWordScore * 2;
                additionalWordsScore += tileScore;
            }    
    
        } 
        else {
            bool checker = false;

            for(int i = startingPosition; i <=endingPosition; i++){
                char bonusChar;
                if (wordOrientation == VERTICAL) {
                    bonusChar = tile->getBonusChar(i, mainWordPlacement);
                } else {
                    bonusChar = tile->getBonusChar(mainWordPlacement, i);
                }
                if(bonusChar == 'D' || bonusChar == 'T' || bonusChar == '*')
                    checker = true;
            }
            if(!checker) additionalWordsScore += tile->getTileValue(letter);
        }
    }

    score +=  additionalWordsScore;
 
}