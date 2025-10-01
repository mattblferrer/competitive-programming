    #include <bits/stdc++.h>
    using namespace std;

class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& nums) {
        sort(nums.begin(), nums.end(), [](int a, int b) {
            return a % 2 < b % 2;
        });
        return nums;
    }
};