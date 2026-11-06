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
    ll n;
    cin >> n;
    vector<ll> a, b;
    ll as = 0, bs = 0;
    for (ll i = n; i >= 1; i--) {
        if (as > bs) {
            b.push_back(i);
            bs += i;
        }
        else {
            a.push_back(i);
            as += i;
        }
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    if (as != bs) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    cout << a.size() << "\n";
    for (ll i = 0; i < a.size(); i++) cout << a[i] << " ";
    cout << "\n" << b.size() << "\n";
    for (ll i = 0; i < b.size(); i++) cout << b[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
