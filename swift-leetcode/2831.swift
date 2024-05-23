class Solution {
    func longestEqualSubarray(_ nums: [Int], _ k: Int) -> Int {
       var cnt: [Int: Int] = [:]
        let n = nums.count
        var j = 0
        var ans = 0
        
        for i in 0..<n {
            cnt[nums[i], default: 0] += 1 // 使用 default 参数来初始化不存在的键
            while i - j + 1 - cnt[nums[j], default: 0] > k {
                cnt[nums[j], default: 0] -= 1
                j += 1
            }
            ans = max(ans, cnt[nums[i], default:0])
        }
        
        return ans
    }
}