package main

import (
	"fmt"
)

func backpack(num []int,path []int, used []bool, res *[][]int) {
	if len(path) == len(num) {
		tmp := make([]int , len(path))
		copy(tmp, path)
		*res = append(*res, tmp)
		return
	}

	for i:=0; i<len(num); i++ {
		if !used[i] {
			path = append(path, num[i])
			used[i] = true
			backpack(num, path, used, res)
			used[i] = false
			path = path[:len(path)-1]
		}
	}
}

func
main() {
	num := []int{1,2,3,4}
	res := [][]int{}
	used := make([]bool, len(num))
	backpack(num, []int{}, used,&res)
	fmt.Println(res)
}