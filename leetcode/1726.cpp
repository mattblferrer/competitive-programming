class Solution {
public:
    int tupleSameProduct(vector<int> &nums) {
        map<int, int> prod;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (i == j) continue;
                prod[nums[i] * nums[j]]++;
            }
        }
        int ans = 0;
        for (const auto &pair : prod) {
            ans += 4 * pair.second * (pair.second - 1);
        }
        return ans;
    }
};