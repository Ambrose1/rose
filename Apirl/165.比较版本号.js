/*
 * @lc app=leetcode.cn id=165 lang=javascript
 *
 * [165] 比较版本号
 */

// @lc code=start
/**
 * @param {string} version1
 * @param {string} version2
 * @return {number}
 */
var compareVersion = function(version1, version2) {
    var ver1 = version1.split(".")
    var ver2 = version2.split(".")
    let n = ver1.length > ver2.length ? ver2.length : ver1.length;
    let i = 0;
    while(i<n){
        let left = parseInt(ver1[i],10);
        let right = parseInt(ver2[i],10);
        if(left < right){
            return -1;
        }else if(left > right) {
            return 1;
        }
        i++;
    }
    if(ver1.length > n){
        let j=n;
        while(j<ver1.length ){
            if(ver1[j] > 0){
                return 1;
            }
            j++;
        }
    }else if (ver2.length > n){
        let j=n;
        while(j<ver2.length ){
            if(ver2[j] > 0){
                return -1;
            }
            j++;
        }
    }
    return 0;
};
// @lc code=end

