#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProduct(int n) {
        string s = to_string(n);
        sort(s.begin(), s.end());
        char a = s[s.size() - 1];
        char b = s[s.size() - 2];
        return (a - '0') * (b - '0');
    }
};