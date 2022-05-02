#
# @lc app=leetcode.cn id=79 lang=python3
#
# [79] 单词搜索
#

# @lc code=start
class Solution:
    def __init__(self):
        self.res = False

    def exist(self, board: List[List[str]], word: str) -> bool:
        m = len(board)
        if(m == 0):return False
        n = len(board[0])
        visit = []
        for i in range(m):
            tmp = list()
            for j in range(n):
                tmp.append(0)
            visit.append(tmp)
        
        for x in range(m):
            for y in range(n):
                if board[x][y] == word[0]:
                    visit[x][y] = 1
                    self.callback(visit, board, x, y, m, n, 1, word,word[0])
                    print(self.res)

                    if self.res:
                        return True
                    else:
                        visit[x][y] = 0
        return False

    # visit 访问数组
    # index 下一位下标
    # word 目标字符串
    def callback(self,visit,board,x,y,m,n,index,word,tmp):
        if index >= len(word): 
            self.res = True
            return 
        if x < m-1 and board[x+1][y] == word[index] and visit[x+1][y] != 1:
            visit[x+1][y] = 1
            tmp+=word[index]
            self.callback(visit, board, x+1, y, m, n, index+1, word,tmp)
            tmp.removesuffix(word[index])
            visit[x+1][y] = 0
        if x > 0 and visit[x-1][y] != 1 and board[x-1][y] == word[index]:
            visit[x-1][y] = 1
            tmp+=word[index]
            self.callback(visit, board, x-1, y, m, n, index+1, word,tmp)
            tmp.removesuffix(word[index])
            visit[x-1][y] = 0
        if y>0 and visit[x][y-1] != 1 and board[x][y-1] == word[index]:
            visit[x][y-1] = 1
            tmp+=word[index]
            self.callback(visit, board, x, y-1, m, n, index+1, word,tmp)
            tmp.removesuffix(word[index])
            visit[x][y-1] = 0
        if y<n-1 and visit[x][y+1] != 1 and board[x][y+1] == word[index]:
            visit[x][y+1] = 1
            tmp+=word[index]
            self.callback(visit, board, x, y+1, m, n, index+1, word,tmp)
            tmp.removesuffix(word[index])
            visit[x][y+1] = 0
        
        

# @lc code=end

