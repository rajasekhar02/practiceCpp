//
// Created by rp6kp on 3/14/2022.
//

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include "utils.h"
#include "chess_board.h"
using namespace std;

ChessBoard::ChessBoard()
{
    initGrid();
    turn = "WHITE";
}

ChessBoard::ChessBoard(string fenString)
{
    grid = getBoardFromFenString(fenString);
    turn = getTurnStringFromFenString(fenString);
    castlesAvailBlack = getAvailableCastlesBySide(fenString, "BLACK");
    castlesAvailWhite = getAvailableCastlesBySide(fenString, "WHITE");
}

string ChessBoard::getAvailableCastlesBySide(string fenString, string side)
{
    vector<string> fenComponents = utils::split(fenString);
    map<string, string> sidesToPieces = {
        {"BLACK", "prnbqk"},
        {"WHITE", "PRNBQK"}};
    map<string, int (*)(int)> sidesToCaseFunctions = {
        {"BLACK", islower},
        {"WHITE", isupper}};
    string availableCastles = fenComponents[2];
    if (availableCastles == "-")
    {
        return "-";
    }
    int i = 0;
    char ch = availableCastles[i];
    string availCastles = "";
    while (i < availableCastles.size())
    {
        if (sidesToPieces[side].find("" + ch) && sidesToCaseFunctions[side](ch))
        {
            availCastles = availCastles + ch;
        }
        i++;
        ch = availableCastles[i];
    }
    return availCastles;
}

string ChessBoard::getBoardStringFromFenString(string fenString)
{
    vector<string> fenComponents = utils::split(fenString);
    return fenComponents[0];
}

string ChessBoard::getTurnStringFromFenString(string fenString)
{
    vector<string> fenComponents = utils::split(fenString);
    cout << fenComponents[1] << endl;
    if (fenComponents[1] == "b")
    {
        return "BLACK";
    }
    return "WHITE";
}

string *ChessBoard::getBoardFromFenString(string fenString)
{
    vector<string> board = utils::split(getBoardStringFromFenString(fenString), '/');
    string *chessGrid = new string[8];
    for (int eachRow = 0; eachRow < 8; eachRow++)
    {
        string chessBoardRow = "........";
        int prevPosition = 0;
        string cells = board[eachRow];
        for (int eachCol = 0; eachCol < cells.size(); eachCol++)
        {
            if (isalpha(cells[eachCol]))
            {
                chessBoardRow[prevPosition] = cells[eachCol];
                prevPosition++;
                continue;
            }
            prevPosition += utils::charToInt(cells[eachCol]);
        }
        chessGrid[eachRow] = chessBoardRow;
    }
    return chessGrid;
}

void ChessBoard::initGrid()
{
    for (int eachRow = 0; eachRow < 8; eachRow++)
    {
        string str = "";
        for (int eachCol = 0; eachCol < 8; eachCol++)
        {
            str += '.';
        }
        grid[eachRow] = str;
    }
}

ostream &ChessBoard::printGrid(ostream &os)
{
    for (int eachRow = 0; eachRow < 8; eachRow++)
    {
        os << grid[eachRow] << endl;
    }
    return os;
}

ostream &operator<<(ostream &os, ChessBoard chessBoard)
{
    os << "from the operator overloading" << endl;
    if (chessBoard.turn == "WHITE")
    {
        os << "Whites to play" << '\n';
    }
    else
    {
        os << "Blacks to play" << '\n';
    }
    chessBoard.printGrid(os);
    cout << chessBoard.castlesAvailBlack << endl;
    cout << chessBoard.castlesAvailWhite << endl;
    return os;
}
