//
// Created by rp6kp on 3/14/2022.
//

#include <string>
#include <vector>

#ifndef CHESS_UTILS_H
#define CHESS_UTILS_H
namespace utils
{
    std::vector<std::string> split(std::string s, char c = ' ');
    int charToInt(char ch);
}
#endif // CHESS_UTILS_H
