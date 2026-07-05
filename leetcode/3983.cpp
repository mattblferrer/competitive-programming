class Solution {
public:
    bool canMakeSubsequence(string s, string t) {
        int i = 0, j = 0, n = s.size();
        for (char c : t) {
            i = max(i + (s[i] == c), j + 1);
            if (s[j] == c) j++;
            if (i == n || j == n) return true;
        }
        return false;
    }
};