#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string toHex(int num) {
        unsigned int n = num;
        if (n < 0) n += (1 << 31);
        if (n == 0) return "0";
        string ans = "";
        while (n > 0) {
            int rem = n % 16;
            if (rem > 9) ans += 'a' + (rem - 10);
            else ans += '0' + rem;
            n /= 16;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};