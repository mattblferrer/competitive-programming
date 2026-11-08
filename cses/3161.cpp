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

// cnt[g] = number of non-empty subsets of a with gcd exactly g, mod mod, O(MAX log MAX) where MAX = max(a)
vector<ll> gcd_subset_count(const vector<int> &a, ll mod) {
    int mx = a.empty() ? 0 : *max_element(a.begin(), a.end());
    vector<int> freq(mx + 1, 0);
    for (int x : a) freq[x]++;
    vector<ll> cnt(mx + 1, 0);
    for (int g = mx; g >= 1; g--) {
        ll multiples = 0, sub = 0;
        for (int j = g; j <= mx; j += g) {
            multiples += freq[j];
            if (j > g) sub += cnt[j];
        }
        cnt[g] = ((binexp(2, multiples, mod) - 1 - sub) % mod + mod) % mod;
    }
    return cnt;
}

void solve() {
    ll n;
    cin >> n;
    vector<int> x(n);
    for (ll i = 0; i < n; i++) cin >> x[i];

    vector<ll> cnt = gcd_subset_count(x, MOD);
    for (ll i = 1; i < cnt.size(); i++) cout << cnt[i] << " ";
    for (ll i = cnt.size(); i <= n; i++) cout << 0 << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
