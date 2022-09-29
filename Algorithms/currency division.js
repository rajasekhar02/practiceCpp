let total = 1000;
let k = 100;
let constant = 1e9+7;
let dp = new Array(total+1).fill(0).map(x=> new Array(k+1).fill(-1));

let numberOfWays = function(currtotal,k,currSelectedCurrency){
    if(currtotal == total){
        return 1;
    }
    if(dp[currtotal][currSelectedCurrency]!=-1){
        return dp[currtotal][currSelectedCurrency];
    }
    let sum = 0;
    for(let i=1;i<=k;i++){
        if(currtotal+i > total || i < currSelectedCurrency) continue;
        sum = sum + numberOfWays(currtotal+i,k,i);
    }
    dp[currtotal][currSelectedCurrency] = sum % constant;
    return dp[currtotal][currSelectedCurrency];
}

numberOfWays(0,k,1)
