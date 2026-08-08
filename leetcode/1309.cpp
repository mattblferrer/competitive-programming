class Solution {
public:
    string freqAlphabets(string s) {
        string ans = "";
        for (int i = s.size() - 1; i >= 0; i--) {
            if (s[i] == '#') {
                int idx = 10 * (s[i - 2] - '0') + (s[i - 1] - '0') - 1;
                ans += idx + 'a';
                i -= 2;
            }
            else {
                int idx = s[i] - '0' - 1;
                ans += idx + 'a';
            }
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};