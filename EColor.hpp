#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>


namespace MM
{
enum class EColor
{
    WHITE = 1,
    BLACK,
    YELLOW,
    RED,
    GREEN,
    PINK,
    ORANGE,
    CYAN
};

char colorToChar(const EColor& color);
EColor charToColor(const char& c);
std::string colorToString(const EColor& color);


const std::vector<EColor> colorSmallPegVec{EColor::WHITE,EColor::BLACK};
const std::vector<char> colorSmallPegCharVec{'W', 'B'};

const std::vector<EColor> colorBigPegVec{EColor::YELLOW, EColor::RED, EColor::GREEN, EColor::PINK, EColor::ORANGE, EColor::CYAN};
const std::vector<char> colorBigPegCharVec{'Y', 'R', 'G', 'P', 'O', 'C'};

const std::vector<EColor> colorVec{EColor::WHITE, EColor::BLACK, EColor::YELLOW, EColor::RED, EColor::GREEN, EColor::PINK, EColor::ORANGE, EColor::CYAN};
const std::vector<char> colorCharVec{'W', 'B', 'Y', 'R', 'G', 'P', 'O', 'C' };
} //namespace MM