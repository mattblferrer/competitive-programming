class Solution {
public:
    int minOperations(string s1, string s2) {
        int n = s1.size();
        if (n == 1) {
            if (s1 == s2) return 0;
            else if (s1[0] == '0') return 1;
            else return -1;
        }
        int ans = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (s1[i] == '1' && s2[i] == '0') {
                if (i == 0) {
                    ans += 2;
                    break;
                }
                if (s1[i - 1] == '0') ans++;
                s1[i] = '0';
                s1[i - 1] = '0';
                ans++;
            }
            else if (s1[i] == '0' && s2[i] == '1') {
                s1[i] = '1';
                ans++;
            }
        }
        return ans;
    }
};