#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string concatHex36(int n) {
        int n2 = n * n, n3 = n2 * n;
        string ans = "";
        while (n3 > 0) {
            if (n3 % 36 <= 9) ans += ((n3 % 36) + '0');
            else ans += ((n3 % 36) - 10 + 'A');
            n3 /= 36;
        }
        while (n2 > 0) {
            if (n2 % 16 <= 9) ans += ((n2 % 16) + '0');
            else ans += ((n2 % 16) - 10 + 'A');
            n2 /= 16;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};