class Solution {
public:
    vector<vector<int>> cyclicShift(int n, vector<vector<int>> &grid, vector<int> &rowShift, vector<int> &colShift) {
        for (int i = 0; i < n; i++) {
            int k = rowShift[i];
            vector<int> row = grid[i];
            for (int j = 0; j < n; j++) {
                grid[i][(j - k + n) % n] = row[j];
            }
        }
        for (int i = 0; i < n; i++) {
            int k = colShift[i];
            vector<int> col;
            for (int j = 0; j < n; j++) col.push_back(grid[j][i]);
            for (int j = 0; j < n; j++) {
                grid[(j - k + n) % n][i] = col[j];
            }
        }
        return grid;
    }
};