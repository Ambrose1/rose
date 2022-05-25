#include<iostream>
#include<vector>
using namespace std;

// 并查集问题

class Solution {
public:
    void solve(vector<vector<char>>& board) {
         int m=board.size(),n = board.at(0).size();
        for(int i=0; i<m; i++){
            dfs(board,i,0);
            dfs(board, i, n-1);
        }

        for(int j=0; j<n; j++){
            dfs(board, 0, j);
            dfs(board, m-1,j);
        }

        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                if(board[i][j] == 'A'){
                    board[i][j] = 'O';
                }else if(board[i][j] == 'O'){
                    board[i][j] = 'X';
                }
            }
        }
    }

    void dfs(vector<vector<char>>& board,int x, int y){
        if(!isArea(board,x,y))return ;
        if(board[x][y] != 'O'){
            return ;
        }
        board[x][y] = 'A';
        dfs(board,x+1,y);
        dfs(board,x-1,y);
        dfs(board,x,y+1);
        dfs(board,x,y-1);
    }

    bool isArea(vector<vector<char>>& board, int x, int y){
        return x >=0 && y>=0 && x < board.size() && y < board.at(0).size();
    }
};