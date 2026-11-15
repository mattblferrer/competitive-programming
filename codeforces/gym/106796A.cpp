#include <bits/stdc++.h>
using namespace std;
struct DeltaDSU {
    vector<int> parent;
    vector<long long> delta;

    DeltaDSU(int n): parent(n + 1), delta(n + 1, 0) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        int root = find(parent[x]);
        delta[x] += delta[parent[x]];
        return parent[x] = root;
    }

    bool unite(int x, int y, long long d) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) {
            return (delta[x] - delta[y]) == d;
        }

        parent[rx] = ry;
        delta[rx] = d - delta[x] + delta[y];
        return true;
    }

    long long diff(int x, int y) {
        find(x);
        find(y);
        return delta[x] - delta[y];
    }
};

int main() {
    int n, a, b; cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        std::cin >> a >> b; a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    DeltaDSU dsu(n);
    vector<int> change(n, 0);
    for (int i = 0; i < n; i++)
    {
        int rep = adj[i].front();
        if (adj.size() != 1) for (int c : adj[i])
        {
            if (rep != c) dsu.unite(rep, c, change[rep] - change[c]);
        }
        for (int c : adj[i])
        {
            change[c]--;
            change[i]++;
        }
    }

    vector<int> ans(n, 0);
    for (int i = 1; i < n; i++)
    {
        ans[i] = dsu.diff(0, i);
    }

    int min_num = *min_element(ans.begin(), ans.end());
    for (int i = 0; i < n; i++) ans[i] += (n - min_num);
    for (int i = 0; i < n; i++) cout << ans[i] << " ";
}