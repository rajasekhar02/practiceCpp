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


for(let i = 100;i<10000;i++){
    let back_track = get_bills(i);
    let greedy = get_bills_greedy(i);

    if(back_track != greedy){
            console.log(i,greedy,back_track);
     // break;
     }
}
