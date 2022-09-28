// Algorithm for Palindrome Substrings of length>=k

let str = "aababaabce" //"aababaabce"  //"aaaaaaaaaa"//"abcdcba" //"aaaaabba" //"aaabaaabaaa"
let dp = new Array(str.length).fill(1).map(_=>new Array(str.length+1).fill(-1));
let isPalindrome = function(position,length){
    if(length == 0 || length == 1){
        return true;
    }
    if(dp[position][length] != -1){
        return dp
    }
    // iterate over possible lengths
    return str[position] === str[position+length-1] && isPalindrome(position+1, length-2)
}

for(let everyIndex=0;everyIndex<str.length;everyIndex++){
     dp[everyIndex][1] = +true;
     dp[everyIndex][0] = +true;
}

for(let everyLength=2;everyLength<str.length+1;everyLength++){
    for(let everyIndex=0;everyIndex<str.length;everyIndex++){
        dp[everyIndex][everyLength] = +(str[everyIndex] === str[everyIndex+everyLength-1] && dp[everyIndex+1][everyLength-2])
    }
}


let k = 4;
let dpMaxPalins = new Array(str.length).fill(-1)
let noOfNonOverlappingPalins = function(position){
    if(position==str.length-k){
        return dp[position][k];
    }
    if(dpMaxPalins[position] != -1){
        return dpMaxPalins[position];
    }
    let maxValue = 0;
    for(let everyIndex1=position; everyIndex1<str.length; everyIndex1++){
         for(let everyLength=k; (everyIndex1+everyLength)<(str.length+1); everyLength++){
            let value = dp[everyIndex1][everyLength] + noOfNonOverlappingPalins(everyIndex1+everyLength);
            if(value>maxValue){
                maxValue=value;
            }
        }
    }
    dpMaxPalins[position] = maxValue;
    return dpMaxPalins[position];
}
// console.log(dp)
console.log(noOfNonOverlappingPalins(0))
