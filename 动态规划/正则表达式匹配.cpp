#include<iostream>
#include<vector>
#include<string>
using namespace std;

// 反复练习
class Solution {
public:
    bool isMatch(string s, string p) {
        int np = p.length();
        int ns = s.length();
        auto match = [&](int x, int y){
            if(x == 0)return false;
            if(p[y-1] == '.')return true;
            return s[x-1] == p[y-1];
        };

        vector<vector<bool>> dp(ns+1, vector<bool>(np+1,false));
        dp[0][0] = true;
        for(int i=0; i<=ns; i++){
            for(int j=1; j<=np; j++){
                if(p[j-1] == '*'){
                    dp[i][j] = dp[i][j] ||dp[i][j-2];
                    if(match(i,j-1)){
                        dp[i][j] = dp[i][j] || dp[i-1][j];
                    }
                }else {
                    if(match(i,j)){
                        dp[i][j] =dp[i][j] || dp[i-1][j-1];
                    }
                }
            }
        }
        return dp[ns][np];
    }
};