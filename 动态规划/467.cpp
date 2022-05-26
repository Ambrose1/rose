#include<iostream>
#include<vector>
#include<numeric>
using namespace std;

class Solution {
public:
    int findSubstringInWraproundString(string p) {
        if(p.size() == 0)return 0;
        int n = p.size();
        vector<int> dp(26);
        int k=0;
        for(int i=0; i<n; i++){
           if(i && (p[i] - p[i-1]+ 26)%26 == 1){
               ++k;
           }else {
               k = 1;
           }
           dp[p[i]-'a'] = max(dp[p[i]-'a'],k);
        }
        return accumulate(dp.begin(),dp.end(),0);
    }
};