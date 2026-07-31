class Solution {
public:
    int maximumLengthSubstring(string s) {
        int ans = 0;
        vector<int> cnt(26);
        int left = 0, right = 0;
        while (right < s.size()) {
            cnt[s[right] - 'a']++;
            bool valid = false;
            while (!valid) {
                valid = true;
                for (int i = 0; i < 26; i++) {
                    if (cnt[i] > 2) {
                        cnt[s[left] - 'a']--;
                        left++;
                        valid = false;
                        break;
                    }
                }
            }
            right++;
            ans = max(ans, right - left);
        }
        return ans;
    }
};