//
// Created by rp6kp on 3/14/2022.
//

#include<string>
#include<vector>

using namespace std;
#ifndef CHESS_UTILS_H
#define CHESS_UTILS_H
namespace utils {
    vector<string> split(string s, char c = ' ');
    int charToInt(char ch);

    vector<string> split(string s, char c) {
        vector<string> res;
        string tempStr = "";
        for (int index = 0; index < s.length(); index++) {
            if (s[index] != c) {
                tempStr += s[index];
            } else {
                res.push_back(tempStr);
                tempStr = "";
            }
        }
        res.push_back(tempStr);
        return res;
    }

    int charToInt(char ch){
        return ch - '0';
    }
}
#endif //CHESS_UTILS_H
