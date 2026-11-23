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

// floor(a^(1/k)) for any a < 2^64 and k >= 1, O(k)
ull kth_root_floor(ull a, ull k) {
    if (k == 1 || a <= 1) return a;
    if (k >= 64) return 1;
    auto fits = [&](ull x) {  // x^k <= a, without overflow
        ull r = 1;
        for (ull i = 0; i < k; i++) {
            if (r > a / x) return false;
            r *= x;
        }
        return true;
    };
    ull x = powl((ld)a, 1.0L / k);  // off by at most a few, fixed below
    while (!fits(x)) x--;
    while (fits(x + 1)) x++;
    return x;
}

void solve() {
    ull a, k;
    cin >> a >> k;
    cout << kth_root_floor(a, k) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    cin >> t;  // comment out for single test
    while (t--) solve();
}
