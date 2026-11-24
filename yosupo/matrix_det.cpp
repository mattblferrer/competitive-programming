// github.com/mattblferrer/competitive-programming

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using ull = unsigned long long;
const ld PI = acosl(-1);
const ll INF = 2e18;
const ll MOD = 998'244'353;
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

// determinant of a square matrix mod a prime, O(n^3)
ll det_mod(vector<vector<ll>> a, ll p) {
    int n = a.size();
    ll det = 1;
    for (int c = 0; c < n; c++) {
        int r = c;
        while (r < n && a[r][c] % p == 0) r++;
        if (r == n) return 0;
        if (r != c) {
            swap(a[r], a[c]);
            det = (p - det) % p;
        }
        det = det * ((a[c][c] % p + p) % p) % p;
        ll inv = binexp((a[c][c] % p + p) % p, p - 2, p);
        for (int i = c + 1; i < n; i++) {
            ll f = (a[i][c] % p + p) % p * inv % p;
            if (f == 0) continue;
            for (int j = c; j < n; j++) a[i][j] = ((a[i][j] - f * ((a[c][j] % p + p) % p)) % p + p) % p;
        }
    }
    return det;
}

void solve() {
    ll n;
    cin >> n;
    vector<vector<ll>> a(n, vector<ll>(n));
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) cin >> a[i][j];
    }
    cout << det_mod(a, MOD) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
