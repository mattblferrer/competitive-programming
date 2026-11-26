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

// calls f(q, l, r) for each maximal block [l, r] of i in [1, n] with floor(n / i) = q, in increasing l (so decreasing
// q); there are at most 2 sqrt(n) blocks, and the q are exactly the distinct values of floor(n / i), O(sqrt(n))
template <class F>
void floor_blocks(ll n, F f) {
    for (ll l = 1, r; l <= n; l = r + 1) {
        ll q = n / l;
        r = n / q;
        f(q, l, r);
    }
}

void solve() {
    ll n;
    cin >> n;
    vector<ll> ans;
    floor_blocks(n, [&](ll q, ll, ll) { ans.push_back(q); });
    reverse(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for (ll q : ans) cout << q << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
