#include "Board.hpp"

namespace MM
{
void Board::show()
{
    printTopBottomEdge();
    printRows();
    printTopBottomEdge();
}

void Board::printTopBottomEdge()
{
    std::cout << "+";
    for(size_t i = 0; i < NUMBER_OF_PEGS; ++i)
    {
        std::cout<<"---";
    }
    std::cout<<"+" << std::endl;
}

void Board::printRows()
{
    for(size_t tryNum = 0; tryNum < numOfTries; ++tryNum)
    {
        std::cout << "|";
        for(size_t bigPegPosition = 0; bigPegPosition < NUMBER_OF_PEGS; ++bigPegPosition)
        {
            std::cout << " " << pegArray[getPositionInVector(tryNum, bigPegPosition)]  << " ";
        }
        std::cout << "|\t";
        for(size_t smallPegPosition = 0; smallPegPosition < NUMBER_OF_PEGS; ++smallPegPosition)
        {
            std::cout <<pegArray[getPositionInVector(tryNum, NUMBER_OF_PEGS + smallPegPosition)] << " ";
        }
        std::cout<<std::endl;
    }
}

unsigned Board::getPositionInVector(unsigned tryNum, unsigned positionInTry)
{
    return tryNum * NUMBER_OF_PEGS_PER_ROW + positionInTry;
}

void Board::put(size_t tryNum, size_t position, char colorChar)
{
    pegArray[getPositionInVector(tryNum, position)] = colorChar;
}

void Board::putOnFirstFree(size_t tryNum, char colorChar)
{
    for(unsigned smallPegPosition = 0; smallPegPosition < NUMBER_OF_PEGS; ++smallPegPosition)
    {
        unsigned positionInPegVec = getPositionInVector(tryNum, NUMBER_OF_PEGS + smallPegPosition);
        if(pegArray[positionInPegVec] == EMPTY_FIELD)
        {
            pegArray[positionInPegVec] = colorChar;
            return;
        }
    }
}
} //namespace MM