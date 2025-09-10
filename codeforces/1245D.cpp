#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

std::vector<long long> parent;
std::vector<long long> size;

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
    return true;
}

bool is_connected(long long a, long long b) {
    return find_set(a) == find_set(b);
}

ll distance(ll x_1, ll y_1, ll x_2, ll y_2) {
    return abs(x_2 - x_1) + abs(y_2 - y_1);
}

void problem1245D() {
    ll n, x_i, y_i;
    std::cin >> n;
    std::vector<pll> xy(n + 1);
    std::vector<ll> c(n + 1), k(n + 1);
    parent.resize(n + 1);
    size.resize(n + 1);
    make_set(0);
    for (ll i = 1; i <= n; i++) {
        std::cin >> x_i >> y_i;
        xy[i] = {x_i, y_i};
        make_set(i);
    }
    for (ll i = 1; i <= n; i++) {
        std::cin >> c[i];
    }
    for (ll i = 1; i <= n; i++) {
        std::cin >> k[i];
    }

    std::vector<std::pair<ll, pll>> edges;
    for (ll i = 1; i <= n; i++) {
        edges.push_back({c[i], {0, i}});
        for (ll j = i + 1; j <= n; j++) {
            ll dist = distance(xy[i].first, xy[i].second, xy[j].first, xy[j].second);
            edges.push_back({(k[i] + k[j]) * dist, {i, j}});
        }
    }
    std::sort(edges.begin(), edges.end());

    ll cost = 0;
    std::vector<ll> power;
    std::vector<pll> conn;
    for (std::pair<ll, pll> pair: edges) {
        ll dist = pair.first, u = pair.second.first, v = pair.second.second;
        if (is_connected(u, v)) continue;
        if (u == 0) power.push_back(v);
        else conn.push_back({u, v});
        cost += dist;
        union_sets(u, v);
    }
    
    std::sort(power.begin(), power.end());
    std::cout << cost << "\n" << power.size() << "\n";  // min yen, v
    for (ll i: power) std::cout << i << " ";  // power stations
    std::cout << "\n" << conn.size() << "\n";  // e
    for (const auto& pair: conn) std::cout << pair.first << " " << pair.second << "\n";  // connections
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    problem1245D();
    return 0;
}