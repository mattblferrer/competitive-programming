class Solution {
public:
    string smallestPalindrome(string s) {
        string ans = "";
        int n = s.size();
        sort(s.begin(), s.begin() + n / 2);
        for (int i = 0; i < n / 2; i++) {
            s[n - i - 1] = s[i];
        }
        return s;
    }
};