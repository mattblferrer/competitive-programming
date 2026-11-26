// github.com/mattblferrer/competitive-programming

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using ull = unsigned long long;
const ld PI = acosl(-1);
const ll INF = 2e18;
const ll MOD = 1'000'000'007;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << '\n'
#else
#define dbg(x)
#endif

// persistent queue: push and pop make a new version and leave the old ones unchanged; version 0 is empty
// every element ever pushed is a node of a tree whose parent is the back of the version it was pushed onto;
// a version is {back node, size}, and its front is the ancestor of the back node at depth dep(back) - size + 1,
// found in O(log n) with skew-binary jump pointers (Myers), so each node costs O(1) memory
//   push(ver, x)    x pushed at the back of ver, returns the new version, O(1)
//   pop(ver)        ver without its front; ver must not be empty, returns the new version, O(1)
//   front(ver)      front element of ver; ver must not be empty, O(log n)
//   back(ver)       back element of ver; ver must not be empty, O(1)
//   size(ver)       number of elements in ver, O(1)
template <class T>
struct PersistentQueue {
    struct Node { int par, jump, dep; T val; };
    vector<Node> t{{0, 0, 0, T()}};  // t[0] is the root, below every element
    vector<pair<int, int>> vers{{0, 0}};  // {back node, size}

    int push(int ver, const T &x) {
        int p = vers[ver].first, j = t[p].jump;
        int jump = t[p].dep - t[j].dep == t[j].dep - t[t[j].jump].dep ? t[j].jump : p;
        t.push_back({p, jump, t[p].dep + 1, x});
        vers.push_back({(int)t.size() - 1, vers[ver].second + 1});
        return vers.size() - 1;
    }

    int pop(int ver) {
        vers.push_back({vers[ver].first, vers[ver].second - 1});
        return vers.size() - 1;
    }

    T front(int ver) const {
        auto [u, s] = vers[ver];
        int d = t[u].dep - s + 1;
        while (t[u].dep > d) u = t[t[u].jump].dep < d ? t[u].par : t[u].jump;
        return t[u].val;
    }

    T back(int ver) const { return t[vers[ver].first].val; }
    int size(int ver) const { return vers[ver].second; }
};

void solve() {
    ll q;
    cin >> q;
    PersistentQueue<ll> que;
    vector<int> ver(q + 1, 0);
    for (ll i = 0; i < q; i++) {
        ll type, t;
        cin >> type >> t;
        if (type == 0) {
            ll x;
            cin >> x;
            ver[i + 1] = que.push(ver[t + 1], x);
        }
        if (type == 1) {
            cout << que.front(ver[t + 1]) << "\n";
            ver[i + 1] = que.pop(ver[t + 1]);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
