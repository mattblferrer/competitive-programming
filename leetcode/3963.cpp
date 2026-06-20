class Solution {
public:
    vector<string> createGrid(int m, int n) {
        vector<string> ans(m);
        for (int i = 0; i < n; i++) ans[0] += '.';
        for (int i = 1; i < m; i++) {
            for (int j = 0; j < n - 1; j++) ans[i] += '#';
            ans[i] += '.';
        }
        return ans;
    }
}