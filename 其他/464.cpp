#include<iostream>
#include<unordered_map>
using namespace std;

class Solution {
public:
    unordered_map<int,bool> demo;
    bool dfs(int maxChoosableInteger, int curSelect, int desiredTotal, int curTotal){
        if(!demo.count(curSelect)){
            bool res = false;
            for(int i=0; i< maxChoosableInteger; i++){
                if(((curSelect >> i)&1) == 0){
                    // 未使用过
                    if(curTotal+i+1 >= desiredTotal){
                        res = true;
                        break;
                    }
                    if(!dfs(maxChoosableInteger, curSelect | (1 << i), desiredTotal, curTotal+i+1)){
                        res = true;
                        break;
                    }
                }
            }
            demo[curSelect] = res;
        }
        return demo[curSelect];
    }


    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        if((maxChoosableInteger+1)*maxChoosableInteger /2 < desiredTotal)return false;
        return dfs(maxChoosableInteger, 0, desiredTotal, 0);
    }
};