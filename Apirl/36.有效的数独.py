#
# @lc app=leetcode.cn id=36 lang=python3
#
# [36] 有效的数独
#

# @lc code=start
class Solution:
    def isValidSudoku(self, board: List[List[str]]) -> bool:
        for i in range(9):
            num = set()
            cols = set()
            for j in range(9):
                if board[i][j] in num:
                    print(num)
                    return False
                if board[i][j] != ".":
                    num.add(board[i][j])
                if board[j][i] in cols:
                    print(cols)
                    return False
                if board[j][i] != ".":
                    cols.add(board[j][i])
        
        for x in range(3):
            for y in range(3):
                if board[x][y] == ".":
                    continue
                if board[x][y] in num:
                    return False
                num.add(board[i+x][j+y])
        return True
            



# @lc code=end

