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

// a^b mod mod, O(log b)
ll binexp(ll a, ll b, ll mod) {
    ll ans = 1;
    a %= mod;
    while (b) {
        if (b % 2) {
            ans = (ans * a) % mod;
        }
        a = (a * a) % mod;
        b >>= 1;
    }
    return ans;
}

// nCk mod any m >= 1 (Granville + CRT over the prime powers p^e dividing m); m should be small, m^2 must fit in ll
//   CombAny(m)    tables for each p^e, O(m)
//   (n, k)        nCk mod m for any n, k fitting in ll, O(sum over p^e of log_p n + log m)
struct CombAny {
    struct PP { ll p, pe; vector<ll> f; };  // f[i] = product of 1..i without the multiples of p, mod pe
    ll m;
    vector<PP> pps;

    CombAny(ll m): m(m) {
        ll rest = m;
        for (ll p = 2; rest > 1; p++) {
            if (p * p > rest) p = rest;
            if (rest % p) continue;
            ll pe = 1;
            while (rest % p == 0) rest /= p, pe *= p;
            vector<ll> f(pe, 1);
            for (ll i = 1; i < pe; i++) f[i] = i % p ? f[i - 1] * i % pe : f[i - 1];
            pps.push_back({p, pe, f});
        }
    }

    ll operator()(ll n, ll k) const {
        if (k < 0 || k > n || m == 1) return 0;
        ll ans = 0, modulus = 1;
        for (auto &[p, pe, f] : pps) {
            ll e = 0, phi = pe / p * (p - 1);
            auto fact = [&](ll x, int sign) {  // unit part of x! mod pe; adds sign * (power of p in x!) to e
                ll r = 1;
                for (; x > 0; x /= p) {
                    r = r * f[x % pe] % pe;
                    if (x / pe % 2) r = r * f[pe - 1] % pe;  // f[pe - 1] is +-1, so f[pe - 1]^(x / pe) is a sign
                    e += sign * (x / p);
                }
                return r;
            };
            ll cur = fact(n, 1) * binexp(fact(k, -1) * fact(n - k, -1) % pe, phi - 1, pe) % pe;
            cur = cur * binexp(p, e, pe) % pe;
            ll t = ((cur - ans) % pe + pe) % pe * binexp(modulus % pe, phi - 1, pe) % pe;  // merge with CRT
            ans += modulus * t;
            modulus *= pe;
        }
        return ans % m;
    }
};

void solve() {
    ll t, m;
    cin >> t >> m;
    CombAny comb(m);
    while (t--) {
        ll n, k;
        cin >> n >> k;
        cout << comb(n, k) << "\n";
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
