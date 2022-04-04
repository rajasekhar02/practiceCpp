#ifndef FEN_UTILS_H
#define FEN_UTILS_H
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "utils.h"
namespace Chess
{
    namespace fen
    {
        std::string getAvailableCastlesBySide(std::string fenString, std::string side)
        {
            std::vector<std::string> fenComponents = utils::split(fenString);
            std::map<std::string, std::string> sidesToPieces = {
                {"BLACK", "prnbqk"},
                {"WHITE", "PRNBQK"}};
            map<std::string, int (*)(int)> sidesToCaseFunctions = {
                {"BLACK", islower},
                {"WHITE", isupper}};
            std::string availableCastles = fenComponents[2];
            if (availableCastles == "-")
            {
                return "-";
            }
            int i = 0;
            char ch = availableCastles[i];
            std::string availCastles = "";
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

        std::string getBoardStringFromFenString(std::string fenString)
        {
            std::vector<std::string> fenComponents = utils::split(fenString);
            return fenComponents[0];
        }

        std::string getTurnStringFromFenString(std::string fenString)
        {
            std::vector<std::string> fenComponents = utils::split(fenString);
            std::cout << fenComponents[1] << std::endl;
            if (fenComponents[1] == "b")
            {
                return "BLACK";
            }
            return "WHITE";
        }

        std::string getEnpassantSquareFromFenString(std::string fenString)
        {
            std::vector<std::string> fenComponents = utils::split(fenString);
            std::cout << fenComponents[3] << std::endl;
            return fenComponents[3];
        }

        int getTotalHalfMovesFromFenString(std::string fenString)
        {
            std::vector<std::string> fenComponents = utils::split(fenString);
            std::cout << fenComponents[4] << std::endl;
            return stoi(fenComponents[4]);
        }

        int getTotalMovesFromFenString(std::string fenString)
        {
            std::vector<std::string> fenComponents = utils::split(fenString);
            std::cout << fenComponents[5] << std::endl;
            return stoi(fenComponents[5]);
        }

        std::string *getBoardFromFenString(std::string fenString)
        {
            std::vector<std::string> board = utils::split(getBoardStringFromFenString(fenString), '/');
            std::string *chessGrid = new std::string[8];
            for (int eachRank = 7; eachRank >= 0; eachRank--)
            {
                std::string chessBoardRow = "........";
                int prevFile = 0;
                std::string cells = board[eachRank];
                for (int eachFile = 0; eachFile < cells.size(); eachFile++)
                {
                    if (isalpha(cells[eachFile]))
                    {
                        chessBoardRow[prevFile] = cells[eachFile];
                        prevFile++;
                        continue;
                    }
                    prevFile += utils::charToInt(cells[eachFile]);
                }
                chessGrid[8 - eachRank - 1] = chessBoardRow;
            }
            return chessGrid;
        }
    }
}
#endif