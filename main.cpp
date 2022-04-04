#include <iostream>
#include <bitset>
#include "chess_board.h"
#include "board_representation.h"
int main()
{
    string fenString = "8/1n3n2/4n3/3n1n2/2n1n3/8/8/8 w - - 0 1";
    ChessBoard chess_board(fenString);
    cout << chess_board << endl;
    chess_board.drawArray();

    // for (int i = 0; i < 64; i++)
    // {
    //     cout << i << ' ' << chess_board.grid[Chess::BoardRepresentation::getFileIndex(i)][Chess::BoardRepresentation::getRankIndex(i)] << endl;
    // }

    Chess::BoardRepresentation::PieceList knights[2] = {Chess::BoardRepresentation::PieceList(10),
                                                        Chess::BoardRepresentation::PieceList(10)};
    bitset<64> x(chess_board.BN);

    for (int i = 0; i < 64; i++)
    {
        if (i % 8 == 7)
        {
            cout << chess_board.grid[(i / 8)][(i % 8)] << " " << Chess::BoardRepresentation::getSquareNameFromIndex(i) << endl;
        }
        else
        {
            cout << chess_board.grid[(i / 8)][i % 8] << " " << Chess::BoardRepresentation::getSquareNameFromIndex(i);
        }
        if (chess_board.grid[(i / 8)][i % 8] == 'n')
        {
            knights[0].addPieceAtSquare(i);
        }
    }

    for (int i = 0; i < 64; i++)
    {
        if (i % 8 == 7)
        {
            cout << x[i] << endl;
        }
        else
        {
            cout << x[i];
        }
    }
    return 0;
}