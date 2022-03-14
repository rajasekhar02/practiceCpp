//
// Created by rp6kp on 3/14/2022.
//

#include <iostream>
#include<vector>
#include<string>
#include<cstring>
#include"utils.h"

#ifndef CHESS_CHESS_BOARD_H
#define CHESS_CHESS_BOARD_H

using namespace std;
class ChessBoard {
public:
    string grid[8];
    string turn;
    bool is_black_castling;
    bool is_white_castling;
    int half_moves;
    long long int moves;

    ChessBoard(){
        initGrid();
        is_black_castling = false;
        is_white_castling = false;
        turn = "WHITE";
    }

    ChessBoard(string fenString){
        initGrid();
        parseFenString(fenString);
    }

    void parseFenString(string fenString){
        vector<string> fenComponents =  utils::split(fenString);
        initGridWithFenBoardString(fenComponents[0]);
    }

    void initGridWithFenBoardString(string fenBoardString){
        vector<string> board = utils::split(fenBoardString, '/');
        for(int eachRow=0;eachRow<8;eachRow++) {
            string chessBoardRow = grid[eachRow];
            int prevPosition = 0;
            string cells = board[eachRow];
            for (int eachCol = 0; eachCol < cells.size(); eachCol++) {
                if (isalpha(cells[eachCol])) {
                    chessBoardRow[prevPosition] = cells[eachCol];
                    prevPosition++;
                    continue;
                }
                prevPosition += utils::charToInt(cells[eachCol]);
            }
            grid[eachRow] = chessBoardRow;
        }
    }

    void initGrid(){
        for(int eachRow=0;eachRow<8;eachRow++){
            string str = "";
            for(int eachCol=0;eachCol<8;eachCol++){
                str += '.';
            }
            grid[eachRow] = str;
        }
    }

    ostream& printGrid(ostream& os){
        for(int eachRow=0;eachRow<8;eachRow++){
           os<<grid[eachRow]<<endl;
        }
        return os;
    }

    void printHorizontalBorder(int lengthOfHorizontalBorder){
        for(int i=0;i<lengthOfHorizontalBorder;i++){
            cout<<"-";
        }
    }
};

ostream& operator<<(ostream& os, ChessBoard chessBoard){
    os << "from the operator overloading" << endl;
    if(chessBoard.turn == "WHITE") {
        os << "Whites to play" << '\n';
    } else{
        os << "Blacks to play" << '\n';
    }
    chessBoard.printGrid(os);
    return os;
}


#endif //CHESS_CHESS_BOARD_H
