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
    vector<bool> friendRequests(int n, vector<vector<int>> &restrictions, vector<vector<int>> &requests) {
        dsu res_dsu(n), req_dsu(n);
        int res_sz = restrictions.size(), req_sz = requests.size();
        for (int i = 0; i < res_sz; i++) {
            int xi = restrictions[i][0], yi = restrictions[i][1];
            res_dsu.union_sets(xi, yi);
        }
        vector<bool> result(req_sz, true);
        for (int i = 0; i < req_sz; i++) {
            int ui = requests[i][0], vi = requests[i][1];
            for (int j = 0; j < res_sz; j++) {
                int xi = restrictions[j][0], yi = restrictions[j][1];
                if ((req_dsu.find_set(xi) == req_dsu.find_set(ui)) &&
                    (req_dsu.find_set(yi) == req_dsu.find_set(vi))) {
                    result[i] = false; break;
                }
                if ((req_dsu.find_set(xi) == req_dsu.find_set(vi)) &&
                    (req_dsu.find_set(yi) == req_dsu.find_set(ui))) {
                    result[i] = false; break;
                }
            }
            if (result[i]) req_dsu.union_sets(ui, vi);
        }
        return result;
    }
};