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
using namespace std;
namespace Chess
{
    class ChessBoard
    {
    public:
        string *grid;
        int flatBoard[64];
        string turn;
        string castlesAvailBlack;
        string castlesAvailWhite;
        string enpassantSquare;
        int halfMoves;
        long long int moves;

        long long int WP = 0l;
        long long int WN = 0l;
        long long int WB = 0l;
        long long int WR = 0l;
        long long int WQ = 0l;
        long long int WK = 0l;

        long long int BP = 0l;
        long long int BN = 0l;
        long long int BB = 0l;
        long long int BR = 0l;
        long long int BQ = 0l;
        long long int BK = 0l;

        ChessBoard();

        ChessBoard(string fenString);

        string getAvailableCastlesBySide(string fenString, string side);

        string getBoardStringFromFenString(string fenString);

        string getTurnStringFromFenString(string fenString);

        string *getBoardFromFenString(string fenString);

        void initGrid();

        void initFlatBoard();

        void arrayToBitBoards();

        long long int convertStringToBitBoard(std::string binary);

        void drawArray();

        ostream &printGrid(ostream &os);
    };
    ostream &operator<<(ostream &os, ChessBoard chessBoard);
}
#endif // CHESS_CHESS_BOARD_H
