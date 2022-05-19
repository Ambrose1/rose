#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param cost int整型vector 
     * @return int整型
     */
    int minCostClimbingStairs(vector<int>& cost) {
        // write code here
        int n= cost.size();
        if(n == 1){
            return cost[0];
        }
        if(n == 2)return cost[0] < cost[1] ? cost[0] : cost[1];
//         vector<int> dp(n+1);
//         dp[0] = 0;
//         dp[1] = 0;
        
        int a=0, b=0,c=0;
        for(int i=2; i<=n;i++){
            c = min(a+cost[i-2],b+cost[i-1]);
            a = b;
            b = c;
//             dp[i] = min(dp[i-1]+cost[i-1],dp[i-2]+cost[i-2]);
        }
        return c;
        
    }
};