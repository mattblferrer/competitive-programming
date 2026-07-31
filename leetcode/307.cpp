class NumArray {
public:
    int n;
    int *vals;
    NumArray(vector<int> &nums) {
        this->n = nums.size();
        this->vals = new int[2 * n];
        for (int i = 0; i < n; ++i) vals[i + n] = nums[i];
        for (int i = n - 1; i > 0; --i) vals[i] = vals[i << 1] + vals[i << 1 | 1];
    }

    void update(int index, int val) {
        for (vals[index += n] = val; index > 1; index >>= 1)
            vals[index >> 1] = vals[index] + vals[index ^ 1];
    }

    int sumRange(int left, int right) {
        int res = 0;
        for (left += n, right += n + 1; left < right; left >>= 1, right >>= 1) {
            if (left & 1) res += vals[left++];
            if (right & 1) res += vals[--right];
        }
        return res;
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */