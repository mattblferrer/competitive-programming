class Solution {
public:
    int minOperations(string s) {
        int n = s.size();
        s += s;
        int ans = 1'000'000;
        for (int i = 0; i < n; i++) {
            int curr = i;
            for (int j = 0; j < n / 2; j++) {
                int diff = (s[i + j] - s[i + n - j - 1] + 26) % 26;
                curr += min(diff, 26 - diff);
            }
            ans = min(ans, curr);
        }
        return ans;
    }
};