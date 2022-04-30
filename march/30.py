
# 全排列 + 字符串匹配
res = []

def allStrs(words):
    n = len(words)
    visit = [False for i in range(n)]
    back(words, visit, [], n, 0)
    # dfs(0, words, words[:], visit)
    print(res)

def back(words,visit,current,n,start):
    # 回溯终止条件
    if(len(current) == n):
        res.append("".join(current))
        return
    for i in range(n):
        if(~visit[i] and words[i] not in current):
            visit[i] = True
            current.append(words[i])
            back(words, visit, current, n,i)
            visit[i] = False
            current.pop()

def dfs(pos,words,tmp,visit):
    if pos == len(words):
        res.append("".join(tmp[:]))
        return
    for i in range(len(words)):
        if(~visit[i]):
            tmp[pos] = words[i]
            visit[i] = True
            dfs(pos+1, words, tmp, visit)
            visit[i] = False


if __name__ == "__main__":
    allStrs(["1","2","3"])
    pass
