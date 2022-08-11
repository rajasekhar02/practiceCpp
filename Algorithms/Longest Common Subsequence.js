let nums =[-1,10,9,2,5,3,7,101,18]
bestLen = new Array(nums.length).fill(0).map(x=>new Array(nums.length).fill(0))

// Implementation 1
for(let i=1;i<nums.length;i++){
    bestLen[i][0] = 1;
}

for(let i=1;i<nums.length;i++){
      for(let j=i+1;j<nums.length;j++){  
            if(nums[i]>=nums[j]) {
                bestLen[j][i] = bestLen[j][i-1];
                continue;
            }
            bestLen[j][i] = Math.max(bestLen[i][i-1]+1, bestLen[j][i-1]);
        }
    }
let max = 0;
// this is needed because of the diagonal elements contains the required max length
for(let i =1;i<nums.length;i++){
    if(max<bestLen[i][i-1]){
        max = bestLen[i][i-1];
    }
}
console.log(max,bestLen[nums.length-1][nums.length-2])

// Implementation 2
// below is the implementation of Jeff Erickson Algorithms Textbook
for(let i=0;i<nums.length;i++){
    bestLen[i][nums.length] = 0
}

for(let j= nums.length-1;j>0;j--){
    for(let i=0;i<j;i++){
        let keep = 1+bestLen[j][j+1];
        let skip = bestLen[i][j+1];

        if(nums[i]>=nums[j]){
            bestLen[i][j] = skip;
        }else{
            bestLen[i][j] = Math.max(keep,skip);
        }
    }
}

console.log(bestLen[0][1]);
