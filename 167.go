func twoSum(numbers []int, target int) []int {
    
    for i,v := range numbers {
        index2 := findNum(numbers[i+1:], target - v)
        if index2 != -1 {
            return []int{i+1, i+index2 + 2}
        }
    }
    return []int{0}
}

func findNum(nums []int, target int) int {
    l,r := 0, len(nums)-1
    for l <= r {
        mid := (l+r)/2
        if target == nums[mid] {
            return mid
        }
        if target < nums[mid] {
            r = mid - 1
        } else {
            l = mid + 1 
        }
    }

    return -1
}