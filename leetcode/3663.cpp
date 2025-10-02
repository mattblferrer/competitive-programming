#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int getLeastFrequentDigit(int n) {
        string s = to_string(n);
        vector<int> freq(10);
        for (char c: s) {
            freq[c - '0']++;
        }
        int ans = 0, f = 10000;
        for (int i = 0; i < 10; i++) {
            if (freq[i] != 0 && freq[i] < f) {
                ans = i;
                f = freq[i];
            }
        }
        return ans;
    }
};