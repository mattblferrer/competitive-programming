class Solution {
public:
    long long removeZeros(long long n) {
        string nstr = to_string(n);
        string ans = "";
        for (int i = 0; i < nstr.size(); i++) {
            if (nstr[i] != '0') ans += nstr[i];
        }
        return stoll(ans);
    }
};