#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> closest_ints(int num) {
        vector<int> ans = {1, num};
        for (int i = 2; i*i <= num; i++) {
            if (num % i == 0) ans = {i, num / i};
        }
        return ans;
    }

    vector<int> closestDivisors(int num) {
        auto p1 = closest_ints(num + 1);
        auto p2 = closest_ints(num + 2);
        int diff1 = abs(p1[0] - p1[1]);
        int diff2 = abs(p2[0] - p2[1]);
        if (diff1 > diff2) return p2;
        else return p1;
    }
};