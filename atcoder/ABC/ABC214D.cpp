#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

std::vector<ll> parent;
std::vector<ll> size;

void make_set(int a) {
    parent[a] = a;
    size[a] = 1;
}

int find_set(int a) {
    if (parent[a] == a) return a;
    return parent[a] = find_set(parent[a]);
}

bool union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a == b) return false;
    if (size[a] < size[b]) std::swap(a, b);
    parent[b] = a;
    size[a] += size[b];
    return true;
}

bool is_connected(int a, int b) {
    return find_set(a) == find_set(b);
}

ll ABC214D() {
    ll n, u, v, w, ans = 0;
    std::cin >> n;
    parent.resize(n + 1);
    size.resize(n + 1);
    std::vector<std::pair<ll, pll>> edges;
    for (ll i = 1; i <= n - 1; i++) {
        std::cin >> u >> v >> w;
        edges.push_back({w, {u, v}});
    }
    std::sort(edges.begin(), edges.end());
    for (ll i = 1; i <= n; i++) {
        make_set(i);
    }
    for (std::pair<ll, pll> pair: edges) {
        w = pair.first, u = pair.second.first, v = pair.second.second;
        if (is_connected(u, v)) continue;
        ans += w * size[find_set(u)] * size[find_set(v)];
        union_sets(u, v); 
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << ABC214D() << "\n";
    return 0;
}