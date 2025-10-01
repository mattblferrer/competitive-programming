#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> decimalRepresentation(int n) {
        vector<int> ans;
        long long curr = 1;
        while (n > 0) {
            if (n % 10 > 0) ans.push_back(curr * (n % 10));
            n /= 10;
            curr *= 10;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};