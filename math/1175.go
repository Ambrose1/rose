package main

const mod int = 1e9 + 7

// 判断质数
func isPrime(n int) bool {
	for i:=2; i*i<=n; i++ {
		if n%i==0 {
			return false
		}
	}
	return true
}

// 计算阶乘，可能越界，求mod
func caljiecheng(n int) int {
	f := 1
	for i := 1; i <= n; i++ {
		f = f*i%mod
	}
	return f
}

// 排列组合 n!
func numPrimeArrangements(n int) int {
    num := 0
    for i:=2; i<=n; i++ {
        if isPrime(i) {
            num++
        }
    }
    return factorial(num) * factorial(n-num) % mod
}