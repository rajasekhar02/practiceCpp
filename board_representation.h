#ifndef BOARD_REPRESENTATION_H
#define BOARD_REPRESENTATION_H
#include <string>
#include <iostream>
namespace Chess
{

    namespace Piece
    {
        /**
         * @brief 5 bits are used to encode the pieces
         *  Starting the from little endian
         * -----------------------------
         * Piece type
         * -----------------------------
         * 1 st bit is diagonal moving
         * 2 nd bit is straight
         * 3 rd bit is sliding piece
         * ----------------------------
         * Color Representation bits
         * --------------------------
         * 4 th bit is white
         * 5 th bit is black
         *
         */
        const int None = 0;

        const int King = 1;

        const int Pawn = 2;

        const int Knight = 3;

        const int Bishop = 5;

        const int Rook = 6;

        const int Queen = 7;

        const int White = 8;

        const int Black = 16;

        const int typeMask = 0b00111;

        const int blackMask = 0b10000;

        const int whiteMask = 0b01000;

        const int colourMask = whiteMask | blackMask;

        bool IsGivenColour(int piece, int colour)
        {
            return (piece & colourMask) == colour;
        }

        int getPieceColour(int piece)
        {
            return piece & colourMask;
        }

        int getPieceType(int piece)
        {
            return piece & typeMask;
        }

        bool isRookOrQueen(int pieceType)
        {
            return (pieceType & 0b110) == 0b110;
        }

        bool isBishopOrQueen(int pieceType)
        {
            return (pieceType & 0b101) == 0b101;
        }

        bool isSlidingPiece(int pieceType)
        {
            return (pieceType & 0b100) != 0;
        }
    }
    namespace BoardRepresentation
    {
        struct PieceList
        {
            int *occupiedSquares;
            int *map;
            int numPieces;

            PieceList(int maxPieceCount = 16)
            {
                occupiedSquares = new int[maxPieceCount]();
                map = new int[64]();
                numPieces = 0;
            }

            void addPieceAtSquare(int square)
            {
                occupiedSquares[numPieces] = square;
                map[square] = square;
                numPieces++;
            }

            void removePieceAtSquare(int square)
            {
                int pieceIndex = map[square];
                occupiedSquares[pieceIndex] = occupiedSquares[numPieces - 1];
                map[occupiedSquares[pieceIndex]] = pieceIndex;
                numPieces--;
            }

            void MovePiece(int startSquare, int targetSquare)
            {
                int pieceIndex = map[startSquare];
                occupiedSquares[pieceIndex] = targetSquare;
                map[targetSquare] = pieceIndex;
            }

            const int operator[](int index) const
            {
                return occupiedSquares[index];
            }
        };
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
        const std::string fileNames = std::string("abcdefgh");
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
            return squareIndex & 7;
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
            return (fileNames[fileIndex] + std::to_string(rankIndex + 1));
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