class Solution {
    func getWinner(_ arr: [Int], _ k: Int) -> Int {
        let n = arr.count;
        var currk = 0;
        var currMax = arr[0];
        for i in 1..<n {
            if currk == k {
                return currMax;
            }
            if currMax > arr[i] {
                currk+=1;
            } else {
                currk = 1;
                currMax = arr[i];
            }
        }
        return currMax;
    }
}