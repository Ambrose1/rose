#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int missingNumber(vector<int>& nums) {

        vector<int> help(nums.size(),0);
        for(int i : nums) {
            if(i>=0 && i<nums.size()){
                help[i] = -1;
            }
        }
        
        for(int i =0; i < nums.size(); i++){
            if(help[i] != -1){
                return i;
            }
        }
        return nums.size();
    }
};