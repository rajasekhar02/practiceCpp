#include<bits/stdc++.h>
using namespace std;
struct Point {
    int x,y;
};

int main(){
    int field[1001][1001];
    int opponents;
    cin>>opponents;
    vector<pair<Point, Point>> opponentRanges(opponents);
    int opponentPosX, opponentPosY, opponentRange;
    for(int i=0;i<opponents;i++){
        cin>>opponentPosX>>opponentPosY>>opponentRange;
        opponentRanges.push_back(make_pair(opponentPosX-opponentRange, opponentPosY+));
    }
    
    // for(int i=0;i<){

    // }
    // for(int i=0;i<1001;i++){
    //     field = 
    // }
    return 0;
}