class Solution:
    def findWinners(self, matches: List[List[int]]) -> List[List[int]]:
        # 初始化两个字典，分别存储每个玩家输掉比赛的次数和输掉比赛的玩家列表
        losers_count = {}
        
        # 遍历比赛结果，更新字典和集合
        for winner, loser in matches:
            # 如果胜者不在字典中，则初始化其输掉比赛的次数为 0
            if winner not in losers_count:
                losers_count[winner] = 0
            # 如果败者不在字典中，则初始化其输掉比赛的次数为 1，并将其添加到输掉比赛的玩家集合中
            if loser not in losers_count:
                losers_count[loser] = 1
            # 如果败者已经输过比赛，则增加其输掉比赛的次数
            else:
                losers_count[loser] += 1
        
        # 从所有玩家中移除输掉比赛的玩家，得到没有输掉任何比赛的玩家集合
        winners_list = [player for player in losers_count if losers_count[player] == 0]
        
        # 从所有玩家中移除输掉比赛的玩家，得到恰好输掉一场比赛的玩家集合
        losers_list = [player for player in losers_count if losers_count[player] == 1]
        
        # 对两个列表进行排序
        winners_list.sort()
        losers_list.sort()
        
        return [winners_list, losers_list]

            


