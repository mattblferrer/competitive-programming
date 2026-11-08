// random input generator; run as "gen seed", and the same seed always prints the same input

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
mt19937_64 rng;

// random integer in [lo, hi], O(1)
ll rnd(ll lo, ll hi) {
    return lo + rng() % (hi - lo + 1);
}

// n random integers in [lo, hi], O(n)
vector<ll> rnd_array(int n, ll lo, ll hi) {
    vector<ll> a(n);
    for (ll &x : a) x = rnd(lo, hi);
    return a;
}

// random permutation of 1..n, O(n)
vector<int> rnd_perm(int n) {
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    shuffle(p.begin(), p.end(), rng);
    return p;
}

// random string of length n using the first k lowercase letters, O(n)
string rnd_string(int n, int k = 26) {
    string s(n, 'a');
    for (char &c : s) c = 'a' + rnd(0, k - 1);
    return s;
}

// random tree on vertices 1..n as n - 1 edges; shape 0 = uniform parents, 1 = path, 2 = star, 3 = long and thin, O(n)
vector<pair<int, int>> rnd_tree(int n, int shape = 0) {
    vector<int> label = rnd_perm(n);
    vector<pair<int, int>> edges;
    for (int i = 1; i < n; i++) {
        int p = shape == 0 ? rnd(0, i - 1) : shape == 1 ? i - 1 : shape == 2 ? 0 : rnd(max(0, i - 3), i - 1);
        edges.push_back({label[p], label[i]});
    }
    shuffle(edges.begin(), edges.end(), rng);
    return edges;
}

// random simple graph on vertices 1..n with m edges (no loops or repeats); connected requires m >= n - 1, O(m log m) when sparse
vector<pair<int, int>> rnd_graph(int n, int m, bool connected = false) {
    assert((ll)m <= (ll)n * (n - 1) / 2);
    vector<pair<int, int>> edges;
    set<pair<int, int>> seen;
    if (connected) {
        assert(m >= n - 1);
        edges = rnd_tree(n);
        for (auto [u, v] : edges) seen.insert(minmax(u, v));
    }
    while ((int)edges.size() < m) {
        int u = rnd(1, n), v = rnd(1, n);
        if (u == v || !seen.insert(minmax(u, v)).second) continue;
        edges.push_back({u, v});
    }
    return edges;
}

int main(int argc, char **argv) {
    rng.seed(atoll(argv[argc - 1]));

    // replace with the problem's input format; small values make failures easy to read
    int n = rnd(1, 10);
    vector<ll> a = rnd_array(n, -10, 10);
    cout << n << '\n';
    for (int i = 0; i < n; i++) cout << a[i] << " \n"[i == n - 1];
    return 0;
}
