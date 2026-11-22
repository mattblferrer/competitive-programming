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

// sum of floor((a * i + b) / m) for i in [0, n); m > 0, a and b can be negative, O(log m)
// the answer and a * n + b (after reducing a and b mod m) must fit in ll
// lattice points with A * x + B * y <= C, 0 <= x <= n, y >= 0 is floor_sum(n + 1, B, -A, C + B) when C - A * n >= 0
ll floor_sum(ll n, ll m, ll a, ll b) {
    ll ans = 0;
    if (a < 0) {
        ll r = (a % m + m) % m;
        ans -= n * (n - 1) / 2 * ((r - a) / m);
        a = r;
    }
    if (b < 0) {
        ll r = (b % m + m) % m;
        ans -= n * ((r - b) / m);
        b = r;
    }
    while (true) {
        if (a >= m) {
            ans += n * (n - 1) / 2 * (a / m);
            a %= m;
        }
        if (b >= m) {
            ans += n * (b / m);
            b %= m;
        }
        ll y_max = a * n + b;
        if (y_max < m) break;
        n = y_max / m;
        b = y_max % m;
        swap(m, a);
    }
    return ans;
}

void solve() {
    ll n, m, a, b;
    cin >> n >> m >> a >> b;
    cout << floor_sum(n, m, a, b) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    cin >> t;  // comment out for single test
    while (t--) solve();
}
