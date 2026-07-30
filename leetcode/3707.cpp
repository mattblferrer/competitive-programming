class Solution {
public:
    bool scoreBalance(string s) {
        int score = 0, curr = 0;
        for (char c : s) score += c - 'a' + 1;
        if (score % 2 == 1) return false;
        for (char c : s) {
            curr += c - 'a' + 1;
            if (curr * 2 == score) return true;
        }
        return false;
    }
};