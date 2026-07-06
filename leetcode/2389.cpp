class Solution {
public:
    vector<int> answerQueries(vector<int> &nums, vector<int> &queries) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<int> pref(n);
        pref[0] = nums[0];
        for (int i = 1; i < n; i++) pref[i] = pref[i - 1] + nums[i];

        vector<int> ans;
        for (int i = 0; i < queries.size(); i++) {
            ans.push_back(distance(pref.begin(), upper_bound(pref.begin(), pref.end(), queries[i])));
        }
        return ans;
    }
};