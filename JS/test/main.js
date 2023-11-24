let arr = [5,7,82,34,6,24,2];
let max = arr[0];
let str = "hello";

function reverse(str){
    let a="";
    for(let i=str.length-1;i>=0;i--){
        a+=str[i];
    }

    console.log(a);

}

for (let i=1;i<arr.length;i++){
    if(max<arr[i])max=arr[i];
}

reverse(str);
console.log(max);