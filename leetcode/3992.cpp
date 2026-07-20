class Solution {
public:
    string rearrangeString(string s, char x, char y) {
        int x_cnt = 0;
        string ans = "";
        for (char c : s) {
            if (c == x) x_cnt++;
            else ans += c;
        }
        for (int i = 0; i < x_cnt; i++) ans += x;
        return ans;
    }
};