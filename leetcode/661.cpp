#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> imageSmoother(vector<vector<int>>& img) {
        int m = img.size(), n = img[0].size();
        vector<vector<int>> ans(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int cnt = 0, sum = 0;
                for (int dy = -1; dy <= 1; dy++) {
                    for (int dx = -1; dx <= 1; dx++) {
                        if ((i + dy < 0) || (i + dy >= m)) continue;
                        if ((j + dx < 0) || (j + dx >= n)) continue;
                        cnt++;
                        sum += img[i + dy][j + dx];
                    }
                }
                ans[i][j] = sum / cnt;
            }
        }
        return ans;
    }
};