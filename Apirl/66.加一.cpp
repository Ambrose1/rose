/*
 * @lc app=leetcode.cn id=66 lang=cpp
 *
 * [66] 加一
 */

// @lc code=start
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int count = digits.size();
        int jinwei = 0;
        for (int i = count -1; i >= 0; i--)
        {
            int tmp = digits[i] + jinwei;
            if (i == count-1)
            {
                tmp += 1;
            }
            if (tmp > 9)
            {
                jinwei = 1;
                tmp = tmp % 10;
                digits[i] = tmp; 
            }else {
                jinwei = 0;
                digits[i] = tmp; 
                break;
            }           
        }
        if (jinwei == 1)
        {
            digits.insert(digits.begin(),1);
        }
        return digits;
        
    }
};
// @lc code=end

