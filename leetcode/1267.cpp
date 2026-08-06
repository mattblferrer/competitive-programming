class Solution {
public:
    int countServers(vector<vector<int>> &grid) {
        int ans = 0, m = grid.size(), n = grid[0].size();
        vector<int> rows(m), cols(n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    ans++;
                    rows[i]++;
                    cols[j]++;
                }
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) continue;
                if ((rows[i] == 1) && (cols[j] == 1)) ans--;
            }
        }
        return ans;
    }
};