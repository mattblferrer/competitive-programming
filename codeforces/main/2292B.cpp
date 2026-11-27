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

void solve() {
    ll n, k, p;
    cin >> n >> k >> p;
    vector<ll> a(n + 1);
    for (ll i = 1; i <= n; i++) cin >> a[i];

    sort(a.begin(), a.end());
    vector<ll> pref(n + 1);
    for (ll i = 1; i <= n; i++) pref[i] = pref[i - 1] + a[i];

    ll ans = 0, i = 1;
    while (i <= n - k + 1) {
        if (pref[i + k - 1] - pref[i - 1] < p) {
            ans += p;
            i += k;
        }
        else {
            ans += a[i];
            i++;
        }
    }
    while (i <= n) {
        ans += a[i];
        i++;
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    cin >> t;  // comment out for single test
    while (t--) solve();
}
