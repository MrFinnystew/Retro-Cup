//
//  Color Text.hpp
//  Retro Cup
//
//  Created by Yu-El Cheong on 3/1/26.
//
#ifndef COLOR_TEXT_HPP
#define COLOR_TEXT_HPP

#include <string>

inline const std::string startText = "\033[";
inline const std::string endText = "m";
inline const std::string resetText = "\033[0m";

inline const std::string boldText = ";1";
inline const std::string italicsText = ";3";
inline const std::string blueText = ";34";
inline const std::string redText = ";31";
inline const std::string greenText = ";32";
inline const std::string yellowText = ";33";

inline const std::string startBlueText = "34";
inline const std::string startItalicsText = "3";
inline const std::string startRedText = "31";
inline const std::string startGreenText = "32";
inline const std::string startYellowText = "33";
inline const std::string startBoldText = "1";

#endif // COLOR_TEXT_HPP
