#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxDistinct(string s) {
        set<char> distinct;
        for (int i = 0; i < s.size(); i++) distinct.insert(s[i]);
        return distinct.size();
    }
};