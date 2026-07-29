class Solution {
public:
    int largestSumAfterKNegations(vector<int> &nums, int k) {
        priority_queue<int, vector<int>, greater<int>> pq(nums.begin(), nums.end());
        for (int i = 0; i < k; i++) {
            int curr = pq.top();
            pq.pop();
            pq.push(-curr);
        }
        int ans = 0;
        while (!pq.empty()) {
            int curr = pq.top();
            pq.pop();
            ans += curr;
        }
        return ans;
    }
};