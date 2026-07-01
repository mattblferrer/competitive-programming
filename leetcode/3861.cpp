class Solution {
public:
    int minimumIndex(vector<int> &capacity, int itemSize) {
        int ans = -1, min_cap = INT_MAX;
        for (int i = 0; i < capacity.size(); i++) {
            if (capacity[i] < itemSize) continue;
            if (min_cap > capacity[i]) {
                ans = i;
                min_cap = capacity[i];
            }
        }
        return ans;
    }
};