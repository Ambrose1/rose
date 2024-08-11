class Solution:
    def minPathCost(self, grid: List[List[int]], moveCost: List[List[int]]) -> int:
        @cache
        def dfs(i: int, j: int) -> int:
            return grid[i][j] if i == 0 else min(dfs(i-1,k) + moveCost[grid[i-1][k]][j] + grid[i][j] for k in range(len(grid[0])))

        return min(dfs(len(grid) - 1, j) for j in range(len(grid[0])))