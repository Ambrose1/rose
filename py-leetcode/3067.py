class Solution:
    def countPairsOfConnectableServers(self, edges: List[List[int]], signalSpeed: int) -> List[int]:
        n =len(edges) + 1
        graph = [[] for _ in range(n)]
        for u,v,w in edges:
            graph[u].append((v, w))
            graph[v].append((u, w))
        def dfs(p, root, curr):
            res = 0
            if curr == 0:
                res += 1
            for v,c in graph[p]:
                if v != root:
                    res += dfs(v, p, (curr + c)%signalSpeed)
            return res
        res = [0] * n
        for i in range(n):
            pre = 0
            for v,c in graph[i]:
                cnt = dfs(v, i, c % signalSpeed)
                res[i] += pre * cnt
                pre += cnt
        return res
                    