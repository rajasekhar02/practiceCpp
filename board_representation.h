#ifndef BOARD_REPRESENTATION_H
#define BOARD_REPRESENTATION_H
#include <string>
#include <iostream>
namespace Chess
{
    namespace Piece{

    }
    namespace BoardRepresentation
    {
        struct Coord
        {
            int fileIndex;
            int rankIndex;
            Coord(int fileIndex, int rankIndex)
            {
                this->fileIndex = fileIndex;
                this->rankIndex = rankIndex;
            }
            bool isWhiteSquare()
            {
                return (fileIndex + rankIndex) % 2 != 0;
            }

            const bool operator==(Coord other) const
            {
                return (this->fileIndex == other.fileIndex && this->rankIndex == other.rankIndex) ? 0 : 1;
            }
        };
        std::ostream &operator<<(std::ostream &os, Coord coord)
        {
            os << coord.fileIndex << " " << coord.rankIndex;
        }
        const std::string fileNames = std::string("abcedfgh");
        const std::string rankNames = std::string("12345678");
        const int a1 = 0;
        const int b1 = 1;
        const int c1 = 2;
        const int d1 = 3;
        const int e1 = 4;
        const int f1 = 5;
        const int g1 = 6;
        const int h1 = 7;

        const int a8 = 56;
        const int b8 = 57;
        const int c8 = 58;
        const int d8 = 59;
        const int e8 = 60;
        const int f8 = 61;
        const int g8 = 62;
        const int h8 = 63;

         int getRankIndex(int squareIndex)
        {
            return squareIndex >> 3;
        }

         int getFileIndex(int squareIndex)
        {
            return squareIndex & 0b000111;
        }

         int IndexFromCoord(int fileIndex, int rankIndex)
        {
            return rankIndex * 8 + fileIndex;
        }

         int IndexFromCoord(Coord coord)
        {
            return IndexFromCoord(coord.fileIndex, coord.rankIndex);
        }

         Coord getCoordFromIndex(int squareIndex)
        {
            return Coord(getFileIndex(squareIndex), getRankIndex(squareIndex));
        }

         bool getLightSquare(int fileIndex, int rankIndex)
        {
            return (fileIndex + rankIndex) % 2 != 0;
        }

         std::string getSquareNameFromCoordinate(int fileIndex, int rankIndex)
        {
            return std::to_string(fileNames[fileIndex]) + std::to_string(rankIndex + 1);
        }

         std::string getSquareNameFromIndex(int squareIndex)
        {
            Coord coor = getCoordFromIndex(squareIndex);
            return getSquareNameFromCoordinate(coor.fileIndex, coor.rankIndex);
        }

        std::string getSquareNameFromCoordinate(Coord coord)
        {
            return getSquareNameFromCoordinate(coord.fileIndex, coord.rankIndex);
        }
    }
}

#endif