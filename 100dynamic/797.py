class Solution:
    def allPathsSourceTarget(self, graph: List[List[int]]) -> List[List[int]]:
        n = len(graph)
        ans = []
        def dfs(i, route):
            if (n - 1 == i):
                ans.append(route[:])
                return
            for k in graph[i]:
                route.append(k)
                dfs(k, route)
                del route[-1]
        dfs(0,[0])
        return ans