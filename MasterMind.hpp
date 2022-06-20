#pragma once
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include "RandomGenerator.hpp"
#include "EColor.hpp"
#include "Board.hpp"
#include "Defs.hpp"


namespace MM
{
enum class EMenuOption
{
    START = 1,
    EXIT = 2
};

class MasterMind
{
    public:
        void run();
    private:
        void showMenu();
        void startGame();
        std::vector<EColor> generateSecreteCode();
        std::vector<EColor> takeGuessFromPlayer();
        bool isGuessValid(std::string& guess);
        void printColorLegend();
        void printVictory();
        void printDefeat(const std::vector<EColor>& secreteCode);
        bool tryParseUserInput(std::string& input, int& selectedOption);
        bool handleInvalidInput(unsigned tryNumber);
        bool handleSelectedOption(int selectedOption, unsigned& tryNumber);
        unsigned markCorrectGuess(Board& board,
                                  unsigned tryNumber, 
                                  const std::vector<EColor>& secreteCode,
                                  const std::vector<EColor>& playerAttempt,
                                  std::unordered_map<EColor, int>& correctPegMap);
        
        void markPegExistWrongPlace(Board& board,
                                    unsigned tryNumber, 
                                    const std::vector<EColor>& secreteCode,
                                    const std::vector<EColor>& playerAttempt,
                                    std::unordered_map<EColor, int>& correctPegMap);;
                      
        inline bool isDecoded(unsigned numOfCorrectPeg);

};
} //namespace MM