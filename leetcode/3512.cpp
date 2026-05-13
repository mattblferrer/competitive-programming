#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        int total = 0;
        for (int i = 0; i < nums.size(); i++) total += nums[i];
        return total % k;
    }
};