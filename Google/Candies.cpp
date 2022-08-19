#include <bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    int cnt = t;
    while(t--){
        int output;
        int input;
        int total = 0;
        int childs,N;
        cin>>N>>childs;
        for(int i=0;i<N;i++){
            cin>>input;
            total += input;
        }
        output = total%childs;
        cout<<"Case #"<<(cnt-t)<<": "<<output<<endl;
    }
    return 0;
}