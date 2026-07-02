class Solution {
public:
    int scoreDifference(vector<int> &nums) {
        int s1 = 0, s2 = 0, turn = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] % 2 == 1) turn = 1 - turn;
            if (i % 6 == 5) turn = 1 - turn;
            if (turn == 0) s1 += nums[i];
            else s2 += nums[i];
        }
        return s1 - s2;
    }
};