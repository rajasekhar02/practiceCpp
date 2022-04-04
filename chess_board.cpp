//
// Created by rp6kp on 3/14/2022.
//

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include "utils.h"
#include "board_representation.h"
#include "chess_board.h"
#include "fen_utils.h"
using namespace std;
namespace Chess
{
    ChessBoard::ChessBoard()
    {
        initGrid();
        turn = "WHITE";
    }

    ChessBoard::ChessBoard(string fenString)
    {
        grid = fen::getBoardFromFenString(fenString);
        turn = fen::getTurnStringFromFenString(fenString);
        enpassantSquare = fen::getEnpassantSquareFromFenString(fenString);
        halfMoves = fen::getTotalHalfMovesFromFenString(fenString);
        moves = fen::getTotalMovesFromFenString(fenString);
        castlesAvailBlack = fen::getAvailableCastlesBySide(fenString, "BLACK");
        castlesAvailWhite = fen::getAvailableCastlesBySide(fenString, "WHITE");
        arrayToBitBoards();
        initFlatBoard();
    }

    void ChessBoard::initFlatBoard()
    {
        for (int i = 0; i < 64; i++)
        {
            char piece = grid[(i / 8)][(i % 8)];
            if (piece == '.')
                continue;
            int pieceColor = isupper(piece) ? Piece::white : Piece::black;
            int pieceType = Piece::pieceSymbolToPieceType.at(tolower(piece));
            flatBoard[i] = pieceColor | pieceType;
        }
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

    void ChessBoard::arrayToBitBoards()
    {
        string binary;
        map<char, long long int *> pieceToBitBoard = {
            {'P', &WP},
            {'N', &WN},
            {'B', &WB},
            {'R', &WR},
            {'Q', &WQ},
            {'K', &WK},
            {'p', &BP},
            {'n', &BN},
            {'b', &BB},
            {'r', &BR},
            {'q', &BQ},
            {'k', &BK}};
        // iterate over all the cells in the grid
        for (int i = 0; i < 64; i++)
        {
            binary = string("0000000000000000000000000000000000000000000000000000000000000000");
            binary = binary.substr(i + 1) + "1" + binary.substr(0, i);
            if (grid[i / 8][i % 8] != '.')
            {
                *pieceToBitBoard[grid[i / 8][i % 8]] += convertStringToBitBoard(binary);
            }
        }
    }

    long long int ChessBoard::convertStringToBitBoard(string binary)
    {
        if (binary[0] == '0')
        {
            return stoll(binary, nullptr, 2);
        }
        return stoll(string("1") + binary.substr(2), nullptr, 2) * 2;
    }

    void ChessBoard::drawArray()
    {
        string chessBoard[8];
        for (int i = 0; i < 8; i++)
        {
            chessBoard[i] = string("........");
        }
        for (int i = 0; i < 64; i++)
        {
            if (((WP >> i) & 1) == 1)
            {
                chessBoard[i / 8][i % 8] = 'P';
            }
            if (((WN >> i) & 1) == 1)
            {
                chessBoard[i / 8][i % 8] = 'N';
            }
            if (((WB >> i) & 1) == 1)
            {
                chessBoard[i / 8][i % 8] = 'B';
            }
            if (((WR >> i) & 1) == 1)
            {
                chessBoard[i / 8][i % 8] = 'R';
            }
            if (((WQ >> i) & 1) == 1)
            {
                chessBoard[i / 8][i % 8] = 'Q';
            }
            if (((WK >> i) & 1) == 1)
            {
                chessBoard[i / 8][i % 8] = 'K';
            }
            if (((BP >> i) & 1) == 1)
            {
                chessBoard[i / 8][i % 8] = 'p';
            }
            if (((BN >> i) & 1) == 1)
            {
                chessBoard[i / 8][i % 8] = 'n';
            }
            if (((BB >> i) & 1) == 1)
            {
                chessBoard[i / 8][i % 8] = 'b';
            }
            if (((BR >> i) & 1) == 1)
            {
                chessBoard[i / 8][i % 8] = 'r';
            }
            if (((BQ >> i) & 1) == 1)
            {
                chessBoard[i / 8][i % 8] = 'q';
            }
            if (((BK >> i) & 1) == 1)
            {
                chessBoard[i / 8][i % 8] = 'k';
            }
        }

        for (int eachRow = 0; eachRow < 8; eachRow++)
        {
            cout << chessBoard[eachRow] << endl;
        }
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
}
