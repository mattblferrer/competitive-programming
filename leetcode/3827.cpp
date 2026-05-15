#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countMonobit(int n) {
        int ans = 0;
        n++;
        while (n > 0) {
            ans++;
            n /= 2;
        }
        return ans;
    }
};