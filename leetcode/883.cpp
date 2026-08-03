class Solution {
public:
    int projectionArea(vector<vector<int>> &grid) {
        int xy = 0, yz = 0, zx = 0, n = grid.size();
        vector<int> y(n), z(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] > 0) xy++;
                y[j] = max(y[j], grid[i][j]);
                z[i] = max(z[i], grid[i][j]);
            }
        }
        for (int i = 0; i < n; i++) {
            yz += y[i];
            zx += z[i];
        }
        return xy + yz + zx;
    }
};