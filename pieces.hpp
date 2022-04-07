

#ifndef CHESS_PIECES_H
#define CHESS_PIECES_H
#include "chess_board.h"
#include <string>
namespace Chess
{
    int countDoubledPawns(GamePosition board, std::string color);
    int countBlockedPawns(GamePosition board, std::string color);
    int countIsolatedPawns(GamePosition board, std::string color);
}
#endif