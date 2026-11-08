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

struct ImplicitTreap {
    struct Node {
        ll val, sum, add;
        unsigned pri;
        int sz, l, r;
        bool rev;  // v's own children are already swapped; rev means its children still need flipping
    };
    vector<Node> t;  // t[0] is the null node
    int root = 0;
    mt19937 gen{(unsigned)chrono::steady_clock::now().time_since_epoch().count()};

    ImplicitTreap(): t(1, Node{0, 0, 0, 0, 0, 0, 0, false}) {}

    void apply(int v, ll d) {
        if (!v) return;
        t[v].val += d;
        t[v].add += d;
        t[v].sum += d * t[v].sz;
    }

    void flip(int v) {
        if (!v) return;
        swap(t[v].l, t[v].r);
        t[v].rev = !t[v].rev;
    }

    void push(int v) {
        if (t[v].add) {
            apply(t[v].l, t[v].add);
            apply(t[v].r, t[v].add);
            t[v].add = 0;
        }
        if (t[v].rev) {
            flip(t[v].l);
            flip(t[v].r);
            t[v].rev = false;
        }
    }

    void pull(int v) {
        t[v].sz = t[t[v].l].sz + 1 + t[t[v].r].sz;
        t[v].sum = t[t[v].l].sum + t[v].val + t[t[v].r].sum;
    }

    int merge(int a, int b) {
        if (!a || !b) return a ? a : b;
        if (t[a].pri > t[b].pri) {
            push(a);
            t[a].r = merge(t[a].r, b);
            pull(a);
            return a;
        }
        push(b);
        t[b].l = merge(a, t[b].l);
        pull(b);
        return b;
    }

    // a gets the first k elements of v, b gets the rest
    void split(int v, int k, int &a, int &b) {
        if (!v) {
            a = b = 0;
            return;
        }
        push(v);
        if (k <= t[t[v].l].sz) {
            split(t[v].l, k, a, t[v].l);
            b = v;
        }
        else {
            split(t[v].r, k - t[t[v].l].sz - 1, t[v].r, b);
            a = v;
        }
        pull(v);
    }

    void insert(int p, ll v) {
        t.push_back({v, v, 0, gen(), 1, 0, 0, false});
        int a, b, id = t.size() - 1;
        split(root, p, a, b);
        root = merge(merge(a, id), b);
    }

    void erase(int p) {
        int a, b, c;
        split(root, p + 1, a, c);
        split(a, p, a, b);
        root = merge(a, c);
    }

    ll get(int p) {
        int v = root;
        while (true) {
            push(v);
            int left = t[t[v].l].sz;
            if (p < left) {
                v = t[v].l;
            }
            else if (p == left) {
                return t[v].val;
            }
            else {
                p -= left + 1;
                v = t[v].r;
            }
        }
    }

    ll query(int l, int r) {
        int a, b, c;
        split(root, r, a, c);
        split(a, l, a, b);
        ll res = t[b].sum;
        root = merge(merge(a, b), c);
        return res;
    }

    void update(int l, int r, ll v) {
        int a, b, c;
        split(root, r, a, c);
        split(a, l, a, b);
        apply(b, v);
        root = merge(merge(a, b), c);
    }

    void reverse(int l, int r) {
        int a, b, c;
        split(root, r, a, c);
        split(a, l, a, b);
        flip(b);
        root = merge(merge(a, b), c);
    }

    int size() const { return t[root].sz; }
};

void solve() {
    ll n, m;
    cin >> n >> m;
    string s;
    cin >> s;

    ImplicitTreap treap;
    for (ll i = 0; i < n; i++) {
        treap.insert(i, s[i]);
    }
    for (ll i = 0; i < m; i++) {
        ll a, b;
        cin >> a >> b;
        a--; b--;
        treap.reverse(a, b + 1);
    }
    for (ll i = 0; i < n; i++) {
        cout << (char)treap.get(i) << "";
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
