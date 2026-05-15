#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int minimumFlips(int n) {
        string rev = "";
        while (n > 0) {
            if (n & 1) rev += '1';
            else rev += '0';
            n /= 2;
        }
        string s = rev;
        reverse(s.begin(), s.end());
        int ans = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] != rev[i]) ans++;
        }
        return ans;
    }
};