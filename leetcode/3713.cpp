class Solution {
public:
    int longestBalanced(string s) {
        int ans = 0, n = s.size();
        for (int i = 0; i < n; i++) {
            vector<int> cnt(26);
            for (int j = i; j < n; j++) {
                cnt[s[j] - 'a']++;
                int same_cnt = 0;
                bool balanced = true;
                for (int k = 0; k < 26; k++) {
                    if (cnt[k] != 0) {
                        if (same_cnt == 0) same_cnt = cnt[k];
                        else if (same_cnt != cnt[k]) balanced = false;
                    }
                }

                if (balanced) ans = max(ans, j - i + 1);
            }
        }
        return ans;
    }
};