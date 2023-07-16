package main

func sumOfDistancesInTree(n int, edges [][]int) []int {
	grapth := make([][]int, n)

	for _, v := range edges {
		x, y := v[0], v[1]
		grapth[x] = append(grapth[x], y)
		grapth[y] = append(grapth[y], x)
	}

	ans := make([]int, n)
	sz := make([]int, n)

	var dfs func(x, p, d int)
	dfs = func(x, p, d int) {
		ans[0] += d
		sz[x] = 1
		for _, v := range grapth[x] {
			if v != p {
				// 递归算法中，顺序看是需要从前往后算还是从后向前
				dfs(v, x, d+1)
				// 此处计算树的子节点数量，明显是从后向前算，需要先递归到头，在执行计算，所以先写递归，然后想加
				sz[x] += sz[v]
			}
		}
	}
	dfs(0, -1, 0)

	var root func(int, int)
	root = func(x, p int) {
		for _, v := range grapth[x] {
			if v != p {
				// 此处从上向下计算，动态规划每个节点的值，所以在递归之前。
				ans[v] = ans[x] + n - 2*sz[v]
				root(v, x)
			}
		}
	}
	root(0, -1)
	return ans
}
