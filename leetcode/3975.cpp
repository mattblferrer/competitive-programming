class Solution {
public:
    vector<vector<int>> filterOccupiedIntervals(vector<vector<int>> &occupiedIntervals, int freeStart, int freeEnd) {
        sort(occupiedIntervals.begin(), occupiedIntervals.end());
        vector<vector<int>> merged;
        for (auto interval : occupiedIntervals) {
            if (merged.empty() || merged.back()[1] < interval[0] - 1) merged.push_back(interval);
            else merged.back()[1] = max(merged.back()[1], interval[1]);
        }
        set<vector<int>> merged_set(merged.begin(), merged.end());
        for (int i = 0; i < merged.size(); i++) {
            auto interval = merged[i];
            int start = interval[0], end = interval[1];
            if (end < freeStart) continue;
            if (start > freeEnd) continue;

            merged_set.erase(interval);
            if ((freeStart <= start) && (end <= freeEnd)) continue;
            else if ((start < freeStart) && (freeEnd < end)) {
                merged_set.insert({start, freeStart - 1});
                merged_set.insert({freeEnd + 1, end});
            }
            else if ((freeStart <= start)) merged_set.insert({freeEnd + 1, end});
            else merged_set.insert({start, freeStart - 1});
        }
        vector<vector<int>> ans;
        for (auto interval : merged_set) {
            ans.push_back(interval);
        }
        return ans;
    }
};