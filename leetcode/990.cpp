class Solution {
public:
    struct dsu {
        vector<int> parent, sz;

        dsu(int a) {
            parent.resize(a);
            sz.resize(a, 1);
            for (int i = 0; i < a; i++) parent[i] = i;
        }

        int find_set(int a) {
            if (parent[a] == a) return a;
            return parent[a] = find_set(parent[a]);
        }

        bool union_sets(int a, int b) {
            a = find_set(a);
            b = find_set(b);
            if (a == b) return false;
            if (sz[a] < sz[b]) swap(a, b);
            parent[b] = a;
            sz[a] += sz[b];
            return true;
        }

        bool is_connected(int a, int b) { return find_set(a) == find_set(b); }
    };

    bool equationsPossible(vector<string> &equations) {
        int n = equations.size();
        dsu eq(26);
        vector<vector<int>> neq(26, vector<int>(26));
        for (int i = 0; i < n; i++) {
            int xi = equations[i][0] - 'a';
            bool is_eq = (equations[i][1] == '=');
            int yi = equations[i][3] - 'a';
            if (xi == yi) {
                if (is_eq) continue;
                else return false;
            }
            if (is_eq) eq.union_sets(xi, yi);
            else neq[xi][yi] = neq[yi][xi] = true;
        }
        for (int i = 0; i < 26; i++) {
            for (int j = i + 1; j < 26; j++) {
                if (eq.is_connected(i, j) && neq[i][j]) return false;
            }
        }
        return true;
    }
};