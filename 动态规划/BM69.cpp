#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    /**
     * 解码
     * @param nums string字符串 数字串
     * @return int整型
     */
    int solve(string nums) {
        // write code here
        if(nums.length() == 0)return 0;
        if(nums[0] == '0')return 0;
        if(nums == "10" || nums == "20")return 0;
        int n = nums.length();
        for(int i=1; i < n; i++){
            if(nums[i] == '0'){
                if(nums[i-1] != '1' && nums[i-1] != '2')return 0;
            }
        }
        vector<int> dp(n+1,1);
        for(int i=2; i<=n; i++){
            if((nums[i-2] == '1' && nums[i-1] != '0') || (nums[i-2] == '2' && nums[i-1]>'0' && nums[i-1]<'7')){
                dp[i] = dp[i-1]+dp[i-2];
                continue;
            }
            dp[i] = dp[i-1];
            
        }
        return dp[n];
    }
};