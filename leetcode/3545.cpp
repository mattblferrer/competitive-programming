class Solution {
public:
    int minDeletion(string s, int k) {
        vector<int> cnt(26);
        for (char c : s) cnt[c - 'a']++;
        sort(cnt.begin(), cnt.end(), greater<int>());
        int ans = 0;
        for (int i = k; i < 26; i++) ans += cnt[i];
        return ans;
    }
};