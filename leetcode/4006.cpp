class Solution {
public:
    int countValidPrefixes(string s) {
        vector<int> cnt(2);
        int ans = 0;
        for (char c : s) {
            cnt[c - '0']++;
            if (abs(cnt[0] - cnt[1]) <= 1) ans++;
        }
        return ans;
    }
};