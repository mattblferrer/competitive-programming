#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

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
