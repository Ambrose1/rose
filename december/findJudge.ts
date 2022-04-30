/*
 * @Author: your name
 * @Date: 2021-12-19 22:12:45
 * @LastEditTime: 2021-12-20 09:58:11
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /myweekend/leetcode刷题笔记/december/findJudge.ts
 */

function findJudge(n : number,trust : number[][]) : number {
    let outDegree : number[] = []; //出度
    let inDegree : number[] = []; //入度
    let res = -1;
    for (let index = 0; index < n; index++) {
        outDegree.push(0);
        inDegree.push(0);
    }
    
    trust.forEach(element => {
        outDegree[element[0]-1] += 1;
        inDegree[element[1]-1] += 1
    });

    for (let index = 0; index < n; index++) {
        if ( outDegree[index] == 0 && inDegree[index] == n-1){
            if(res == -1){
                res = index+1;
            }else {
                return -1;
            }
        }
    }
    return res;

}

(()=>{
    let res = findJudge(2,[[1,2]]);
    console.log(res);
})();
export {};