class Solution {
public:
    int elevatorRequests(int n, vector<int> &requests) {
        int ans = requests[0];
        for (int i = 0; i < requests.size() - 1; i++) ans += abs(requests[i + 1] - requests[i]);
        return ans;
    }
};