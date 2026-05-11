#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string addBinary(string a, string b) {
        string ans = "";
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        while (a.size() < b.size()) a += '0';
        while (b.size() < a.size()) b += '0';

        for (int i = 0; i < a.size(); i++) {
            ans.push_back(a[i] + b[i] - '0');
        }
        ans.push_back('0');
        for (int i = 0; i < a.size(); i++) {
            if (ans[i] >= '2') {
                ans[i] -= 2;
                ans[i + 1]++;
            }
        }
        if (ans.back() == '0') ans.pop_back();
        reverse(ans.begin(), ans.end());
        return ans;
    }
};