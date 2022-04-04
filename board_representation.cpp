
#include <string>
#include <iostream>
#include "board_representation.h"
namespace Chess
{
    namespace Piece
    {
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

        PieceList::PieceList(int maxPieceCount)
        {
            occupiedSquares = new int[maxPieceCount]();
            map = new int[64]();
            numPieces = 0;
        }

        void PieceList::addPieceAtSquare(int square)
        {
            occupiedSquares[numPieces] = square;
            map[square] = square;
            numPieces++;
        }

        void PieceList::removePieceAtSquare(int square)
        {
            int pieceIndex = map[square];
            occupiedSquares[pieceIndex] = occupiedSquares[numPieces - 1];
            map[occupiedSquares[pieceIndex]] = pieceIndex;
            numPieces--;
        }

        void PieceList::movePiece(int startSquare, int targetSquare)
        {
            int pieceIndex = map[startSquare];
            occupiedSquares[pieceIndex] = targetSquare;
            map[targetSquare] = pieceIndex;
        }

        const int PieceList::operator[](int index) const
        {
            return occupiedSquares[index];
        }

        Coord::Coord(int fileIndex, int rankIndex)
        {
            this->fileIndex = fileIndex;
            this->rankIndex = rankIndex;
        }
        bool Coord::isWhiteSquare()
        {
            return (fileIndex + rankIndex) % 2 != 0;
        }

        const bool Coord::operator==(Coord other) const
        {
            return (this->fileIndex == other.fileIndex && this->rankIndex == other.rankIndex) ? 0 : 1;
        }

        std::ostream &operator<<(std::ostream &os, Coord coord)
        {
            os << coord.fileIndex << " " << coord.rankIndex;
        }

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
