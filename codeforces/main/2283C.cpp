// github.com/mattblferrer/competitive-programming

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void test() {
    ll n;
    cin >> n;
    vector<ll> a(n + 1), b(n + 1);
    for (ll i = 1; i <= n; i++) {
        bool di;
        cin >> di;
        a[i] = i;
        if (di) b[i] = 2 * i;
        else b[i] = i;
    }
    ll a_or = 0, b_xor = 0;
    for (ll i = 1; i <= n; i++) {
        a_or |= a[i];
        b_xor ^= b[i];
    }
    cout << a_or << " " << b_xor << "\n";
}

void solve(ll n) {
    vector<bool> d(n + 1);

    ll all_or = 0;
    for (ll i = 1; i <= n; i++) {
        all_or |= i;
    }
    ll all_xor = 0;
    for (ll i = 1; i <= n; i++) {
        all_xor ^= i;
    }

    for (ll i = n; i >= 1; i--) {
        if ((all_xor ^ (i) ^ (2 * i)) > all_xor) {
            d[i] = 1;
            all_xor = (all_xor ^ (i) ^ (2 * i));
        }
    }

    for (ll i = 1; i <= n; i++) cout << d[i] << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        solve(n);
    }
    return 0;
}