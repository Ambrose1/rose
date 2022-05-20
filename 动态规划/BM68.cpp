#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    /**
     * 
     * @param matrix int整型vector<vector<>> the matrix
     * @return int整型
     */
    int minPathSum(vector<vector<int> >& matrix) {
        // write code here
        
        int m = matrix.size();
        int n = matrix.at(0).size();
        if(m*n == 0)return 0;
        
        vector<vector<int>> dp(m+1,vector<int>(n+1,INT_MAX));
        
        for(int i=1; i<=m; i++){
            for(int j=1; j<=n; j++){
                dp[i][j] = min(dp[i-1][j],dp[i][j-1]) + matrix[i-1][j-1]; 
                if(i==1 && j==1)dp[i][j] = matrix[0][0];
            }
        }
        return dp[m][n];
    }
};