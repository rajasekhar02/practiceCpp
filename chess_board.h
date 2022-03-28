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
class ChessBoard
{
public:
    string *grid;
    string turn;
    string castlesAvailBlack;
    string castlesAvailWhite;
    int halfMoves;
    long long int moves;

    ChessBoard();

    ChessBoard(string fenString);

    string getAvailableCastlesBySide(string fenString, string side);

    string getBoardStringFromFenString(string fenString);

    string getTurnStringFromFenString(string fenString);

    string *getBoardFromFenString(string fenString);

    void initGrid();

    ostream &printGrid(ostream &os);
};

ostream &operator<<(ostream &os, ChessBoard chessBoard);

#endif // CHESS_CHESS_BOARD_H
