let Word1 = "FOOD";
let Word2 = "MONEY";

let bestDis = new Array(Word1.length).fill(0).map(
    x=>{
        return new Array(Word2.length).fill(0).map(
            y=>{
                return 0;   
            }
        ) 
    }
)

for(let i=1;i<Word1.length;i++){
    bestDis[i][0] = i;
   
}

for(let i=1;i<Word2.length;i++){
    bestDis[0][i] = i;  
}
for(let i=1;i<Word1.length;i++){
    for(let j=1;j<Word2.length;j++){
        bestDis[i][j] = Math.min(bestDis[i-1][j]+1, bestDis[i][j-1]+1,bestDis[i-1][j-1]+(Word1[i] !== Word2[j]))
    }
}

console.log(bestDis)
