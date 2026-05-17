#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        int ans = 0;
        for (int i = 0; i < strs[0].size(); i++) {
            bool is_sorted = true;
            for (int j = 0; j < strs.size() - 1; j++) {
                if (strs[j][i] > strs[j + 1][i]) {
                    is_sorted = false;
                    break;
                }
            }
            if (!is_sorted) ans++;
        }
        return ans;
    }
};