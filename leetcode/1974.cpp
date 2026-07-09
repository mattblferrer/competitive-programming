class Solution {
public:
    int minTimeToType(string word) {
        int curr = 0, ans = 0;
        for (char c : word) {
            c -= 'a';
            ans += min(abs(c - curr), 26 - abs(c - curr)) + 1;
            curr = c;
        }
        return ans;
    }
};