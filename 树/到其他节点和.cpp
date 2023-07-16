#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        vector<vector<int>> tree(n);
        vector<int> ans(n);

        // make tree
        for (auto &a : edges) {
            int x = a[0], y = a[1];
            tree[x].push_back(y);
            tree[y].push_back(x);
        }

        vector<int> sz(n, 1);
        function<void(int,int,int)> dfs = [&](int x, int father, int depth) {
            ans[0] += depth;
            for (int j : tree[x]) {
                if (j != father) {
                    dfs(j,x,depth+1);
                    sz[x] += sz[j];
                }
            }
        };
        dfs(0,-1,0);

        function<void(int, int)> root = [&](int x, int fa) {
            for (int y : tree[x]) {
                if (y!= fa) {
                    ans[y] = ans[x] + n - 2* sz[y];
                    root(y, x);
                }
            }
        };
        root(0,-1);
        return ans;

    }
};