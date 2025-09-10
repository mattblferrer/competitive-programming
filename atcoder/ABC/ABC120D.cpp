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

void ABC120D() {
    ll n, m, a_i, b_i;
    std::cin >> n >> m;
    std::vector<pll> pairs(m + 1);
    for (int i = 1; i <= m; i++) {
        std::cin >> a_i >> b_i;
        pairs[i] = {a_i, b_i};
    }
    parent.resize(n + 1);
    size.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        make_set(i);
    }
    std::vector<ll> ans(m + 1);
    ll inc = n * (n - 1) / 2;
    for (int i = m; i > 0; i--) {
        ans[i] = inc;
        a_i = find_set(pairs[i].first), b_i = find_set(pairs[i].second);
        if (a_i == b_i) continue;
        inc += (size[a_i] * (size[a_i] - 1)) / 2 + (size[b_i] * (size[b_i] - 1)) / 2;
        union_sets(a_i, b_i);
        a_i = find_set(a_i);
        inc -= (size[a_i] * (size[a_i] - 1)) / 2;
        
    }
    for (int i = 1; i <= m; i++) {
        std::cout << ans[i] << "\n";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    ABC120D();
    return 0;
}