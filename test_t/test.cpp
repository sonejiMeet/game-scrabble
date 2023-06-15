#include <iostream>
#include <memory>
#include <cstring>
#include <cassert>
#include "../src/scrabble.h"
#include "../src/tile.h"
#include "../src/player.h"
#include "../src/word.h"
#include "../src/colors.h"

bool mapsAreEqual(const std::map<char, unsigned int>& map1, const std::map<char, unsigned int>& map2) {
    if (map1.size() != map2.size())
        return false;

    for (auto const& pair : map1) {
        if (map2.count(pair.first) == 0 || map2.at(pair.first) != pair.second) {
            return false;
        }
    }

    return true;
}

int main(void){
    std::shared_ptr<Scrabble> board = std::make_shared<Scrabble>();
    std::shared_ptr<Tile> tile = std::make_shared<Tile>();
    int expectedScore1 = 8; // Score for "HELLO" should be 8
    int expectedScore2 = 14; // Score for "SCRABBLE" should be 14

    int score1 = tile->stringToValue("HELLO");
    int score2 = tile->stringToValue("SCRABBLE");

    if (score1 != expectedScore1) {
        throw std::runtime_error("Test case failed: Expected score1 = 8, Actual score1 = " + std::to_string(score1));
    }

    if (score2 != expectedScore2) {
        throw std::runtime_error("Test case failed: Expected score2 = 14, Actual score2 = " + std::to_string(score2));
    }

    // Additional test cases can be added here
    char expectedChar1 = 'D'; // Bonus character at row 1, column 1 should be 'D'
    char expectedChar2 = 'T'; // Bonus character at row 2, column 3 should be 'T'

    char bonusChar1 = tile->getBonusChar(1, 1);
    char bonusChar2 = tile->getBonusChar(7, 0);

    if (bonusChar1 != expectedChar1) {
        throw std::runtime_error("Test case failed: Expected bonusChar1 = 'D', Actual bonusChar1 = " + std::to_string(bonusChar1));
    }

    if (bonusChar2 != expectedChar2) {
        throw std::runtime_error("Test case failed: Expected bonusChar2 = 'T', Actual bonusChar2 = " + std::to_string(bonusChar2));
    }


    {  // test drawTiles()
        Player player(tile);

        std::map<char, unsigned int> expectedCounts = tile->getLetterCounts();
        
        player.drawTiles();
        std::vector<char> playerTiles = player.getTiles();
        
        for (int i = 0; i < 7; i++) {
            expectedCounts[playerTiles[i]]--;
        }
        if (!mapsAreEqual(tile->getLetterCounts(), expectedCounts))
            std::cerr << "Test failed: illegal drawing of tiles" << std::endl;    
    }

    {   //testing isValidWord()
        Word word(board);

        std::string insertWord = "Bruh";
        std::string notInsertWord = "OK";
        
        word.addValidWord(insertWord);

        if(word.isValidWord(insertWord)){
            std::cerr << ANSI_B_RED << "Test failed: insertWord is not in the database." << ANSI_reset << std::endl;
        }

        if(!word.isValidWord(notInsertWord)){
            std::cerr << ANSI_B_RED << "Test failed: notInsertWord is not in the database." << ANSI_reset << std::endl;
        }
    }

    {   //testing checkWord()
        Word word(board);
        std::string valid_checkWordInDictionary = "word";
        std::string invalid_checkwordInDictionary = "wrod";

        if(word.checkWord(valid_checkWordInDictionary) == false){
            std::cerr << ANSI_B_RED << "checkWord() doesnt work for a valid word: Expected true but returns false" << ANSI_COLOR_RESET << std::endl;
        }
        if(word.checkWord(invalid_checkwordInDictionary) == true){
            std::cerr << ANSI_B_RED << "checkWord() doesnt work for invalid word: Expected false but returns true otherwise" << ANSI_COLOR_RESET << std::endl;
        }
    }



    { // testing getWordFromBoard()
        std::shared_ptr<Scrabble> board = std::make_shared<Scrabble>();
        
        Word word(board);
        
        board->setBoard(4, 4, 't');
        board->setBoard(4, 5, 'e');
        board->setBoard(4, 6, 's');
        board->setBoard(4, 7, 't');
        board->setBoard(4, 8, 'i');
        board->setBoard(4, 9, 'n');
        board->setBoard(4, 10, 'g');
        
        int mainWordPlacement = 4; // row positon of the word

        std::string result = word.getWordFromBoard(mainWordPlacement,4,10, HORIZONTAL);
        
        if(result != "TESTING")
            std::cerr << ANSI_B_RED << "getWordFromBoard() failed, Expected word: TESTING, Result: " << result << ANSI_COLOR_RESET << std::endl;
    }



    {   // testing playerScore function
        std::shared_ptr<Scrabble> board = std::make_shared<Scrabble>();
        std::shared_ptr<Tile> tile = std::make_shared<Tile>();
        Word word(board);
        Player player(tile);

        board->setBoard(4, 3, 't');
        board->setBoard(4, 4, 'e');
        board->setBoard(4, 5, 's');
        board->setBoard(4, 6, 't');

        int mainWordPlacement = 4; // row positon of the word

        std::string word1 = word.getWordFromBoard(mainWordPlacement, 3, 6, HORIZONTAL);
        player.calculatePlayerScore(word1, mainWordPlacement, 3, 6, HORIZONTAL);

        if(player.getScore() != 8){
            std::cerr << "Expected result: 8, Result got:" << player.getScore() << std::endl;
        }
    }
    {
        std::shared_ptr<Scrabble> board = std::make_shared<Scrabble>();
        std::shared_ptr<Tile> tile = std::make_shared<Tile>();
        Word word(board);
        Player player(tile);

        board->setBoard(1, 1, 'S');
        board->setBoard(1, 2, 'c');
        board->setBoard(1, 3, 'r');
        board->setBoard(1, 4, 'a');
        board->setBoard(1, 5, 'b');
        board->setBoard(1, 6, 'b');
        board->setBoard(1, 7, 'l');
        board->setBoard(1, 8, 'e');

        int mainWordPlacement2 = 1; // row positon of the word

        std::string word2 = word.getWordFromBoard(mainWordPlacement2, 1, 8, HORIZONTAL);
        player.calculatePlayerScore(word2, mainWordPlacement2, 1, 8, HORIZONTAL);

        if(player.getScore() != 37){
            std::cerr << "Expected result: 37, Result got:" << player.getScore() << std::endl;
        }
    }
    {
        std::shared_ptr<Scrabble> board = std::make_shared<Scrabble>();
        std::shared_ptr<Tile> tile = std::make_shared<Tile>();
        Word word(board);
        Player player(tile);

        board->setBoard(1, 13, 'm');
        board->setBoard(2, 13, 'a');
        board->setBoard(3, 13, 'k');
        board->setBoard(4, 13, 'e');
        board->setBoard(5, 13, 'r');

        int mainWordPlacement3 = 13; // col positon of the word

        std::string word3 = word.getWordFromBoard(mainWordPlacement3,1,5, VERTICAL);
        player.calculatePlayerScore(word3, mainWordPlacement3, 1, 5, VERTICAL);
        if(player.getScore() != 25){
            std::cerr << "Expected result: 25, Result got:" << player.getScore() << std::endl;
        }
    }
    {
        std::shared_ptr<Scrabble> board = std::make_shared<Scrabble>();
        std::shared_ptr<Tile> tile = std::make_shared<Tile>();
        Word word(board);
        Player player(tile);

        board->setBoard(7, 6, 'S');
        board->setBoard(7, 7, 'o');
        board->setBoard(7, 8, 'd');
        board->setBoard(7, 9, 'a');

        int mainWordPlacement4 = 7; // row positon of the word

        std::string word4 = word.getWordFromBoard(mainWordPlacement4 ,6,9, HORIZONTAL);
        player.calculatePlayerScore(word4, mainWordPlacement4, 6, 9, HORIZONTAL);
        if(player.getScore() != 10){
            std::cerr << "Expected result: 10, Result got:" << player.getScore() << std::endl;
        }
    }
    {
        std::shared_ptr<Scrabble> board = std::make_shared<Scrabble>();
        std::shared_ptr<Tile> tile = std::make_shared<Tile>();
        Word word(board);
        Player player(tile);

        board->setBoard(7, 6, 'G');
        board->setBoard(8, 6, 'A');
        board->setBoard(9, 6, 'N');
        board->setBoard(10, 6, 'G');

        int mainWordPlacement4 = 6; // row positon of the word

        std::string word4 = word.getWordFromBoard(mainWordPlacement4 ,7,10, VERTICAL);
        player.calculatePlayerScore(word4, mainWordPlacement4, 7, 10, VERTICAL);
        if(player.getScore() != 7){
            std::cerr << "Expected result: 7, Result got:" << player.getScore() << std::endl;
        }
    }

    std::cout << "\nEnd of tests\n" << std::endl;
    return 0;
}