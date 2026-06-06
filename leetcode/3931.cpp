#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isAdjacentDiffAtMostTwo(string s) {
        for (int i = 0; i < s.size() - 1; i++) {
            if (abs(s[i + 1] - s[i]) > 2) return false;
        }
        return true;
    }
};