class Solution {
public:
    bool hasSameDigits(string s) {
        while (s.size() > 2) {
            string new_s;
            for (int i = 0; i < s.size() - 1; i++) {
                new_s.push_back(((s[i] - '0') + (s[i + 1] - '0')) % 10 + '0');
            }
            s = new_s;
        }
        return s[0] == s[1];
    }
};