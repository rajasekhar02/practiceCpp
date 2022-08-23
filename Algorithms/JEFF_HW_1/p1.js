let set = new Set()

function Baguenaudier_puzzle(num){
    if(num === 0) return [0];
    
    // Task-1
    let binaryNum = Array.from(Number(num).toString(2))
    let numberAfterFlippingRightBit = num ^ 1;
    let value = [];
    if(!set.has(numberAfterFlippingRightBit)){
        set.add(numberAfterFlippingRightBit);
       value = Baguenaudier_puzzle(numberAfterFlippingRightBit);
    }
    if(value.length>0){
        value.push(num)
        return value;
    }
    //Task-2
    let i = 0;
    let mask = 1;
    for(i=binaryNum.length-1; i>0; i--){
         mask = mask<<1;
        if(+binaryNum[i] === 1){
            // mask = mask<<1;
            break;
        }
      
    }
    numberAfterFlippingRightBit = num ^ mask;
    if(!set.has(numberAfterFlippingRightBit)){
        set.add(numberAfterFlippingRightBit);
        value = Baguenaudier_puzzle(numberAfterFlippingRightBit);
    }
    if(value.length>0){
        value.push(num)
        return value;
    }
    return [];
}

let number  = 31;
set.add(number);
let arr = Baguenaudier_puzzle(number)
    arr.map((x,index)=> {
   return index === 0 ? 0: Math.log2(Math.abs(arr[index-1]-x))+1;
}).reverse();
