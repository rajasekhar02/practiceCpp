#ifndef BOARD_REPRESENTATION_H
#define BOARD_REPRESENTATION_H
#include <string>
#include <iostream>
#include <map>
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
        const int none = 0;

        const int king = 1;

        const int pawn = 2;

        const int knight = 3;

        const int bishop = 5;

        const int rook = 6;

        const int queen = 7;

        const int white = 8;

        const int black = 16;

        const int typeMask = 0b00111;

        const int blackMask = 0b10000;

        const int whiteMask = 0b01000;

        const int colourMask = whiteMask | blackMask;

        const std::map<char, int> pieceSymbolToPieceType = {
            {'p', pawn},
            {'r', rook},
            {'n', knight},
            {'b', bishop},
            {'q', queen},
            {'k', king},
            {'.', none}};
        const std::map<int, char> pieceTypeToPieceSymbol = {
            {pawn, 'p'},
            {rook, 'r'},
            {knight, 'n'},
            {bishop, 'b'},
            {queen, 'q'},
            {king, 'k'},
            {none, '.'}};

        bool IsGivenColour(int piece, int colour);

        int getPieceColour(int piece);

        int getPieceType(int piece);

        bool isRookOrQueen(int pieceType);

        bool isBishopOrQueen(int pieceType);

        bool isSlidingPiece(int pieceType);

    }
    namespace BoardRepresentation
    {
        struct PieceList
        {
            int *occupiedSquares;
            int *map;
            int numPieces;

            PieceList(int maxPieceCount = 16);

            void addPieceAtSquare(int square);

            void removePieceAtSquare(int square);

            void movePiece(int startSquare, int targetSquare);

            const int operator[](int index) const;
        };
        struct Coord
        {
            int fileIndex;
            int rankIndex;
            Coord(int fileIndex, int rankIndex);

            bool isWhiteSquare();

            const bool operator==(Coord other) const;
        };
        std::ostream &operator<<(std::ostream &os, Coord coord);

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

        int getRankIndex(int squareIndex);

        int getFileIndex(int squareIndex);

        int IndexFromCoord(int fileIndex, int rankIndex);

        int IndexFromCoord(Coord coord);

        Coord getCoordFromIndex(int squareIndex);

        bool getLightSquare(int fileIndex, int rankIndex);

        std::string getSquareNameFromCoordinate(int fileIndex, int rankIndex);

        std::string getSquareNameFromIndex(int squareIndex);

        std::string getSquareNameFromCoordinate(Coord coord);

    }
}
#endif