class Solution:
    def isWinner(self, player1: List[int], player2: List[int]) -> int:
        sum1, sum2 = 0,0
        f1, f2 = 1,1
        for i in range(len(player1)):
            sum1 += player1[i] * f1
            sum2 += player2[i] * f2
            if player1[i] == 10:
                f1 = 2
            elif (i > 1 and player1[i-1] != 10):
                f1 = 1
            if player2[i] == 10:
                f2 = 2
            elif (i > 1 and player2[i-1] != 10):
                f2 = 1
        if sum1 == sum2 :
            return 0
        return 1 if sum1 > sum2 else 2
