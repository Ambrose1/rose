#include<iostream>
#include<vector>
using namespace std;

class Solution {

public:
    int countOnes(int x) {
        int ones = 0;
        while(x > 0){
            x &= (x-1);
            ones++;
        }
        return ones;
    }

    vector<int> countBits(int n){
        vector<int> ans(n+1);
        for(int i=0; i< n+1;i++){
            ans.push_back(countOnes(i));
        }
        return ans;
    }

    // 最高有效位 的概念，当前数字有1 的数量等于上一个最高有效位的值加上 dp[当前数值 - 最高有效位] + 1
    // 状态转移
    vector<int> countBits(int n) {
        if(n==0)return vector<int>(1,0);
        vector<int> dp(n+1);
        dp[0] = 0;
        dp[1] = 1;
        int heightBit = 1;
        for(int i=2; i<=n; i++){
            if((i &(i-1)) == 0){
                heightBit = i;
                dp[i] = 1;
                continue;
            }
            dp[i] = dp[i - heightBit] + 1;
        }
        return dp;
        
    }
};