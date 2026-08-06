class Solution {
public:
    long long maxKelements(vector<int> &nums, int k) {
        long long ans = 0;
        priority_queue<int> pq(nums.begin(), nums.end());
        for (int i = 0; i < k; i++) {
            int x = pq.top();
            pq.pop();
            pq.push((x + 2) / 3);
            ans += x;
        }
        return ans;
    }
};