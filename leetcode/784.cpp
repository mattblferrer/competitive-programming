#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> letterCasePermutation(string s) {
        vector<string> ans;
        int letters = 0;
        for (int i = 0; i < s.size(); i++) {
            if (isalpha(s[i])) letters++;
        }
        for (int i = 0; i < (1 << letters); i++) {
            int ctr = 0;
            string curr = "";
            for (int j = 0; j < s.size(); j++) {
                if (!isalpha(s[j])) {
                    curr += s[j];
                    continue;
                }
                if (i & (1 << ctr)) curr += toupper(s[j]);
                else curr += tolower(s[j]);
                ctr++;
            }
            ans.push_back(curr);
        }
        return ans;
    }
};