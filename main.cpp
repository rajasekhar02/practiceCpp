#include <iostream>
#include "chess_board.h"
int main() {
    string fenString = "rnbqkbnr/pppp3p/5p2/4p1p1/4P3/5PPB/PPPPN2P/RNBQKR2 w Qkq - 0 1";
    ChessBoard chess_board(fenString);
    cout << chess_board;
    return 0;
}