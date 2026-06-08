class Solution {
public:
    vector<int> pivotArray(vector<int>& nums, int pivot) {
        vector<int> small, big;
        int p = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] < pivot) small.push_back(nums[i]);
            else if (nums[i] > pivot) big.push_back(nums[i]);
            else p++;
        }
        for (int i = 0; i < small.size(); i++) nums[i] = small[i];
        for (int i = small.size(); i < small.size() + p; i++) nums[i] = pivot;
        for (int i = 0; i < big.size(); i++) nums[small.size() + p + i] = big[i];
        return nums;
    }
};