class Solution {
public:
    int equalPairs(vector<vector<int>> &grid) {
        map<vector<int>, int> rows, cols;
        int n = grid.size();
        for (int i = 0; i < n; i++) {
            rows[grid[i]]++;
            vector<int> curr;
            for (int j = 0; j < n; j++) {
                curr.push_back(grid[j][i]);
            }
            cols[curr]++;
        }
        int ans = 0;
        for (const auto &pair : rows) {
            if (cols.count(pair.first)) ans += pair.second * cols[pair.first];
        }
        return ans;
    }
};