function reversePrefix(word: string, ch: string) : string {
    var index = word.indexOf(ch);
    console.log(index);
    if(index == -1){
        console.log(index);
    }
    return "";
}

reversePrefix("abcdef",'o');


function reverse(aim: string) :string {
    let ans : string = "";
    for(let i=0;i<aim.length;i++){
        ans += aim[aim.length-i-1]
    }
    return ans;
};

console.log(reverse("abcde"))