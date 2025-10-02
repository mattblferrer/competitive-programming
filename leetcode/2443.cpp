#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool sumOfNumberAndReverse(int num) {
        for (int i = 0; i < num; i++) {
            string s = to_string(i);
            string rev = s;
            reverse(rev.begin(), rev.end());
            int r = stoi(rev);
            if (i + r == num) return true;
        }
        return false;
    }
};