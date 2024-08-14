class Solution:
    def cherryPickup(self, grid: List[List[int]]) -> int:
        m,n = len(grid), len(grid[0])
        def getValue(i,j1,j2):
            return grid[i][j1] + grid[i][j2] if j1 != j2 else grid[i][j1]
        @lru_cache(None)
        def dfs(i, j1, j2):
            if i == m-1:
                return getValue(i, j1, j2)
            best = 0
            for dj1 in [j1 -1, j1, j1 + 1]:
                for dj2 in [j2-1,j2,j2+1]:
                    if 0 <= dj1 < n and 0 <= dj2 < n:
                        best = max(best, dfs(i+1,dj1,dj2))
            return best + getValue(i,j1, j2)
        return dfs(0,0,n-1)