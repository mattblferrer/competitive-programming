#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string makeGood(string s) {
        string ans = "";
        for (int i = 0; i < s.size(); i++) {
            if (ans.empty()) ans.push_back(s[i]);
            else if ((s[i] != ans.back()) && (tolower(s[i]) == tolower(ans.back()))) ans.pop_back();
            else ans.push_back(s[i]);
        }
        return ans;
    }
};