class Solution {
public:
    vector<string> createGrid(int m, int n, int k) {
        if (((m == 1) || (n == 1)) && (k > 1)) return {};  // 1w or 1h arr, more than 1 path
        vector<string> grid(m);
        if (m == 1) {
            for (int j = 0; j < n; j++) {
                grid[0] += '.';
            }
            return grid;
        }
        if (n == 1) {
            for (int i = 0; i < m; i++) {
                grid[i] = ".";
            }
            return grid;
        }
        if ((m >= 2) && (n >= k)) {
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < k; j++) {
                    grid[i] += '.';
                }
            }
            for (int j = k; j < n; j++) {
                grid[0] += '#';
                grid[1] += '.';
            }
            for (int i = 2; i < m; i++) {
                for (int j = 0; j < n - 1; j++) {
                    grid[i] += '#';
                }
                grid[i] += '.';
            }
            return grid;
        }
        if ((m >= k) && (n >= 2)) {
            for (int i = 0; i < k; i++) {
                for (int j = 0; j < 2; j++) {
                    grid[i] += '.';
                }
            }
            for (int i = 0; i < k - 1; i++) {
                for (int j = 2; j < n; j++) {
                    grid[i] += '#';
                }
            }
            for (int j = 2; j < n; j++) {
                grid[k - 1] += '.';
            }
            for (int i = k; i < m; i++) {
                for (int j = 0; j < n - 1; j++) {
                    grid[i] += '#';
                }
                grid[i] += '.';
            }
            return grid;
        }
        if ((m >= 3) && (n >= 3)) {
            grid[0] = "..#";
            grid[1] = "...";
            grid[2] = "#..";
            return grid;
        }
        return {};
    }
};