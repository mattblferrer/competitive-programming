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

// number of distinct non-empty subsequences of a (a string, or a vector of any comparable type) mod mod; add 1 for
// the empty one. f counts them with the empty one: appending x doubles f, minus the ones that already ended in x,
// which number f just before x last appeared, O(n log n)
template <class S>
ll distinct_subsequences(const S &a, ll mod) {
    map<typename S::value_type, ll> last;  // last[x] = f just before the latest x
    ll f = 1 % mod;
    for (const auto &x : a) {
        ll g = (2 * f - last[x] + mod) % mod;
        last[x] = f;
        f = g;
    }
    return (f - 1 + mod) % mod;
}

void solve() {
    ll n;
    cin >> n;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    cout << distinct_subsequences(a, MOD) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
