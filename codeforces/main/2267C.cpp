#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

vector<ll> spf(300'001);

void precomp() {
    for (ll i = 0; i <= 300'000; i++) spf[i] = i;
    for (ll i = 2; i <= 300'000; i++) {
        for (ll j = i * i; j <= 300'000; j += i) {
            spf[j] = min(spf[j], i);
        }
    }
}

void solve() {
    ll n, x;
    cin >> n >> x;
    vector<ll> a(n + 1);
    for (ll i = 1; i <= n; i++) cin >> a[i];

    map<ll, ll> pf;
    for (ll i = 1; i <= n; i++) {
        set<ll> primes;
        ll div = a[i];
        while (div != 1) {
            primes.insert(spf[div]);
            div /= spf[div];
        }
        for (ll p : primes) pf[p] += a[i];
    }
    ll ans = 0;
    for (const auto &[ai, score] : pf) {
        if (gcd(x, ai) != 1) ans = max(ans, score);
    }

    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    precomp();
    int t; cin >> t; while (t--) solve();
    return 0;
}