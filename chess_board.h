//
// Created by rp6kp on 3/14/2022.
//

#include <iostream>
#include<vector>
#include<string>

#ifndef CHESS_CHESS_BOARD_H
#define CHESS_CHESS_BOARD_H

using namespace std;
class ChessBoard {
public:
    vector<vector<char>> grid;
    string turn;
    bool is_black_castling;
    bool is_white_castling;
    int half_moves;
    long long int moves;

    ChessBoard(int pass){
        grid.resize(8,vector<char>(8,'*'));
        is_black_castling = false;
        is_white_castling = false;
        turn = "WHITE";
        cout<<"constructor"<<pass<<endl;
    }



    void printGrid(ostream& os){
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                os<<this->grid[i][j]<<endl;
            }
        }
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
    return os;
}


#endif //CHESS_CHESS_BOARD_H
