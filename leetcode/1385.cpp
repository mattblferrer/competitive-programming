class Solution {
public:
    int findTheDistanceValue(vector<int> &arr1, vector<int> &arr2, int d) {
        set<int> arr2_set(arr2.begin(), arr2.end());
        arr2_set.insert(-1'000'000'000);
        arr2_set.insert(1'000'000'000);
        int ans = 0;
        for (int i = 0; i < arr1.size(); i++) {
            auto ub = arr2_set.upper_bound(arr1[i]);
            int low = *prev(ub), high = *ub;
            if ((low < arr1[i] - d) && (arr1[i] + d < high)) ans++;
        }
        return ans;
    }
};