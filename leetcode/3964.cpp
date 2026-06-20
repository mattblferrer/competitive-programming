class Solution {
public:
    using ll = long long;
    using vll = vector<ll>;

    struct segtree {
        ll i, j, val, temp_val = 0;
        segtree *l, *r;
        segtree(vll &ar, int _i, int _j): i(_i), j(_j) {
            if (i == j) {
                val = ar[i];
                l = r = NULL;
            }
            else {
                int k = (i + j) >> 1;
                l = new segtree(ar, i, k);
                r = new segtree(ar, k + 1, j);
                val = l->val + r->val;
            }
        }
        void visit() {
            if (temp_val) {
                val += (j - i + 1) * temp_val;
                if (l) {
                    l->temp_val += temp_val;
                    r->temp_val += temp_val;
                }
                temp_val = 0;
            }
        }
        void increase(int _i, int _j, ll _inc) {
            visit();
            if (_i <= i && j <= _j) {
                temp_val += _inc;
                visit();
            }
            else if (_j < i or j < _i) {
                // do nothing
            }
            else {
                l->increase(_i, _j, _inc);
                r->increase(_i, _j, _inc);
                val = l->val + r->val;
            }
        }
        ll query(int _i, int _j) {
            visit();
            if (_i <= i and j <= _j)
                return val;
            else if (_j < i || j < _i)
                return 0;
            else
                return l->query(_i, _j) + r->query(_i, _j);
        }
    };

    int minLights(vector<int> &lights) {
        int ans = 0;
        int n = lights.size();
        vector<ll> lit(n);
        segtree tree(lit, 0, n - 1);
        for (int i = 0; i < n; i++) {
            int v = lights[i];
            if (v) tree.increase(max(0, i - v), min(n - 1, i + v), v);
        }
        for (int i = 0; i < n; i++) {
            if (tree.query(i, i) == 0) {
                ans++;
                tree.increase(i, min(n - 1, i + 2), 1);
            }
        }
        return ans;
    }
}