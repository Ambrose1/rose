#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    /**
     * 最少货币数
     * @param arr int整型vector the array
     * @param aim int整型 the target
     * @return int整型
     */
    int minMoney(vector<int>& arr, int aim) {
        // write code here
        if(aim == 0)return 0;
        vector<int> dp(aim+1,-1);
        for(int i=0; i< arr.size(); i++){
            if(arr[i] > aim){
                continue;
            }
            dp[arr[i]] = 1;
        }
        
        for(int i=0; i<=aim; i++){
            if(dp[i] != -1){
                for(int j : arr){
                    if(i+j > aim)continue;
                    if(dp[i+j] > 0){
                        dp[i+j] = min(dp[i+j],dp[i]+1);
                        continue;
                    }
                    dp[i+j] = dp[i]+1;
                }
            }
        }
        return dp[aim];
        
        
    }
};