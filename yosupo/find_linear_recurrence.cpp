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

// a^b mod mod, O(log b)
ll binexp(ll a, ll b, ll mod) {
    ll ans = 1;
    a %= mod;
    while (b) {
        if (b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}

// shortest linear recurrence of s mod a prime (Berlekamp-Massey), O(n^2)
// returns c so that s[i] = c[0] * s[i - 1] + c[1] * s[i - 2] + ... for every i >= c.size()
vector<ll> berlekamp_massey(const vector<ll> &s, ll mod) {
    int n = s.size(), len = 0, m = 0;
    vector<ll> cur(n + 1, 0), prev(n + 1, 0);
    cur[0] = prev[0] = 1;
    ll b = 1;
    for (int i = 0; i < n; i++) {
        m++;
        ll d = (s[i] % mod + mod) % mod;
        for (int j = 1; j <= len; j++) d = (d + cur[j] * ((s[i - j] % mod + mod) % mod)) % mod;
        if (d == 0) continue;
        vector<ll> saved = cur;
        ll coef = d * binexp(b, mod - 2, mod) % mod;
        for (int j = m; j < n + 1; j++) cur[j] = ((cur[j] - coef * prev[j - m]) % mod + mod) % mod;
        if (2 * len > i) continue;
        len = i + 1 - len;
        prev = saved;
        b = d;
        m = 0;
    }
    vector<ll> c(len);
    for (int i = 0; i < len; i++) c[i] = (mod - cur[i + 1]) % mod;
    return c;
}

void solve() {
    ll n;
    cin >> n;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    vector<ll> rec = berlekamp_massey(a, MOD);
    cout << rec.size() << "\n";
    for (ll i = 0; i < rec.size(); i++) cout << rec[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
