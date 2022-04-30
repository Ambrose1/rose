/*
 * @lc app=leetcode.cn id=93 lang=cpp
 *
 * [93] 复原 IP 地址
 */

// @lc code=start
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        int n = s.length();
        vector<string> ans;
        string str = "";
        dfs(1,0,s,str,ans);
        return ans;
    }
    /**
     * @brief 
     * 
     * @param index 第几个点
     * @param last  上一个点的位置
     * @param ip    ip
     * @param res   结果集
     */
    void dfs(int index, int last, string &ip, string &str, vector<string> res){
        if (index == 4)
        {
            res.push_back(str);
        }
        string tmp = "";
        for (int i = last; i < ip.length(); i++)
        {
            if (ip[i] == 0)
            {
                str.append(string(ip[i]))
                str.append(".")
                dfs(++index,i+1,ip,str,res);
            }else {
                // 一个数
                str.append(ip[i])
                str.append(".")
                dfs(++index,i+1,ip,str,res);
                // 两个数
                str.append(string(ip,i,2))
                str.append(".")
                dfs(++index,i+2,ip,str,res);
                // 三个数
                if (atoi(string(ip,i,3)) <= 255)
                {
                    str.append(string(ip,i,3))
                    str.append(".")
                    dfs(++index,i+3,ip,str,res);
                }
                
                
            }
            
        }
        
        
        
    }
};
// @lc code=end

