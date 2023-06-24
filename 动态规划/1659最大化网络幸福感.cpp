#include<iostream>

class Solution {
private:
    static constexpr int T = 243, N = 5, M = 6;
    int n, m, tot;
    int mask_bits[T][N];
    int iv_count[T], ev_count[T];
    int inner_score[T], inter_score[T][T];
    int d[N][T][M + 1][M + 1];

    // 邻居间的分数
    static constexpr int score[3][3] = {
        {0, 0, 0},
        {0, -60, -10},
        {0, -10, 40}
    };

public:
    void init_data() {
        // 计算行内分数
        for (int mask = 0; mask < tot; mask++) {
            int mask_tmp = mask;
            for (int i = 0; i < n; i++) {
                int x = mask_tmp % 3;
                mask_bits[mask][i] = x;
                mask_tmp /= 3;
                if (x == 1) {
                    iv_count[mask]++;
                    inner_score[mask] += 120;
                } else if (x == 2) {
                    ev_count[mask]++;
                    inner_score[mask] += 40;
                }
                if (i > 0) {
                    inner_score[mask] += score[x][mask_bits[mask][i - 1]];
                }
            }
        }
        // 计算行间分数
        for (int i = 0; i < tot; i++) {
            for (int j = 0; j < tot; j++) {
                inter_score[i][j] = 0;
                for (int k = 0; k < n; k++) {
                    inter_score[i][j] += score[mask_bits[i][k]][mask_bits[j][k]];
                }
            }
        }
    }

    int getMaxGridHappiness(int m, int n, int introvertsCount, int extrovertsCount) {
        this->n = n;
        this->m = m;
        // 状态总数为 3^n
        this->tot = pow(3, n);

        init_data();
        // 记忆化搜索数组，初始化为 -1，表示未赋值
        memset(d, -1, sizeof d);
        return dfs(0, 0, introvertsCount, extrovertsCount);
    }

    int dfs(int row, int premask, int iv, int ev) {
        if (row == m || (iv == 0 && ev == 0)) {
            return 0;
        }
        // 如果该状态已经计算过答案，则直接返回
        if (d[row][premask][iv][ev] != -1) {
            return d[row][premask][iv][ev];
        }
        // 使用引用，简化代码
        int& res = d[row][premask][iv][ev];
        // 合法状态，初始值为 0
        res = 0;
        for (int mask = 0; mask < tot; mask++) {
            // mask 包含的内向人数不能超过 iv ，外向人数不能超过 ev
            if (iv_count[mask] > iv || ev_count[mask] > ev) {
                continue;
            }
            res = max(res, dfs(row + 1, mask, iv - iv_count[mask], ev - ev_count[mask]) 
                            + inner_score[mask] 
                            + inter_score[premask][mask]);
        }
        return res;
    }
};