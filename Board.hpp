#pragma once
#include <iostream>
#include <vector>
#include "Defs.hpp"


namespace MM
{

constexpr char EMPTY_FIELD = 'X';
class Board
{
    public:
        Board(size_t _numOfTries) : numOfTries(_numOfTries), pegArray(_numOfTries * NUMBER_OF_PEGS_PER_ROW, EMPTY_FIELD)
        {
        }
        void show();
        void put(size_t tryNum, size_t position, char colorChar);
        void putOnFirstFree(size_t tryNum, char colorChar);
        
    private:
        void printTopBottomEdge();
        void printRows();
        size_t numOfTries;
        std::vector<char> pegArray;
        unsigned getPositionInVector(unsigned tryNum, unsigned positionInTry);
};
} //namespace MM