//
// Created by rp6kp on 3/14/2022.
//

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cstring>

#ifndef CHESS_CHESS_BOARD_H
#define CHESS_CHESS_BOARD_H

namespace Chess
{
    const int DirectionOffsets[8] = {8, -8, -1, 1, 7, -7, 9, -9};
    const int noOfFiles = 8;
    const int noOfRanks = 8;

    struct Move
    {
        int StartSquare;
        int TargetSquare;
    };

    struct GamePosition
    {
    public:
        static int numSquaresToDirections[64][8];
        std::string *grid;
        std::string turn;
        std::string castlesAvailBlack;
        std::string castlesAvailWhite;
        std::string enpassantTargetSquare;
        int halfMoves;
        long long int moves;

        GamePosition();

        GamePosition(std::string fenString);

        static void precomputeMoveData();

        std::string getAvailableCastlesBySide(std::string fenString, std::string side);

        std::string getBoardStringFromFenString(std::string fenString);

        std::string getTurnStringFromFenString(std::string fenString);

        std::string *getBoardFromFenString(std::string fenString);

        std::string getEnpassantFromFenString(std::string fenString);

        int getHalfMovesFromFenString(std::string fenString);

        int getMovesFromFenString(std::string fenString);

        void initGrid();

        // functions yet to be implemented

        GamePosition clone();

        std::string to_string();

        bool isOccupied(std::string *grid, int x, int y);

        bool isOccupiedby(std::string *grid, int x, int y, std::string color);

        bool isCheck(GamePosition position, string color);

        bool isCheckmate(GamePosition position, string color);

        bool isStalemate(GamePosition position);

        // static bool validateFenString(std::string fenString);
        std::ostream &printGrid(std::ostream &os);
    };
    std::ostream &operator<<(std::ostream &os, GamePosition GamePosition);
}
#endif // CHESS_CHESS_BOARD_H
