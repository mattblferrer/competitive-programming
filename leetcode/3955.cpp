#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> generateValidStrings(int n, int k) {
        vector<string> ans;
        for (int i = 0; i < (1 << n); i++) {
            string s = "";
            int x = i;
            while (x > 0) {
                if (x & 1) s.push_back('1');
                else s.push_back('0');
                x /= 2;
            }
            while (s.size() < n) s.push_back('0');
            reverse(s.begin(), s.end());

            bool valid = true;
            for (int j = 0; j < n - 1; j++) {
                if (s[j] == '1' && s[j + 1] == '1') valid = false;
            }
            if (!valid) continue;

            int cost = 0;
            for (int j = 0; j < n; j++) {
                if (s[j] == '1') cost += j;
            }
            if (cost <= k) ans.push_back(s);
        }
        return ans;
    }
};