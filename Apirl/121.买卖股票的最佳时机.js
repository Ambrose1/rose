/*
 * @lc app=leetcode.cn id=121 lang=javascript
 *
 * [121] 买卖股票的最佳时机
 */

// @lc code=start
/**
 * @param {number[]} prices
 * @return {number}
 */
var maxProfit = function(prices) {
    if(prices.length < 2)return 0;
    let max = 0,min=prices[0];
    let n = prices.length;
    for(let i=1; i<n; i++) {
        max = Math.max(max,prices[i] - min);
        min = Math.min(min, prices[i]);
    }
    return max;
};
// @lc code=end

