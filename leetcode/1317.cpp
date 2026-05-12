#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool is_valid(int n) {
        string s = to_string(n);
        for (char c : s) {
            if (c == '0') return false;
        }
        return true;
    }

    vector<int> getNoZeroIntegers(int n) {
        for (int i = 1; i < n; i++) {
            if (is_valid(i) && is_valid(n - i)) return {i, n - i};
        }
        return {0, 0};
    }
};