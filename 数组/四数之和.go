package main

import "sort"

func fourSum(nums []int, target int) [][]int {
	sort.Ints(nums)
	n := len(nums)
	res := [][]int{}

	for i := 0; i < n-3 && nums[i]+nums[i+1]+nums[i+2]+nums[i+3] <= target; i++ {
		if i > 0 && nums[i] == nums[i-1] || nums[i]+nums[n-1]+nums[n-2]+nums[n-3] < target {
			continue
		}

		for j := i + 1; j < n-2 && nums[i]+nums[j]+nums[j+1]+nums[j+2] <= target; j++ {
			if j > i+1 && nums[j] == nums[j-1] || nums[i]+nums[j]+nums[n-1]+nums[n-2] < target {
				continue
			}

			newTarget := target - nums[i] - nums[j]
			left, right := j+1, n-1

			for left < right {
				if nums[left]+nums[right] == newTarget {
					res = append(res, []int{nums[i], nums[j], nums[left], nums[right]})

					left++
					for left < right && nums[left-1] == nums[left] {
						left++
					}

					right--
					for left < right && nums[right+1] == nums[right] {
						right--
					}
				} else if nums[left]+nums[right] < newTarget {
					left++
				} else {
					right--
				}
			}
		}
	}

	return res
}
