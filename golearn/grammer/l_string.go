package main

import "fmt"

func l_string(s string) int {
	res := 0
	ch := rune(s[0])
	for i:= 1; i<len(s); i++ {
		c := rune(s[i])
		if c < ch {
			res = 1
			ch = c
		} else if c == ch {
			res++
		}
	}
	return res
}

func numSmallerByFrequency(queries []string, words []string) []int {
    count := make([]int, 12)
    for _,s:=range words {
        count[l_string(s)] += 1
    }

    for i:=9; i>=1; i-- {
        count[i] += count[i+1]
    }
    res := make([]int, len(queries))
    for i,s := range queries {
        res[i] = count[l_string(s) +1]
    }
    return res
}

func l_string(s string) int {
    cnt := 0
    ch := 'z'
    for _, c := range s {
        if c < ch {
        ch = c
        cnt = 1
        } else if c == ch {
        cnt++
        }
    }
    return cnt
}

func findIndex(sortedArr []int, target int) int {
    if target <= sortedArr[0] {
        return 0
    }
    if target >= sortedArr[len(sortedArr)-1] {
    	return len(sortedArr)
    }
    l := 0
    r := len(sortedArr) - 1
    for l < r {
        mid := (l + r) / 2
        if sortedArr[mid] < target {
            l = mid + 1
        } else {
            r = mid - 1
            if sortedArr[mid] == target {
                r = mid
            }
        }
    }
    if sortedArr[l] == target {
        return l
    }
    return l + 1
}

func countLarger(sortedArr []int, target int) int {
    l := 0
    r := len(sortedArr) - 1
    for l <= r {
        mid := (l + r) / 2
        if sortedArr[mid] <= target {
            l = mid + 1
        } else {
            r = mid - 1
        }
    }
    return len(sortedArr) - r - 1
}

func main() {
	res := l_string("dcce")
	fmt.Println("res = ",res)

	arr := []int{1}
	num:=findIndex(arr, 8)
	fmt.Println(num)

}