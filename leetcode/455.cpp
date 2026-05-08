#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int ans = 0, ctr = 0;

        for (int i = 0; i < g.size(); i++) {
            if (ctr >= s.size()) break;
            while (g[i] > s[ctr] && ctr < s.size() - 1) ctr++;
            if (g[i] <= s[ctr]) {
                ans++;
                ctr++;
            }
        }
        return ans;
    }
};