/*
A string is said to be a special string if either of two conditions is met:

All of the characters are the same, e.g. aaa.
All characters except the middle one are the same, e.g. aadaa.
A special substring is any substring of a string which meets one of those criteria. Given a string, determine how many special substrings can be formed from it.

*/


function substrCount(n, s) {
   const chFreq = Array.from(s).reduce((acc,curr)=>{
       if(acc.length === 0 || acc[acc.length-1][0] != curr){
           acc.push([curr, 0]);
       } 
       acc[acc.length-1][1]++
       return acc;
   },[]);
   let count = 0;
   if(chFreq.length>3){
       let curr = chFreq[0];
       let next = chFreq[1];
       count = (curr[1]*(curr[1]+1))/2;
       for(let i = 1;i<chFreq.length-1;i++){
           let prev = curr;
           curr = next;
           next = chFreq[i+1] 
           count += (curr[1]*(curr[1]+1))/2;
           if(prev[0] === next[0] && curr[1] === 1){
               count+= Math.min(prev[1],next[1]);
           }
       }
       count+= (next[1]*(next[1]+1))/2;
   }else{
       count = chFreq.reduce((acc,curr)=>{
           return acc+(curr[1]*(curr[1]+1)/2)
       },0)
   }
   return count;
}
