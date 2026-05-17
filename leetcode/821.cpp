#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> shortestToChar(string s, char c) {
        vector<int> a = {-((int)s.size() * 2)};
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == c) a.push_back(i);
        }
        a.push_back(s.size() * 2);
        vector<int> answer(s.size());
        for (int i = 0; i < s.size(); i++) {
            int low = *prev(lower_bound(a.begin(), a.end(), i));
            int high = *lower_bound(a.begin(), a.end(), i);
            answer[i] = min(abs(high - i), abs(low - i));
        }
        return answer;
    }
};