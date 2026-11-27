class Solution {
public:
    bool validDigit(int n, int x) {
        string nstr = to_string(n);
        if (nstr[0] == '0' + x) return false;
        for (int i = 0; i < nstr.size(); i++) {
            if (nstr[i] == '0' + x) return true;
        }
        return false;
    }
};