#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    int cnt = 0;
    cnt = t;
    cin.ignore();
    while(t--){
        string output[2]= {"Nothing.","Spell!"};
        bool isSpell = false;
        string str;
        cin>>str;
        cout<<str;
        //count syllables at each position
        //take position where syllable are greater than two as the initial break
        //apply common substring
        cout<<"Case #"<<(cnt-t)<<": "<<output[isSpell]<<endl;
    }
    return 0;
}