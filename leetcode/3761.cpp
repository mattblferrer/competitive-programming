class Solution {
public:
    int minMirrorPairDistance(vector<int> &nums) {
        int n = nums.size(), ans = n + 1;
        map<int, vector<int>> idx;
        for (int i = 0; i < n; i++) {
            idx[nums[i]].push_back(i);
        }
        for (int i = 0; i < n; i++) {
            string to_str = to_string(nums[i]);
            reverse(to_str.begin(), to_str.end());
            int rev = stoi(to_str);

            if ((idx[rev].size() > 0) && (idx[rev].back() > i)) {
                ans = min(ans, *(upper_bound(idx[rev].begin(), idx[rev].end(), i)) - i);
            }
        }

        if (ans == n + 1) return -1;
        else return ans;
    }
};