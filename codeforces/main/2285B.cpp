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
    ll n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    ll zeros = 0, ones = 0;
    for (ll i = 0; i < n; i++) {
        if (s[i] == '0') zeros++;
        else ones++;
    }
    if (zeros < ones) {
        for (ll i = 0; i < n; i++) {
            if ((k) && (s[i] == '0')) {
                s[i] = '1';
                k--;
            }
        }
    }
    else {
        for (ll i = 0; i < n; i++) {
            if ((k) && (s[i] == '1')) {
                s[i] = '0';
                k--;
            }
        }
    }
    zeros = 0, ones = 0;
    for (ll i = 0; i < n; i++) {
        if (s[i] == '0') zeros++;
        else ones++;
    }

    cout << (zeros * (zeros + 1)) / 2 + (ones * (ones + 1)) / 2 + 1 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    cin >> t;  // comment out for single test
    while (t--) solve();
}
