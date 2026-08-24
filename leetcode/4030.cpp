class Solution {
public:
    bool isPalindromic(string s) {
        string bin = "";
        for (char c : s) {
            for (int i = 128; i >= 1; i /= 2) {
                if (c >= i) {
                    bin += '1';
                    c -= i;
                }
                else bin += '0';
            }
        }
        for (int i = 0; i < bin.size(); i++) {
            if (bin[i] != bin[bin.size() - i - 1]) return false;
        }
        return true;
    }
};