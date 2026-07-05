class Solution {
public:
    struct point_segtree {
        int n;
        int *vals;
        point_segtree(vector<int> &ar, int n) {
            this->n = n;
            vals = new int[2 * n];
            for (int i = 0; i < n; ++i) vals[i + n] = ar[i];
            for (int i = n - 1; i > 0; --i) vals[i] = max(vals[i << 1], vals[i << 1 | 1]);
        }
        void update(int i, int v) {
            for (vals[i += n] += v; i > 1; i >>= 1)
                vals[i >> 1] = max(vals[i], vals[i ^ 1]);
        }
        int query(int l, int r) {
            int res = -10000000;
            for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
                if (l & 1) res = max(res, vals[l++]);
                if (r & 1) res = max(res, vals[--r]);
            }
            return res;
        }
    };

    int maxValidPairSum(vector<int> &nums, int k) {
        int n = nums.size();
        point_segtree tree(nums, n);
        int ans = 0;
        for (int i = 0; i < n - 1; i++) {
            ans = max(ans, nums[i] + tree.query(i + k, n - 1));
        }
        return ans;
    }
};