#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        map<int, int> cnt;
        for (int i = 0; i < nums.size(); i++) {
            cnt[nums[i]]++;
        }
        vector<pair<int, int>> cnt_pairs;
        for (const auto& pair : cnt) {
            cnt_pairs.push_back({pair.second, pair.first});
        }
        sort(cnt_pairs.begin(), cnt_pairs.end(), greater<pair<int, int>>());
        vector<int> ans;
        for (int i = 0; i < k; i++) ans.push_back(cnt_pairs[i].second);
        return ans;
    }
};