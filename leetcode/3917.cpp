#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> countOppositeParity(vector<int>& nums) {
        vector<int> answer(nums.size());
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[i] % 2 != nums[j] % 2) answer[i]++;
            }
        }
        return answer;
    }
};