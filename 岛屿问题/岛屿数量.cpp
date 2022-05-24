#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int ans = 0;
        for(int i=0; i<grid.size(); i++){
            for(int j=0; j<grid[0].size();j++){
                if(grid[i][j] == '1'){
                    if(dfs(grid,i,j) > 0){
                        ans++;
                    }
                }
            }
        }
        return ans;
    }

    int dfs(vector<vector<char>>& grid, int x, int y){
        if(!isArea(grid, x, y))return 0;
        if(grid[x][y] != '1')return 0;
        grid[x][y] = '2';

        return 1+dfs(grid, x+1,y) +dfs(grid,x,y+1)+dfs(grid,x,y-1)+dfs(grid,x-1,y);
    }

    bool isArea(vector<vector<char>>& grid, int x, int y){
        return x < grid.size() && y < grid[0].size() && x >= 0 && y >=0;
    }
};