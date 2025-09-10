#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

std::vector<long long> parent;
std::vector<long long> size;
std::vector<long long> special;

void make_set(long long a) {
    parent[a] = a;
    size[a] = 1;
}

long long find_set(long long a) {
    if (parent[a] == a) return a;
    return parent[a] = find_set(parent[a]);
}

bool union_sets(long long a, long long b) {
    a = find_set(a);
    b = find_set(b);
    if (a == b) return false;
    if (size[a] < size[b]) std::swap(a, b);
    parent[b] = a;
    size[a] += size[b];
    special[a] += special[b];  // added line for special vertices
    return true;
}

bool is_connected(long long a, long long b) {
    return find_set(a) == find_set(b);
}

void problem1081D() {
    ll n, m, k, x_i, u, v, w;
    std::cin >> n >> m >> k;
    parent.resize(n + 1);
    size.resize(n + 1);
    special.resize(n + 1);
    std::set<ll> x;
    for (ll i = 1; i <= k; i++) {
        std::cin >> x_i;
        x.insert(x_i);
    }
    std::vector<std::pair<ll, pll>> edges;
    for (ll i = 1; i <= m; i++) {
        std::cin >> u >> v >> w;
        edges.push_back({w, {u, v}});
    }
    std::sort(edges.begin(), edges.end());
    for (ll i = 1; i <= n; i++) {
        make_set(i);
        if (x.count(i)) special[i] = 1;
        else special[i] = 0;
    }
    ll ans = 0;
    for (std::pair<ll, pll> pair: edges) {  // create mst of special vertices
        w = pair.first, u = pair.second.first, v = pair.second.second;
        if (is_connected(u, v)) continue;
        union_sets(u, v);
        if (special[find_set(u)] == k) {  // all special vertices in same component
            ans = w;
            break;
        }
    }
    for (ll i = 1; i <= k; i++) {
        std::cout << ans << " ";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    problem1081D();
    return 0;
}