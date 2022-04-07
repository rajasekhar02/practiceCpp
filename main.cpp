#include <iostream>
#include "chess_board.h"
using namespace std;
int main()
{
    std::string fenString = "rnbqkbnr/ppp1p1pp/8/3pPp2/8/8/PPPP1PPP/RNBQKBNR w KQkq f6 0 3";
    // if (!Chess::GamePosition::validateFenString(fenString))
    // {
    //     std::cout << "INVALID FEN STRING" << std::endl;
    //     return 0;
    // }
    Chess::GamePosition::precomputeMoveData();
    Chess::GamePosition chess_board(fenString);

    std::cout << chess_board;
    for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << Chess::GamePosition::numSquaresToDirections[i][j] << endl;
        }
    }
    return 0;
}