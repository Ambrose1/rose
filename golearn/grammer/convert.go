package main

import (
	"fmt"
	"strconv"
	"regexp"
)

func main() {
	str := "0012345a"

	regex := regexp.MustCompile("[a-z]")
    if regex.MatchString(str) {
        fmt.Printf("字符串长度：%d\n",len(str))
    }
	
	// 将字符串转换为整数类型
	num, err := strconv.Atoi(str)
	
	if err != nil {
		fmt.Println("转换失败:", err)
		return
	}
	
	fmt.Printf("转换后的整数：%d\n", num)
}
