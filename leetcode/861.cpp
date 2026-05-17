#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int matrixScore(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        for (int i = 0; i < m; i++) {
            if (grid[i][0] == 0) {
                for (int j = 0; j < n; j++) grid[i][j] = 1 - grid[i][j];
            }
        }
        for (int i = 0; i < n; i++) {
            int ones = 0, zeros = 0;
            for (int j = 0; j < m; j++) {
                if (grid[j][i] == 0) zeros++;
                else ones++;
            }
            if (zeros < ones) continue;
            for (int j = 0; j < m; j++) grid[j][i] = 1 - grid[j][i];
        }
        int score = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                score += grid[i][j] * (1 << (n - j - 1));
            }
        }
        return score;
    }
};