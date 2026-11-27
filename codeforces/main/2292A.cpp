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
    ll l, a, b;
    cin >> l >> a >> b;
    vector<ll> t1(l), t2(l);
    ll aa = 0, bb = 0;
    for (ll i = 0; i < l; i++) {
        if (t1[aa]) break;
        t1[aa]++;
        aa = (aa + a) % l;
    }
    for (ll i = 0; i < l; i++) {
        if (t2[bb]) break;
        t2[bb]++;
        bb = (bb + b) % l;
    }
    ll ans = 0;
    for (ll i = 0; i < l; i++) {
        if ((t1[i]) && (t2[i])) ans++;
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
