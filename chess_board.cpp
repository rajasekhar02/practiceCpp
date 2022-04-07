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

namespace Chess
{
    int GamePosition::numSquaresToDirections[64][8];

    GamePosition::GamePosition()
    {
        initGrid();
        turn = "WHITE";
    }

    GamePosition::GamePosition(string fenString)
    {
        grid = getBoardFromFenString(fenString);
        turn = getTurnStringFromFenString(fenString);
        castlesAvailBlack = getAvailableCastlesBySide(fenString, "BLACK");
        castlesAvailWhite = getAvailableCastlesBySide(fenString, "WHITE");
        enpassantTargetSquare = getEnpassantFromFenString(fenString);
        halfMoves = getHalfMovesFromFenString(fenString);
        moves = getMovesFromFenString(fenString);
    }

    string GamePosition::getAvailableCastlesBySide(string fenString, string side)
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

    string GamePosition::getBoardStringFromFenString(string fenString)
    {
        vector<string> fenComponents = utils::split(fenString);
        return fenComponents[0];
    }

    string GamePosition::getEnpassantFromFenString(string fenString)
    {
        vector<string> fenComponents = utils::split(fenString);
        return fenComponents[3];
    }

    string GamePosition::getTurnStringFromFenString(string fenString)
    {
        vector<string> fenComponents = utils::split(fenString);
        cout << fenComponents[1] << endl;
        if (fenComponents[1] == "b")
        {
            return "BLACK";
        }
        return "WHITE";
    }

    string *GamePosition::getBoardFromFenString(string fenString)
    {
        vector<string> board = utils::split(getBoardStringFromFenString(fenString), '/');
        string *chessGrid = new string[8];
        for (int eachRow = 0; eachRow < 8; eachRow++)
        {
            string GamePositionRow = "........";
            int prevPosition = 0;
            string cells = board[eachRow];
            for (int eachCol = 0; eachCol < cells.size(); eachCol++)
            {
                if (isalpha(cells[eachCol]))
                {
                    GamePositionRow[prevPosition] = cells[eachCol];
                    prevPosition++;
                    continue;
                }
                prevPosition += utils::charToInt(cells[eachCol]);
            }
            chessGrid[eachRow] = GamePositionRow;
        }
        return chessGrid;
    }

    // pair<bool, string> GamePosition::validateFenString(string fenString)
    // {
    //     string errorMessages[] = {
    //         "VALID",
    //         "Some fields are missing in the Fen String",
    //         "Moves number Field should be positive and >=zero",
    //         "Half Moves number Field should be positive and >=zero",
    //         "Enpassant Target Square Field is Invalid",
    //         "Castling Availibity Field is Invalid",
    //         "Side To Move Field is Invalid",
    //         "Piece positions does not contain 8'/'-delimited rows",
    //         "Piece positions is invalid due to consecutive numbers",
    //         "PiecePositions is invalid due to invalid characters",
    //         "PiecePositions is invalid due to row count too large",
    //         "Illegal en-passant square"};
    //     pair<bool, string> validationResult;
    //     vector<string> fenComponents = utils::split(fenString, ' ');
    //     if (fenComponents.size() != 6)
    //     {
    //         return make_pair(false, errorMessages[1]);
    //     }
    //     try
    //     {
    //         int moves = stoi(fenComponents[5]);
    //         if (moves <= 0)
    //         {
    //             return make_pair(false, errorMessages[2]);
    //         }

    //     }
    //     catch (const std::invalid_argument &ia)
    //     {
    //         return make_pair(false, errorMessages[2]);
    //     }
    //     catch (const std::out_of_range &oor)
    //     {
    //         return make_pair(false, errorMessages[2]);
    //     }
    //     return make_pair(true, errorMessages[0]);
    // }
    void GamePosition::precomputeMoveData()
    {
        for (int file = 0; file < noOfFiles; file++)
        {
            for (int rank = 0; rank < noOfRanks; rank++)
            {
                int numNorth = 7 - rank;
                int numSouth = rank;
                int numWest = file;
                int numEast = 7 - file;

                int squareIndex = rank * 8 + file;

                numSquaresToDirections[squareIndex][0] = numNorth;
                numSquaresToDirections[squareIndex][1] = numSouth;
                numSquaresToDirections[squareIndex][2] = numWest;
                numSquaresToDirections[squareIndex][3] = numEast;
                numSquaresToDirections[squareIndex][1] = min(numNorth, numWest);
                numSquaresToDirections[squareIndex][1] = min(numSouth, numEast);
                numSquaresToDirections[squareIndex][1] = min(numNorth, numEast);
                numSquaresToDirections[squareIndex][1] = min(numSouth, numWest);
            }
        }
    }

    int GamePosition::getHalfMovesFromFenString(string fenString)
    {
        vector<string> fenComponents = utils::split(fenString);
        return stoi(fenComponents[4]);
    }

    int GamePosition::getMovesFromFenString(string fenString)
    {
        vector<string> fenComponents = utils::split(fenString);
        return stoi(fenComponents[5]);
    }

    void GamePosition::initGrid()
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

    ostream &GamePosition::printGrid(ostream &os)
    {
        for (int eachRow = 0; eachRow < 8; eachRow++)
        {
            os << grid[eachRow] << endl;
        }
        return os;
    }

    ostream &operator<<(ostream &os, GamePosition GamePosition)
    {
        if (GamePosition.turn == "WHITE")
        {
            os << "Whites to play" << '\n';
        }
        else
        {
            os << "Blacks to play" << '\n';
        }
        GamePosition.printGrid(os);
        os << GamePosition.castlesAvailBlack << endl;
        os << GamePosition.castlesAvailWhite << endl;
        os << GamePosition.enpassantTargetSquare << endl;
        os << GamePosition.halfMoves << endl;
        os << GamePosition.moves << endl;
        return os;
    }
}