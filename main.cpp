#include <iostream>
#include "chess_board.h"
#include "board_representation.h"
int main()
{
    string fenString = "rnbqkbnr/pppp3p/5p2/4p1p1/4P3/5PPB/PPPPN2P/RNBQKR2 w Qkq - 0 1";
    ChessBoard chess_board(fenString);
    cout << chess_board << endl;
    chess_board.drawArray();

    for (int i = 0; i < 64; i++)
    {
        cout << i << ' ' << Chess::BoardRepresentation::getCoordFromIndex(i) << ' ' << Chess::BoardRepresentation::getFileIndex(i) << " " << Chess::BoardRepresentation::getRankIndex(i) << endl;
    }
    return 0;
}