class Solution {
public:
    long long minCost(vector<int> &arr, vector<int> &brr, long long k) {
        int n = arr.size();
        long long reorder = 0, equal = 0;
        for (int i = 0; i < n; i++) {
            equal += abs(arr[i] - brr[i]);
        }
        sort(arr.begin(), arr.end());
        sort(brr.begin(), brr.end());
        for (int i = 0; i < n; i++) {
            reorder += abs(arr[i] - brr[i]);
        }
        return min(equal, k + reorder);
    }
};