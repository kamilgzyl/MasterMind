#include "EColor.hpp"

namespace MM
{
char colorToChar(const EColor& color)
{
    switch(color)
    {
        case EColor::WHITE:
            return 'W';
        case EColor::BLACK:
            return 'B';
        case EColor::YELLOW:
            return 'Y';
        case EColor::RED:
            return 'R';
        case EColor::GREEN:
            return 'G';
        case EColor::PINK:
            return 'P';
        case EColor::ORANGE:
            return 'O';
        case EColor::CYAN:
            return 'C';
        default: 
        {
            std::cout << __FUNCTION__ << "::NotSupported color: " << static_cast<int>(color) << std::endl;
            return 'X';
        }          
    }
}

EColor charToColor(const char& c)
{
    switch(c)
    {
        case 'W':
            return EColor::WHITE;
        case 'B':
            return EColor::BLACK;
        case 'Y':
            return EColor::YELLOW;
        case 'R':
            return EColor::RED;
        case 'G':
            return EColor::GREEN;
        case 'P':
            return EColor::PINK;
        case 'O':
            return EColor::ORANGE;
        case 'C':
            return EColor::CYAN;
        default: 
        {
            std::cout << __FUNCTION__ << "::NotSupported color: " << c << std::endl;
            return EColor::ORANGE;
        }   
    }
}

std::string colorToString(const EColor& color)
{
    switch(color)
    {
        case EColor::WHITE:
            return "WHITE";
        case EColor::BLACK:
            return "BLACK";
        case EColor::YELLOW:
            return "YELLOW";
        case EColor::RED:
            return "RED";
        case EColor::GREEN:
            return "GREEN";
        case EColor::PINK:
            return "PINK";
        case EColor::ORANGE:
            return "ORANGE";
        case EColor::CYAN:
            return "CYAN";
        default: 
        {
            std::cout << __FUNCTION__ << "::NotSupported color: " << static_cast<int>(color) << std::endl;
            return "INVALID";
        }          
    }
}
} //namespace MM