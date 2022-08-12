let avail_demonations = [1,4,7,13,28,52,91,365]
    //.sort((a,b)=>b-a);

let get_bills = function(total_value){
    if(total_value == 0) return 0;
    let min_value = total_value;
    for(let i=0;i<avail_demonations.length;i++){
        let no_of_bills_ith_denomination = Math.floor(total_value/avail_demonations[i]);
        if(no_of_bills_ith_denomination >= 1){
            let output = no_of_bills_ith_denomination + get_bills(total_value%avail_demonations[i]);
            min_value = Math.min(output,min_value);
        }
    }
    return min_value;
}

let get_bills_2 = function(total_value){
    if(total_value == 0) return 0;
    let min_value = total_value;
    for(let i=0;i<avail_demonations.length;i++){
        let remain_value = total_value-avail_demonations[i];
        if(remain_value >= 0){
            let output = 1 + get_bills(remain_value);
            min_value = Math.min(output,min_value);
        }
    }
    return min_value;
}

let get_bills_3 = function(total_value){
    let temp_total_value = total_value;

    // parameter used for iterating in the recurrence
    for(let i=2;i<total_value+1;i++){
       // inside loop in the recurrence
        for(let den=0;den<avail_demonations.length;den++){
            // base condition
            if((i-avail_demonations[den]) <= 0) continue;

            // recurrence relation
            dp[i] = Math.min(dp[i-avail_demonations[den]]+1,dp[i]);
        }
    }
    return dp[total_value];
}

let get_bills_greedy = function(total_value){
    let value = total_value;
    let count_bills = 0;
    avail_demonations = avail_demonations.sort((a,b)=>b-a);
    for(let i=0;i<avail_demonations.length;i++){
        let no_of_bills_ith_denomination = Math.floor(value/avail_demonations[i]);
        if(no_of_bills_ith_denomination >= 1){
           count_bills +=no_of_bills_ith_denomination;
           value = value%avail_demonations[i]
        }
    }
    // console.log(value);
    return count_bills;
}


let dp = new Array(100000).fill(1e9);
dp[0] = 0;
for(let i=0;i<avail_demonations.length;i++){
        dp[avail_demonations[i]] = 1;
}
for(let i = 1000;i>=100;i--){
    let back_track = get_bills_2(i);
    // let greedy = get_bills_2(i);
       
    let dp_iter = dp[i]<1e9 ? dp[i]:get_bills_3(i);
    if(dp_iter != back_track){
            console.log(i,back_track,dp_iter);
     // break;
     }
}
