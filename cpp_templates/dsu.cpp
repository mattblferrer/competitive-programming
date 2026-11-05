#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// disjoint set union with path compression and union by size
//   DSU(n)               n singleton sets {0}, ..., {n - 1}, O(n)
//   find_set(a)          representative of a's set, O(alpha(n)) amortized
//   union_sets(a, b)     merge the sets of a and b; false if already in the same set, O(alpha(n))
//   is_connected(a, b)   whether a and b are in the same set, O(alpha(n))
struct DSU {
    vector<int> parent, sz;

    DSU(int n): parent(n), sz(n, 1) {
        iota(parent.begin(), parent.end(), 0);
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
