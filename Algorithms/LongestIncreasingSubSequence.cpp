#include<bits/stdc++.h>
using namespace std;
 vector<int> nums;
 vector<vector<int>> bestLen;
 int solveLISBug(int position, int prev_big_num_idx){
    
    if(position >= nums.size()){
        // this last index value is zero because the counting is starting from the last position
        return 0;
    }

    if(nums[position] > nums[prev_big_num_idx]){
        return  1 + solveLISBug(position+1, prev_big_num_idx);
    }
    
    int len_if_this_position_neglected = solveLISBug(position+1, prev_big_num_idx);
    
    int len_if_seq_start_from_this_position = solveLISBug(position+1, position);
        
    return  max(len_if_this_position_neglected, len_if_seq_start_from_this_position);
    
}

int solveLISBug1(int position, int prev_big_num_idx, int length){
        
    if(position >= nums.size()){
        // this last index value is zero because the counting is starting from the last position
        return length;
    }

    if(nums[position] > nums[prev_big_num_idx]){
        return  solveLISBug1(position+1, prev_big_num_idx, length+1);
    }
    
    int len_if_this_position_neglected = solveLISBug1(position+1, prev_big_num_idx, length);
    
    int len_if_seq_start_from_this_position = solveLISBug1(position+1, position, 0);
        cout<<len_if_this_position_neglected<<" "<<len_if_seq_start_from_this_position<<endl;

    return  max(len_if_this_position_neglected, len_if_seq_start_from_this_position);
}

int solveLISRec(int position, int prev_big_num_idx, int length){
        
    if(position >= nums.size()){
        // this last index value is zero because the counting is starting from the last position
        return length;
    }
    // cout<<"p_n: "<<nums[prev_big_num_idx]<<" c_n:"<<nums[position]<<" len: "<<length<<endl;
    if(nums[prev_big_num_idx] >= nums[position]){
        return  solveLISRec(position+1, prev_big_num_idx, length);
    }
    
    int len_if_this_position_neglected = solveLISRec(position+1, prev_big_num_idx, length);
    
    int len_if_seq_includes_this_position = solveLISRec(position+1, position, length+1);
        
    return  max(len_if_this_position_neglected, len_if_seq_includes_this_position);
}

int solveLISDP(int position, int prev_big_num_idx){
    if(position >= nums.size()){
        // this last index value is zero because the counting is starting from the last position
        return 0;
    }
    // cout<<"p_n: "<<nums[prev_big_num_idx]<<" c_n:"<<nums[position]<<" len: "<<length<<endl;
    if(bestLen[position][prev_big_num_idx]!=-1){
        return bestLen[position][prev_big_num_idx];
    }
    if(nums[prev_big_num_idx] >= nums[position]){ 
        return solveLISDP(position+1, prev_big_num_idx);
    }
    
    int len_if_this_position_neglected = solveLISDP(position+1, prev_big_num_idx);
    
    int len_if_seq_includes_this_position = 1+solveLISDP(position+1, position);
    
    bestLen[position][prev_big_num_idx] = max(len_if_this_position_neglected,len_if_seq_includes_this_position);
    
    return bestLen[position][prev_big_num_idx];
}

int solveLISDP2(int position, int prev_big_num_idx,int length){
    if(position >= nums.size()){
        // this last index value is zero because the counting is starting from the last position
        return 0;
    }
    // cout<<"p_n: "<<nums[prev_big_num_idx]<<" c_n:"<<nums[position]<<" len: "<<length<<endl;
    if(bestLen[position][prev_big_num_idx]!=-1){
        return length+bestLen[position][prev_big_num_idx];
    }
    if(nums[prev_big_num_idx] >= nums[position]){ 
        return solveLISDP(position+1, prev_big_num_idx);
    }
    
    int len_if_this_position_neglected = solveLISDP(position+1, prev_big_num_idx);
    
    int len_if_seq_includes_this_position = solveLISDP(position+1, position,length+1);
    
    bestLen[position][prev_big_num_idx] = max(len_if_this_position_neglected,len_if_seq_includes_this_position);
    
    return bestLen[position][prev_big_num_idx];
}

int main(){
// 3
// 4
// 1
// 4
// 3
    vector<vector<int>> testcases = {
        vector<int>{4,10,4,3,8,9},
        vector<int>{10 ,9,2,5,3,7,101,18},
        vector<int>{7,7,7,7,7,7,7},
        vector<int>{0,1,0,3,2,3},
        vector<int>{10,9,2,5,3,4}
    };
   for(int i=0;i<testcases.size();i++){
        nums = vector<int>(testcases[i].size()+1, -1e9);
        for(int j=0;j<testcases[i].size();j++){
            nums[j+1] = testcases[i][j];
            // cout<<nums[j+1]<<endl;
        } 
        bestLen = vector< vector<int> >(nums.size(),vector<int>(nums.size(),-1));
        int value = solveLISDP2(1,0,0);
        cout<<"answer: "<<value<<endl;
        // cout<<"next testcase"<<endl;
    }
    return 0;
}