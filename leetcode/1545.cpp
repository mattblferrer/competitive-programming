class Solution {
public:
    char findKthBit(int n, int k) {
        string s = "0";
        for (int i = 0; i < n; i++) {
            string s_add = s;
            s += '1';
            for (int j = s_add.size() - 1; j >= 0; j--) {
                if (s_add[j] == '0') s += '1';
                else s += '0';
            }
        }
        return s[k - 1];
    }
};