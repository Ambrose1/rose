#include<iostream>
#include<vector>
using namespace std;

// 全排列2

class Solution {
private:
    vector<int> visit;
public:
    void backtrack(vector<int>& nums, vector<vector<int>>& ans, int idx, vector<int>& perm) {
        if (idx == nums.size()) {
            ans.emplace_back(perm);
            return;
        }
        for (int i = 0; i < (int)nums.size(); ++i) {
            if (visit[i] || (i > 0 && nums[i] == nums[i - 1] && !visit[i - 1])) {
                continue;
            }
            perm.emplace_back(nums[i]);
            visit[i] = 1;
            backtrack(nums, ans, idx + 1, perm);
            visit[i] = 0;
            perm.pop_back();
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> arr;
        visit.resize(nums.size());
        sort(nums.begin(),nums.end());
        backtrack(nums,ans,0,arr);
        return ans;
    }

    void dfs(vector<int>& nums, vector<vector<int>> &ans,int idx, vector<int> arr){
        if(idx == nums.size()){
            ans.emplace_back(arr);
            return;
        }

        for(int i=0; i<nums.size(); i++){
            if(visit[i] || (i>0 && nums[i] == nums[i-1] && !visit[i-1])){
                continue;
            }
            arr.emplace_back(nums[i]);
            visit[i] = 1;
            dfs(nums,ans,idx+1,arr);
            visit[i] = 0;
            arr.pop_back();
        }
    
    }
};