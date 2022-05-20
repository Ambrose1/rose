#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    /**
     * longest common subsequence
     * @param s1 string字符串 the string
     * @param s2 string字符串 the string
     * @return string字符串
     */
    string LCS(string s1, string s2) {
        // write code here
        int x = s1.length(), y = s2.length();
        if(x*y == 0)return "-1";
        
        vector<vector<int>> dp(x+1,vector<int>(y+1,0));
        vector<vector<int>> b(x+1,vector<int>(y+1,0));
        
        for(int i=1; i<=x; i++){
            for(int j=1; j<=y; j++){
                if(s1[i-1] == s2[j-1]){
                    dp[i][j] = 1+dp[i-1][j-1];
                    b[i][j] = 1;
                    continue;
                }
                if(dp[i-1][j] > dp[i][j-1]){
                    dp[i][j] = dp[i-1][j];
                    b[i][j] = 2;
                }else {
                    dp[i][j] = dp[i][j-1];
                    b[i][j] = 3;
                }
            }
        }
        
        string res = ans(x, y, b, s1);
        return res != "" ? res : "-1";
    }
    
    string ans(int i, int j, vector<vector<int>> &b, string s1) {
        string res = "";
        if(i == 0 || j == 0)return res;
        if(b[i][j] == 1){
            res+= ans(i-1,j-1,b,s1);
            res += s1[i-1];
        }else if(b[i][j] == 2) {
            res += ans(i-1, j, b, s1);
        }else if(b[i][j] == 3){
            res += ans(i, j-1, b, s1);
        }
        return res;
    }
};