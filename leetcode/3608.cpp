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

    int minTime(int n, vector<vector<int>> &edges, int k) {
        int m = edges.size();
        if (m == 0) return 0;

        dsu d(n);
        sort(edges.begin(), edges.end(), [](vector<int> &a, vector<int> &b) {
            return a[2] > b[2];
            });
        int comp = n;

        for (int i = 0; i < m; i++) {
            if (d.union_sets(edges[i][0], edges[i][1])) comp--;
            if (comp < k) return edges[i][2];
        }
        return 0;
    }
};