
let s=[
    [4,9,2],
    [3,5,7],
    [8,1,5]
];

main();


function formingMagicSquare(s) {
    // Write your code here

    return s.forEach(element =>{
        console.log(element.reduce((prev,cur)=>prev+cur));
    });
}

function main() {
    console.log(formingMagicSquare(s));
}
