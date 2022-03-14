#include <iostream>
#include "chess_board.h"
int main() {
    string fenString = "5r1k/6pp/4Qpb1/p7/8/6PP/P4PK1/3q4 b - - 4 37";
    ChessBoard chess_board(fenString);
    cout << chess_board;
    return 0;
}