#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int row, col;
    bool is_valid(int x, int y) {
        if (x < 0 || x >= row) return false;
        if (y < 0 || y >= col) return false;
        return true;
    }
    int islandPerimeter(vector<vector<int>>& grid) {
        vector<int> xs = {1, 0, -1, 0}, ys = {0, 1, 0, -1};
        
        row = grid.size(), col = grid[0].size();
        int ans = 0;
        vector<vector<bool>> seen(row, vector<bool>(col, false));
        queue<pair<int, int>> q;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (grid[i][j] && q.size() == 0) {
                    q.push({i, j});
                    seen[i][j] = true;
                }   
            }
        }
        while (!q.empty()) {
            auto curr = q.front();
            q.pop();
            int x = curr.first;
            int y = curr.second;
            for (int i = 0; i <= 3; i++) {
                if (!is_valid(x + xs[i], y + ys[i])) ans++;
                else if (grid[x + xs[i]][y + ys[i]] == 0) ans++;
                else if (!seen[x + xs[i]][y + ys[i]]) {
                    q.push({x + xs[i], y + ys[i]});
                    seen[x + xs[i]][y + ys[i]] = true;
                }
            }
        }
        return ans;
    }
};