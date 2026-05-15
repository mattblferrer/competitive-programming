#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> x_moves = {0, 1, 0, -1};
    vector<int> y_moves = {1, 0, -1, 0};

    int numIslands(vector<vector<char>>& grid) {
        int ans = 0;
        int m = grid.size(), n = grid[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '0') continue;
                ans++;
                queue<pair<int, int>> q;
                q.push({i, j});
                grid[i][j] = '0';
                
                while (!q.empty()) {
                    int curr_i = q.front().first, curr_j = q.front().second;
                    q.pop();
                    for (int mx = 0; mx < 4; mx++) {
                        int new_i = curr_i + x_moves[mx];
                        int new_j = curr_j + y_moves[mx];
                        if ((new_i < 0) || (new_i >= m)) continue;
                        if ((new_j < 0) || (new_j >= n)) continue;
                        if (grid[new_i][new_j] == '1') {
                            q.push({new_i, new_j});
                            grid[new_i][new_j] = '0';
                        }
                    }
                }
            }
        }
        return ans;
    }
};