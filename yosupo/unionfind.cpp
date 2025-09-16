#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

using namespace std;

std::vector<long long> parent;
std::vector<long long> sz;  // size of connected component

void make_set(long long a) {
    parent[a] = a;
    sz[a] = 1;
}

long long find_set(long long a) {
    if (parent[a] == a) return a;
    return parent[a] = find_set(parent[a]);
}

bool union_sets(long long a, long long b) {
    a = find_set(a);
    b = find_set(b);
    if (a == b) return false;
    if (sz[a] < sz[b]) std::swap(a, b);
    parent[b] = a;
    sz[a] += sz[b];
    return true;
}

bool is_connected(long long a, long long b) {
    return find_set(a) == find_set(b);
}

void solve() {
    int n, q, t, u, v;
    cin >> n >> q;
    parent.resize(n);
    sz.resize(n);
    for (int i = 0; i < n; i++) {
        make_set(i);
    }
    for (int i = 0; i < q; i++) {
        cin >> t >> u >> v;
        if (t == 0) {
            union_sets(u, v);
        }
        if (t == 1) {
            cout << is_connected(u, v) << "\n";
        }
    }
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();
    return 0;
}