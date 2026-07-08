class Solution {
public:
    int garbageCollection(vector<string> &garbage, vector<int> &travel) {
        int ans = 0, n = garbage.size();
        map<char, int> max_g;
        for (int i = 0; i < n; i++) {
            for (char c : garbage[i]) max_g[c] = max(max_g[c], i);
        }
        for (char c : "MPG") {
            for (int i = 0; i <= max_g[c]; i++) {
                if (i != 0) ans += travel[i - 1];
                for (char ch : garbage[i]) {
                    if (ch == c) ans++;
                }
            }
        }
        return ans;
    }
};