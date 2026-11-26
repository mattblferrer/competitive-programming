// github.com/mattblferrer/competitive-programming

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using ull = unsigned long long;
const ld PI = acosl(-1);
const ll INF = 2e18;
const ll MOD = 998244353;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << '\n'
#else
#define dbg(x)
#endif

// Aho-Corasick automaton: KMP for many patterns over the alphabet [BASE, BASE + ALPHA)
//   add(s)          add pattern s, O(|s|)
//   build()         compute the fail links; call exactly once, after all adds, O(nodes * ALPHA)
//   count(text)     total occurrences of all patterns in text, counted with multiplicity, O(|text|)
template <int ALPHA = 26, char BASE = 'a'>
struct AhoCorasick {
    vector<array<int, ALPHA>> next;
    vector<int> fail;
    vector<ll> words;

    AhoCorasick() { new_node(); }

    int new_node() {
        array<int, ALPHA> a;
        a.fill(-1);
        next.push_back(a);
        fail.push_back(0);
        words.push_back(0);
        return next.size() - 1;
    }

    void add(const string &s) {
        int v = 0;
        for (char ch : s) {
            int c = ch - BASE;
            if (next[v][c] == -1) {
                int u = new_node();
                next[v][c] = u;
            }
            v = next[v][c];
        }
        words[v]++;
    }

    void build() {
        queue<int> q;
        for (int c = 0; c < ALPHA; c++) {
            int &u = next[0][c];
            if (u == -1) u = 0;
            else q.push(u);
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            words[v] += words[fail[v]];
            for (int c = 0; c < ALPHA; c++) {
                int &u = next[v][c];
                if (u == -1) {
                    u = next[fail[v]][c];
                } else {
                    fail[u] = next[fail[v]][c];
                    q.push(u);
                }
            }
        }
    }

    ll count(const string &text) const {
        ll res = 0;
        int v = 0;
        for (char ch : text) {
            v = next[v][ch - BASE];
            res += words[v];
        }
        return res;
    }
};

void solve() {
    ll n;
    cin >> n;
    AhoCorasick<> ac;
    vector<string> s(n);
    for (ll i = 0; i < n; i++) {
        cin >> s[i];
        ac.add(s[i]);
    }
    ll m = ac.next.size();
    vector<ll> par(m), end(n);
    for (ll v = 0; v < m; v++) {
        for (ll c = 0; c < 26; c++) if (ac.next[v][c] != -1) par[ac.next[v][c]] = v;
    }
    for (ll i = 0; i < n; i++) {
        ll v = 0;
        for (char ch : s[i]) v = ac.next[v][ch - 'a'];
        end[i] = v;
    }
    ac.build();
    cout << m << "\n";
    for (ll v = 1; v < m; v++) cout << par[v] << " " << ac.fail[v] << "\n";
    for (ll i = 0; i < n; i++) cout << end[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
