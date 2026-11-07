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
    ll n, q;
    cin >> n >> q;
    vector<ll> k(q);
    for (ll i = 0; i < q; i++) cin >> k[i];

    vector<ll> cards(n + 1);
    for (ll i = 1; i <= n; i++) cards[i] = i;
    for (ll i = 0; i < q; i++) {
        reverse(cards.begin() + 1, cards.begin() + k[i] + 1);
        for (ll j = 1; j <= k[i]; j++) {
            cards[j] = -cards[j];
        }
    }
    for (ll i = 1; i <= n; i++) cout << cards[i] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
