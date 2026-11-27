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

// f(0..n) (f(0) = 0, f(1) = 1) for any multiplicative f from fpk(p, k) = f(p^k), by a linear sieve that tracks the
// full power pw[i] of the smallest prime of i: f(i) = f(i / pw[i]) f(pw[i]), and fpk is called once per prime power,
// O(n) time; T is ll, int or a modular type
template <class T, class F>
vector<T> multiplicative_sieve(int n, F fpk) {
    vector<T> f(n + 1);
    vector<int> pw(n + 1), primes;
    vector<char> e(n + 1);
    if (n >= 1) f[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!pw[i]) {
            pw[i] = i, e[i] = 1, f[i] = fpk(i, 1);
            primes.push_back(i);
        }
        for (int p : primes) {
            if ((ll)i * p > n) break;
            int ip = i * p;
            if (i % p == 0) {  // p is the smallest prime of i
                pw[ip] = pw[i] * p, e[ip] = e[i] + 1;
                f[ip] = pw[ip] == ip ? fpk(p, e[ip]) : f[ip / pw[ip]] * f[pw[ip]];
                break;
            }
            pw[ip] = p, e[ip] = 1, f[ip] = f[i] * f[p];
        }
    }
    return f;
}

vector<ll> sieve = multiplicative_sieve<ll>(1'000'001, [](int p, int k) {
    return k + 1;
    });

void solve() {
    ll x;
    cin >> x;
    cout << sieve[x] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    cin >> t;  // comment out for single test
    while (t--) solve();
}
