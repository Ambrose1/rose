// 面试题 16.19. 水域大小
func pondSizes(land [][]int) []int {
	m, n := len(land), land(land[0])
	var dfs func(int ,int) int 
	dfs = func(x, y int) int {
		if x < 0 || x >=m || y < 0 || y >= n || land[x][y] != 0 {
			return 0
		}

		land[x][y] = 1
		res := 1
		for i := -1; i <= 1; i++ {
			for j:=-1; j <=1; j++ {
				if i == 0 && j == 0 {
					continue
				}
				res += dfs(x+i, y+j)
			}
		}
		return res
	}

	res := []int{}
	for i:=0; i < m; i++ {
		for j:=0; j < n; j++ {
			if land[i][j] == 0 {
				res = append(res, dfs(i,j))
			}
		}
	}
	return res
}