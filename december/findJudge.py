'''
Author: Ambrose
Date: 2021-12-19 19:15:40
LastEditTime: 2021-12-19 21:56:48
LastEditors: Please set LastEditors
Description: 打开koroFileHeader查看配置 
FilePath: /myweekend/leetcode刷题笔记/december/findJudge.py
'''

'''
description: 
param {int} n
param {list} trust
return {*}
'''
def findJudge(n: int, trust) -> int:
    # dic = [[[1,4],[2,3]],[[2],[3]]]
    res = -1
    dic = [[] for i in range(n)]
    for item in dic: 
        item.append([])
        item.append([])
    print(dic)
    for item in trust:
        index = item[0]-1
        aim = item[1]-1
        dic[index][1].append(aim)
        dic[aim][0].append(index)
    print(dic)
    for i in range(len(dic)):
        if(len(dic[i][1]) == 0 and len(dic[i][0]) == n-1):
            if (res == -1):
                res = i+1
            else:
                return -1
        
    return res

if __name__ == '__main__':
    print(findJudge(3, [[1,2],[2,3]]))

    pass
