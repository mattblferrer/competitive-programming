#include <bits/stdc++.h>
using namespace std;
class DSU {
public:
    vector<int> parent, siz;

    DSU(int n) {
        parent.resize(n + 1);
        siz.resize(n + 1, 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
        }
    }

    int find_set(int v)
    {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    void union_sets(int a, int b)
    {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (siz[a] < siz[b])
                swap(a, b);
            parent[b] = a;
            siz[a] += siz[b];
        }
    }

    int get_size(int v) {
        return siz[find_set(v)];
    }
};

void solve() {
    int n, m, k; cin >> n >> m >> k;

    DSU dsu(n);
    for (int i = 0; i < m; i++)
    {
        int l, r; cin >> l >> r; l--; r--;
        dsu.union_sets(l, r);
    }

    vector<int> assignment(n, -1);
    vector<int> count(n, 0);
    for (int i = 0; i < n; i++)
    {
        if (dsu.get_size(i) != 0 && dsu.get_size(i) < k)
        {
            cout << "impossible\n";
            return;
        }
    }

    for (int i = 0; i < n; i++)
    {
        int cur_group = dsu.find_set(i);
        assignment[i] = (count[cur_group] % k) + 1;
        count[cur_group]++;
    }

    for (int i : assignment) cout << i << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}