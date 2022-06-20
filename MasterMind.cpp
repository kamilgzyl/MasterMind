#include "MasterMind.hpp"
#include <stdexcept>

namespace MM
{
bool MasterMind::tryParseUserInput(std::string& userInput, int& selectedOption)
{
    try
    {
        selectedOption = std::stoi(userInput);
    }
    catch (std::invalid_argument)
    {
        return false;
    }
    return true;
}

bool MasterMind::handleInvalidInput(unsigned tryNumber)
{
    if(tryNumber == NUM_OF_MENU_TRIES)
    {
        std::cout <<"Good bye!" << std::endl;
        return false;
    }
    else
    {
        std::cout <<"Invalid option. Please try again (remaning tries: " <<  NUM_OF_MENU_TRIES - tryNumber <<  ")."<< std::endl;
    }
    return true;
}



void MasterMind::run()
{
    bool isRunning = true;
    unsigned tryNumber = 0;
    do
    {
        showMenu();

        int selectedOption = 0;
        std::string userInput;
        getline(std::cin, userInput);
        if(tryParseUserInput(userInput, selectedOption))
        {
            isRunning = handleSelectedOption(selectedOption, tryNumber);
        }
        else
        {
            isRunning = handleInvalidInput(++tryNumber);
        }
    }
    while(isRunning);
}

bool MasterMind::handleSelectedOption(int selectedOption, unsigned& tryNumber)
{
    bool shouldContinue = true;
    switch(selectedOption)
    {
        case static_cast<int>(EMenuOption::START):
        {
            system("clear");
            startGame();
            tryNumber = 0;
        }
        break;
        case static_cast<int>(EMenuOption::EXIT):
        {
            std::cout <<"Good bye!" << std::endl;
            shouldContinue = false;
        }
        break;

        default:
        {
            shouldContinue = handleInvalidInput(++tryNumber);
        }
        break;
    }
    return shouldContinue;
}

 void MasterMind::showMenu()
{
    std::stringstream menuOutput;
    menuOutput << "Hello in MasterMind!" << std::endl;
    menuOutput << "Choose option: " << std::endl;
    menuOutput << "\t 1. Start Game." << std::endl;
    menuOutput << "\t 2. Exit." << std::endl;

    std::cout << menuOutput.str();
}

std::vector<EColor> MasterMind::generateSecreteCode()
{
    std::vector<EColor> pegVec;
    for(unsigned i = 0; i < NUMBER_OF_PEGS; ++i)
    {
        pegVec.push_back(static_cast<EColor>(RandomGenerator::generateNumber(FIRST_CODE_PEG_COLOR_IDX, FIRST_CODE_PEG_COLOR_IDX + NUM_OF_BIG_PEGS_COLORS)));
    }
    return pegVec;
}

void MasterMind::startGame()
{
    const std::vector<EColor> secreteCode = generateSecreteCode();
    Board board(NUM_OF_TRIES);

    unsigned tryNumber = 0;
    while(tryNumber < NUM_OF_TRIES)
    {
        system("clear");
        printColorLegend();

        board.show();

        auto playerAttempt = takeGuessFromPlayer();

        std::unordered_map<EColor, int> correctPegMap;
        unsigned numOfCorrectPeg = markCorrectGuess(board, tryNumber, secreteCode, playerAttempt, correctPegMap);
        if(isDecoded(numOfCorrectPeg))
        {
            printVictory();
            return;
        }
        markPegExistWrongPlace(board, tryNumber, secreteCode, playerAttempt, correctPegMap);
        tryNumber++;
    }
    system("clear");
    printColorLegend();
    board.show();
    printDefeat(secreteCode);
}

unsigned MasterMind::markCorrectGuess(Board& board,
                                      unsigned tryNumber,
                                      const std::vector<EColor>& secreteCode,
                                      const std::vector<EColor>& playerAttempt,
                                      std::unordered_map<EColor, int>& correctPegMap)
{
    unsigned numOfCorrectPeg = 0;
    for(size_t pos = 0; pos < playerAttempt.size(); ++pos)
    {
        board.put(tryNumber, pos, colorToChar(playerAttempt[pos]));

        if(playerAttempt[pos] == secreteCode[pos])
        {
            numOfCorrectPeg++;
            correctPegMap[playerAttempt[pos]]++;
            board.putOnFirstFree(tryNumber, colorToChar(EColor::BLACK));
        }
    }
    return numOfCorrectPeg;
}

void MasterMind::markPegExistWrongPlace(Board& board,
                                        unsigned tryNumber,
                                        const std::vector<EColor>& secreteCode,
                                        const std::vector<EColor>& playerAttempt,
                                        std::unordered_map<EColor, int>& correctPegMap)
{
    for(size_t pos = 0; pos < playerAttempt.size(); ++pos)
    {
        if(correctPegMap[playerAttempt[pos]] == std::count(secreteCode.begin(), secreteCode.end(), playerAttempt[pos]))
        {
            continue;
        }
        if(correctPegMap[playerAttempt[pos]] < std::count(secreteCode.begin(), secreteCode.end(), playerAttempt[pos]) &&
           std::count(playerAttempt.begin(), playerAttempt.end(), playerAttempt[pos]) >  correctPegMap[playerAttempt[pos]])
        {
            correctPegMap[playerAttempt[pos]]++;
            board.putOnFirstFree(tryNumber,  colorToChar(EColor::WHITE));
        }
    }
}

inline bool MasterMind::isDecoded(unsigned numOfCorrectPeg)
{
    return numOfCorrectPeg == NUMBER_OF_PEGS;
}

void MasterMind::printVictory()
{
    std::cout <<"\n\n Y O U   W I N\n\n\n"<<std::endl;
}

void MasterMind::printDefeat(const std::vector<EColor>& secreteCode)
{
    std::cout <<"\n\n Y O U   L O S E\n\n\n"<<std::endl;
    std::cout << "Sercret code:" << std::endl;
    std::stringstream output;
    for(auto c : secreteCode)
    {
        output << colorToChar(c) << " ";
    }
    output <<std::endl<<std::endl<<std::endl;
    std::cout << output.str();
}

void MasterMind::printColorLegend()
{
    std::stringstream legenOutput;
    legenOutput << "Hint Peg colors:" << std::endl;
    legenOutput << "| ";
    for( const auto& color : colorSmallPegVec )
    {
        legenOutput << colorToString(color) << ": " << colorToChar(color) << " | ";
    }
    legenOutput << std::endl << std::endl;
    legenOutput << "Code Peg colors:" << std::endl;
    legenOutput << "| ";
    for( const auto& color : colorBigPegVec )
    {
        legenOutput << colorToString(color) << ": " << colorToChar(color) << " | ";
    }
    legenOutput << std::endl;
    std::cout << legenOutput.str();
}

bool MasterMind::isGuessValid(std::string& guess)
{
    if(guess.length() > NUMBER_OF_PEGS)
    {
        return false;
    }
    for(auto c : guess)
    {
        if(std::find(colorBigPegCharVec.begin(), colorBigPegCharVec.end(), c) == colorBigPegCharVec.end())
        {
            return false;
        }
    }
    return true;
}

std::vector<EColor> MasterMind::takeGuessFromPlayer()
{
    std::string guess{};
    std::vector<EColor> playerCode;
    while(true)
    {
        std::cin >> guess;
        std::cin.ignore();
        for (auto& c: guess)
        {
            c = toupper(c); //convert to UPPER CASE
        }
        if(isGuessValid(guess))
        {
            for(auto& c : guess)
            {
                playerCode.push_back(charToColor(c));
            }
            break;
        }
        else
        {
            std::cout <<"Invalid input, please try again" <<std::endl;
        }
    }
    return playerCode;
}
} //namespace MM
